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


Projection makeDefaultProjection() {
    Projection proj;
    proj.makeProjectionMatrix(45.0f, 0.1f, 1000.0f, 800.0f, 600.0f);
    return proj;
}

View makeDefaultView() {
    View view;
    view.makeViewMatrixPosRot(GLESC::Transform::Position(0.0f, 0.0f, 3.0f),
                              GLESC::Transform::Rotation(0.0f, 0.0f, 0.0f));
    return view;
}


Renderer::Renderer(WindowManager& windowManager) :
    windowManager(windowManager), shader(Shader("Shader.glsl")),
    projection(makeDefaultProjection()), view(makeDefaultView()), frustum(projection * view) {
}


void Renderer::swapBuffers() const {
    getGAPI().swapBuffers(windowManager.getWindow());
}

void Renderer::clear() {
    getGAPI().clear({
        Enums::ClearBits::Color,
        Enums::ClearBits::Depth,
        Enums::ClearBits::Stencil
    });
    getGAPI().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
}


void Renderer::renderMeshes(double timeOfFrame) {
    drawCounter.startFrame();

    View viewMat = getView();
    Projection projMat = getProjection();
    VP viewProj = viewMat * projMat;

    // Don't render anything if the view matrix is not valid
    frustum.update(viewProj);


    for (auto& dynamicMesh : adaptedBatches) {
        NormalMat normalMat;
        normalMat.makeNormalMatrix(modelView);


        if (!frustum.contains(*dynamicMesh.boundingVolume)) continue;
        const Material& material = *dynamicMesh.material;

        shader.bind(); // Activate the shader program before transform, material and lighting
        applyTransform(view, viewProj, normalMat);
        applyMaterial(material);
        applyLighSpots(lights, timeOfFrame);
        renderMesh(dynamicMesh);
    }
}


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
            Transform::Transformer::worldToCamera(interpolatedTransform.getPosition(), getView());
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

void Renderer::applySun(const GlobalSun& sun) {
    if (!sun.isDirty()) return;
    Vec3F sunColor = sun.getColor().getRGBVec3FNormalized();
    float sunIntensity = sun.getIntensity();
    Math::Direction sunDirection = sun.getDirection();
    Shader::setUniform("uGlobalSuns.color", sunColor);
    Shader::setUniform("uGlobalSuns.intensity", sunIntensity);
    Shader::setUniform("uGlobalSuns.direction", sunDirection);
    sun.setClean();
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

void Renderer::applyFog(const FogData& fogParam) {
    Shader::setUniform("uFog.color", Vec3F(fogParam.fog->getColor()));
    Shader::setUniform("uFog.density", fogParam.fog->getDensity());
    Shader::setUniform("uFog.near", fogParam.fog->getStart());
    Shader::setUniform("uFog.far", fogParam.fog->getEnd());
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


void Renderer::applyTransform(const View& view, const VP& vp, const NormalMat& normalMat) {
    Shader::setUniform("uVP", vp);
    Shader::setUniform("uView", view);
    Shader::setUniform("uNormalMat", normalMat);
}

Renderer::~Renderer() {
    getGAPI().deleteContext();
}

void Renderer::attatchMeshToBatch(ColorMesh& batch, ColorMesh& mesh, const Transform::Transform& transform) {
    Transform::Transformer::transformMesh(mesh, transform.getModelMatrix());
    BoundingVolume transformedBoundingVol =
            Transform::Transformer::transformBoundingVolume(mesh.getBoundingVolume(), transform.getModelMatrix());

    if (!frustum.contains(transformedBoundingVol)) return;
    batch.attatchMesh(mesh);
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


void Renderer::sendMeshData(const Material& material,
                        ColorMesh& mesh) {
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
        adaptedBatches.push_back(MeshAdapter::adaptMesh(mesh, mesh.getBoundingVolume(), material));
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