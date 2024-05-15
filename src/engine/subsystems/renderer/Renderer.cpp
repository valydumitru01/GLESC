/******************************************************************************
 * @file   Renderer.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include <omp.h>
#include "engine/subsystems/renderer/Renderer.h"

#include "engine/subsystems/transform/Transform.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/math/Frustum.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
#include "engine/subsystems/renderer/lighting/LightSpot.h"

using namespace GLESC::Render;


Counter Renderer::drawCounter{};

Renderer::Renderer(WindowManager& windowManager) :
    windowManager(windowManager), shader(Shader("Shader.glsl")),
    camera(),
    projection(createProjectionMatrix(CameraPerspective())),
    view(createViewMatrix(Transform::Transform())),
    frustum(view * projection) {
    camera.camera = &defaultCameraPerspective;
    camera.transform = &defaultCameraTransform;
}

Projection Renderer::createProjectionMatrix(const CameraPerspective& camera) {
    Projection projection;
    projection.makeProjectionMatrix(camera.getFovDegrees(), camera.getNearPlane(),
                                    camera.getFarPlane(),
                                    camera.getViewWidth(),
                                    camera.getViewHeight());
    return projection;
}

View Renderer::createViewMatrix(const Transform::Transform& transform) {
    View view;
    view.makeViewMatrixPosRot(transform.getPosition(), transform.getRotation());
    return view;
}


void Renderer::swapBuffers() const {
    getGAPI().swapBuffers(windowManager.getWindow());
}

void Renderer::start() {
    getGAPI().clear({
        Enums::ClearBits::Color,
        Enums::ClearBits::Depth,
        Enums::ClearBits::Stencil
    });
    getGAPI().clearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // TODO: Enable the renderer to work with multiple projection and view matrices (multiple cameras)
    Projection projection;
    projection.makeProjectionMatrix(camera.camera->getFovDegrees(), camera.camera->getNearPlane(),
                                    camera.camera->getFarPlane(),
                                    camera.camera->getViewWidth(),
                                    camera.camera->getViewHeight());
    this->setProjection(projection);
    View view;
    view.makeViewMatrixPosRot(camera.transform->getPosition(),
                              camera.transform->getRotation());
    this->setView(view);
}


void Renderer::renderMeshes(double timeOfFrame) {
    drawCounter.startFrame();
    View viewMat = getView();
    Projection projMat = getProjection();
    VP viewProj = viewMat * projMat;
    shader.bind(); // Activate the shader program before transform, material and lighting setup
    // Don't render anything if the view matrix is not valid
    frustum.update(viewProj);

#pragma omp parallel default(none) \
shared(adaptedMeshes, lights, sun, fog, skybox, timeOfFrame, view, projection, frustum, \
    viewMat, projMat, viewProj, mvMutex, normalMatMutex, mvpMutex, frustumMutex, \
    interpolationMutex, mvs, mvps, normalMats, isContainedInFrustum)
    {

#pragma omp for schedule(dynamic)
        for (auto& dynamicMesh : adaptedMeshes) {
            {
                std::lock_guard lockInterpolation(interpolationMutex);
                interpolationTransforms[dynamicMesh.transform].pushTransform(*dynamicMesh.transform);
            }
            Transform::Transform interpolatedTransform =
                interpolationTransforms[dynamicMesh.transform].interpolate(timeOfFrame);
            Model model = interpolatedTransform.getModelMatrix();

            BoundingVolume transformedBoundingVol =
                Transform::Transformer::transformBoundingVolume(*dynamicMesh.boundingVolume, model);
            {
                std::lock_guard lockMutex(frustumMutex);
                isContainedInFrustum[&dynamicMesh] = frustum.contains(transformedBoundingVol);
            }
            MVP MVPMat = model * viewProj;
            MV MV = model * viewMat;
            NormalMat normalMat;
            normalMat.makeNormalMatrix(MV);
            {
                std::lock_guard lockMVP(mvpMutex);
                mvs[&dynamicMesh] = MV;
            }
            {
                std::lock_guard lockMV(mvMutex);
                mvps[&dynamicMesh] = MVPMat;
            }
            {
                std::lock_guard lockNormalMat(normalMatMutex);
                normalMats[&dynamicMesh] = normalMat;
            }
        }
    }
    for (auto& dynamicMesh : adaptedMeshes) {
        if (!isContainedInFrustum[&dynamicMesh]) continue;
        const Material& material = *dynamicMesh.material;
        applyTransform(mvs[&dynamicMesh], mvps[&dynamicMesh], normalMats[&dynamicMesh]);
        applyMaterial(material);
        renderMesh(dynamicMesh);
    }
    applyLighSpots(lights, timeOfFrame);
    applySun(sun);
    applyFog(fog, camera.transform->getPosition());
    applySkybox(skybox, viewMat, projMat);
}

/* 10FPS gain from doing it parallely
void Renderer::renderMeshes(double timeOfFrame) {
    drawCounter.startFrame();

    View viewMat = getView();
    Projection projMat = getProjection();
    VP viewProj = viewMat * projMat;

    // Don't render anything if the view matrix is not valid
    frustum.update(viewProj);


    shader.bind(); // Activate the shader program before transform, material and lighting
    applyLighSpots(lights, timeOfFrame);
    applySun(sun);
    applyFog(fog);
    for (auto& dynamicMesh : adaptedMeshes) {
        interpolationTransforms[dynamicMesh.transform].pushTransform(*dynamicMesh.transform);
        Transform::Transform interpolatedTransform =
            interpolationTransforms[dynamicMesh.transform].interpolate(timeOfFrame);

        Model model = interpolatedTransform.getModelMatrix();

        BoundingVolume transformedBoundingVol =
            Transform::Transformer::transformBoundingVolume(*dynamicMesh.boundingVolume, model);
        if (!frustum.contains(transformedBoundingVol)) continue;
        const Material& material = *dynamicMesh.material;

        MVP MVPMat =model* viewProj ;
        MV MV = viewMat * model;
        NormalMat normalMat;
        normalMat.makeNormalMatrix(MV);

        applyTransform(MV, MVPMat, normalMat);
        applyMaterial(material);
        renderMesh(dynamicMesh);
    }

    applySkybox(skybox, viewMat, projMat);
}*/

void Renderer::applyLighSpots(const std::vector<Light>& lights, double timeOfFrame) const {
    size_t lightCount = static_cast<int>(lights.size());
    Shader::setUniform("uLights.count", lightCount);
    for (size_t i = 0; i < lightCount; i++) {
        const LightSpot& light = *lights[i].light;
        std::string iStr = std::to_string(i);
        const Transform::Transform& transform = *lights[i].transform;
        interpolationTransforms[&transform].pushTransform(transform);
        const Transform::Transform& interpolatedTransform =
            interpolationTransforms[&transform].interpolate(timeOfFrame);

        Position lightPosViewSpace =
            Transform::Transformer::transformPosition(interpolatedTransform.getPosition(), getView());
        Shader::setUniform("uLights.posInViewSpace[" + iStr + "]", lightPosViewSpace);

        if (!light.isDirty()) continue;

        Vec3F lightColor = light.getColor().getRGBVec3FNormalized();
        float lightIntensity = light.getIntensity();
        float lightRadius = light.getRadius();
        Shader::setUniform("uLights.color[" + iStr + "]", lightColor);
        Shader::setUniform("uLights.intensity[" + iStr + "]", lightIntensity);

        Shader::setUniform("uLights.radius[" + iStr + "]", lightRadius);
        light.setClean();
    }
}

void Renderer::applySun(const Sun& sunParam) {
    if (sunParam.sun == nullptr) return;
    GlobalSun sun = *sunParam.sun;

    if (!sun.isDirty()) applyAmbientLight(*sunParam.ambientLight);

    Vec3F sunColor = sun.getColor().getRGBVec3FNormalized();
    float sunIntensity = sun.getIntensity();
    Math::Direction sunDirection = sun.getDirection();
    Shader::setUniform("uGlobalSun.color", sunColor);
    Shader::setUniform("uGlobalSun.intensity", sunIntensity);
    Shader::setUniform("uGlobalSun.direction", sunDirection);
    sun.setClean();

    applyAmbientLight(*sunParam.ambientLight);
}

void Renderer::applyAmbientLight(const GlobalAmbienLight& ambientLight) {
    if (!ambientLight.isDirty()) return;
    Vec3F ambientColor = ambientLight.getColor().getRGBVec3FNormalized();
    float ambientIntensity = ambientLight.getIntensity();
    Shader::setUniform("uAmbient.color", ambientColor);
    Shader::setUniform("uAmbient.intensity", ambientIntensity);
    ambientLight.setClean();
}


void Renderer::applySkybox(const Skybox& skyboxParam, const View& view, const Projection& projection) {
    skyboxParam.draw(view, projection);
}

void Renderer::applyFog(const FogData& fogParam, const Position& cameraPosition) {
    if (fogParam.fog == nullptr) return;
    Shader::setUniform("uFog.color", fogParam.fog->getColor().getRGBVec3FNormalized());
    Shader::setUniform("uFog.density", fogParam.fog->getDensity());
    Shader::setUniform("uFog.end", fogParam.fog->getEnd()+ cameraPosition.length());
}

void Renderer::applyMaterial(const Material& material) {
    //Shader::setUniform("uMaterial.diffuseIntensity",material.getDiffuseIntensity());
    //
    Shader::setUniform("uMaterial.specularColor", material.getSpecularColor().getRGBVec3FNormalized());
    Shader::setUniform("uMaterial.specularIntensity", material.getSpecularIntensity());
    //
    //Shader::setUniform("uMaterial.emissionColor",material.getEmissionColor());
    //Shader::setUniform("uMaterial.emissionIntensity",material.getEmmisionIntensity());
    //
    Shader::setUniform("uMaterial.shininess", material.getShininess());
}


void Renderer::applyTransform(const MV& MVMat, const MVP& MVPMat, const NormalMat& normalMat) {
    Shader::setUniform("uMVP", MVPMat);
    Shader::setUniform("uMV", MVMat);
    Shader::setUniform("uNormalMat", normalMat);
}

Renderer::~Renderer() {
    getGAPI().deleteContext();
}


void Renderer::renderInstances(const AdaptedInstances& adaptedInstances) {
    // Bind the VAO before drawing
    adaptedInstances.vertexArray->bind();
    getGAPI().drawTrianglesIndexedInstanced(adaptedInstances.indexBuffer->getCount(),
                                            adaptedInstances.instanceCount);
}

void Renderer::renderMesh(const AdaptedMesh& mesh) {
    // Bind the VAO before drawing
    mesh.vertexArray->bind();
    getGAPI().drawTrianglesIndexed(mesh.indexBuffer->getCount());
    drawCounter.addToCounter(1);
}


void Renderer::sendMeshData(const ColorMesh& mesh, const Material& material, const Transform::Transform& transform) {
    D_ASSERT_TRUE(!mesh.isBeingBuilt(), "Mesh is being built");

    if (mesh.getVertices().empty()) {
        Console::error("Mesh has no vertices");
        return;
    }

    RenderType renderType = mesh.getRenderType();

    if (renderType == RenderType::Static) {
        D_ASSERT_TRUE(false, "Static meshes are not supported");
        return;
    }
    if (renderType == RenderType::InstancedStatic) {
        D_ASSERT_TRUE(false, "Instanced static meshes are not supported");
        return;
    }
    if (renderType == RenderType::InstancedDynamic) {
        D_ASSERT_TRUE(false, "Instanced dynamic meshes are not supported");
        return;
    }
    if (renderType == RenderType::Dynamic) {
        adaptedMeshes.push_back(MeshAdapter::adaptMesh(mesh, material, transform));
        return;
    }
    D_ASSERT_TRUE(false, "Unknown render type");
}

void Renderer::addLightSpot(const LightSpot& light, const Transform::Transform& transform) {
    Light lightData{};
    lightData.light = &light;
    lightData.transform = &transform;
    lights.push_back(lightData);
}

void Renderer::setSun(const GlobalSun& sun, const GlobalAmbienLight& ambientLight,
                      const Transform::Transform& transform) {
    this->sun.sun = &sun;
    this->sun.ambientLight = &ambientLight;
    this->sun.transform = &transform;
}

void Renderer::setFog(const Fog& fogParam, const Transform::Transform& transform) {
    this->fog.fog = &fogParam;
    this->fog.transform = &transform;
}

void Renderer::setCamera(const CameraPerspective& cameraPerspective, const Transform::Transform& transform) {
    this->camera.camera = &cameraPerspective;
    this->camera.transform = &transform;
}
