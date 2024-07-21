#include <omp.h>
#include "engine/subsystems/renderer/Renderer.h"

#include "engine/subsystems/transform/Transform.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/math/Frustum.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
#include "engine/subsystems/renderer/lighting/LightPoint.h"

using namespace GLESC::Render;


Counter Renderer::drawCounter{};
constexpr int reservedSize = 100;

Renderer::Renderer(WindowManager& windowManager) :
    windowManager(windowManager), shader(Shader("Shader.glsl")),
    camera(),
    projection(createProjectionMatrix(CameraPerspective())),
    view(createViewMatrix(Transform::Transform())),
    viewProjection(projection * view),
    //skybox("sea-day", "jpg"),
    frustum(viewProjection) {
    camera.camera = &defaultCameraPerspective;
    camera.transform = &defaultCameraTransform;

    meshesToRender.reserve(reservedSize);
    meshMaterials.reserve(reservedSize);
    meshTransforms.reserve(reservedSize);
    lights.reserve(reservedSize);
    lightTransforms.reserve(reservedSize);
    interpolationTransforms.reserve(reservedSize);
    mvs.reserve(reservedSize);
    mvps.reserve(reservedSize);
    normalMats.reserve(reservedSize);
    isContainedInFrustum.reserve(reservedSize);
}

// =====================================================================================================================
// =========================================Private methods (Rendering methods)=========================================
// =====================================================================================================================
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
    view.makeViewMatrixPosRot(transform.getPosition(), transform.getRotation().toRads());
    return view;
}


void Renderer::swapBuffers() const {
    getGAPI().swapBuffers(windowManager.getWindow());
}

void Renderer::start(const double timeOfFrame) {
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

    const Transform::Transform interpolatedTransform =
        interpolationTransforms[camera.transform].interpolate(static_cast<float>(timeOfFrame));
    View view;
    view.makeViewMatrixPosRot(interpolatedTransform.getPosition(), interpolatedTransform.getRotation().toRads());
    this->setView(view);

    viewProjection = projection * view;
}

void Renderer::renderLights(const std::vector<const LightPoint*>& lights,
                            const std::vector<const Transform::Transform*>& lightTransforms,
                            const double timeOfFrame) const {
    size_t lightCount = static_cast<int>(lights.size());
    Shader::setUniform("uLights.count", lightCount);
    for (size_t lightIndex = 0; lightIndex < lightCount; lightIndex++) {
        const LightPoint& light = *lights[lightIndex];
        std::string iStr = std::to_string(lightIndex);
        const Transform::Transform& transform = *lightTransforms[lightIndex];
        const Transform::Transform& interpolatedTransform =
            interpolationTransforms.at(&transform).interpolate(static_cast<float>(timeOfFrame));

        Position lightPosViewSpace =
            Transform::Transformer::transformVector(interpolatedTransform.getPosition(), getView());
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
    Shader::setUniform("uSunDirection", sunDirection);
    sun.setClean();

    applyAmbientLight(*sunParam.ambientLight);
}

void Renderer::applyAmbientLight(const GlobalAmbientLight& ambientLight) {
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
    Shader::setUniform("uFog.end", fogParam.fog->getEnd());
}

void Renderer::applyMaterial(const Material& material) {
    Shader::setUniform("uMaterial.diffuseIntensity",material.getDiffuseIntensity());
    Shader::setUniform("uMaterial.specularColor", material.getSpecularColor().getRGBVec3FNormalized());
    Shader::setUniform("uMaterial.specularIntensity", material.getSpecularIntensity());
    Shader::setUniform("uMaterial.emissionColor",material.getEmissionColor().getRGBVec3FNormalized());
    Shader::setUniform("uMaterial.emissionIntensity",material.getEmissionIntensity());
    Shader::setUniform("uMaterial.shininess", material.getShininess());
}

void Renderer::applyTransform(const MV& MVMat, const MVP& MVPMat, const NormalMat& normalMat, const View& view) {
    Shader::setUniform("uMVP", MVPMat);
    Shader::setUniform("uMV", MVMat);
    Shader::setUniform("uViewMat", view);
    Shader::setUniform("uNormalMat", normalMat);
}

void Renderer::render(double timeOfFrame) {
    drawCounter.startCounter();
    const View& viewMat = getView();
    const Projection& projMat = getProjection();
    const VP& viewProjMat = getViewProjection();
    shader.bind(); // Activate the shader program before transform, material and lighting setup
    frustum.update(viewProjMat);

    // TODO: Fix parallelization, it is not working, flickering is happening and meshes get swapped
    //#pragma omp parallel for default(shared) schedule(dynamic)
    for (int meshIndex = 0; meshIndex < meshesToRender.size(); meshIndex++) {
        const ColorMesh& mesh = *meshesToRender[meshIndex];
        const Transform::Transform& transform = *meshTransforms[meshIndex];
        Transform::Transform interpolatedTransform =
            interpolationTransforms[&transform].interpolate(static_cast<float>(timeOfFrame));

        Model model = interpolatedTransform.getModelMatrix();

        Math::BoundingVolume transformedBoundingVol =
            Transform::Transformer::transformBoundingVolume(mesh.getBoundingVolume(), interpolatedTransform);
        {
            std::lock_guard lockMutex(frustumMutex);
            isContainedInFrustum.push_back(frustum.contains(transformedBoundingVol));
        }
        MVP MVPMat = viewProjMat * model;
        MV MV = viewMat * model;
        NormalMat normalMat;
        normalMat.makeNormalMatrix(MV);
        {
            std::lock_guard lockMVP(mvpMutex);
            mvs.push_back(MV);
        }
        {
            std::lock_guard lockMV(mvMutex);
            mvps.push_back(MVPMat);
        }
        {
            std::lock_guard lockNormalMat(normalMatMutex);
            normalMats.push_back(normalMat);
        }
    }
    renderLights(lights, lightTransforms, timeOfFrame);
    applySun(sun);
    applyFog(fog, camera.transform->getPosition());

    std::string renderedMeshesPtr;
    for (int i = 0; i < meshesToRender.size(); i++) {
        if (!isContainedInFrustum[i]) continue;
        const ColorMesh& mesh = *meshesToRender[i];
        const Material& material = *meshMaterials[i];
        applyTransform(mvs[i], mvps[i], normalMats[i], viewMat);
        applyMaterial(material);
        mesh.sendToGpuBuffers();
        renderMesh(mesh);
        renderedMeshesPtr += std::to_string(i) + " ";
    }

    applySkybox(skybox, viewMat, projMat);
    hasRenderBeenCalled = true;
}

void Renderer::clearMeshData() {
    meshesToRender.clear();
    meshMaterials.clear();
    meshTransforms.clear();
    instances.clear();
    mvs.clear();
    mvps.clear();
    normalMats.clear();
    isContainedInFrustum.clear();
}

void Renderer::clearLightData() {
    lights.clear();
    lightTransforms.clear();
}


Renderer::~Renderer() {
    getGAPI().deleteContext();
}


void Renderer::renderMesh(const ColorMesh& mesh) {
    // Bind the VAO before drawing
    mesh.getVertexArray().bind();
    getGAPI().drawTrianglesIndexed(mesh.getIndexBuffer().getCount());
    drawCounter.addToCounter(1);
}

void Renderer::renderInstances(MeshIndex adaptedInstances) {
}

// =====================================================================================================================
// ===========================================Public methods (Update methods)===========================================
// =====================================================================================================================

void Renderer::sendMeshData(const ColorMesh& mesh, const Material& material, const Transform::Transform& transform) {
    D_ASSERT_TRUE(!mesh.isBeingBuilt(), "Mesh is being built");

    RenderType renderType = mesh.getRenderType();
    interpolationTransforms[&transform].pushTransform(transform);

    if (mesh.getVertices().empty()) {
        Console::warn("Mesh has no vertices");
        return;
    }

    if (renderType == RenderType::SingleDrawStatic) {
        D_ASSERT_TRUE(false, "Static meshes are not supported");
        return;
    }
    if (renderType == RenderType::InstancedStatic) {
        D_ASSERT_TRUE(false, "Instanced static meshes are not supported");
        return;
    }
    if (renderType == RenderType::InstancedDynamic) {
        meshesToRender.push_back(&mesh);
        meshMaterials.push_back(&material);
        meshTransforms.push_back(&transform);
        instances[&mesh].push_back(meshTransforms.size());
        return;
    }
    if (renderType == RenderType::SingleDrawDynamic) {
        meshesToRender.push_back(&mesh);
        meshMaterials.push_back(&material);
        meshTransforms.push_back(&transform);
        return;
    }
    D_ASSERT_TRUE(false, "Unknown render type");
}


void Renderer::sendLightPoint(const LightPoint& light, const Transform::Transform& transform) {
    this->lightTransforms.push_back(&transform);
    this->lights.push_back(&light);
    this->interpolationTransforms[&transform].pushTransform(transform);
}

void Renderer::setSun(const GlobalSun& sun, const GlobalAmbientLight& ambientLight,
                      const Transform::Transform& transform) {
    this->sun.sun = &sun;
    this->sun.ambientLight = &ambientLight;
    this->sun.transform = &transform;
    this->interpolationTransforms[&transform].pushTransform(transform);
}

void Renderer::setFog(const Fog& fogParam, const Transform::Transform& transform) {
    this->fog.fog = &fogParam;
    this->fog.transform = &transform;
    this->interpolationTransforms[&transform].pushTransform(transform);
}

void Renderer::setCamera(const CameraPerspective& cameraPerspective, const Transform::Transform& transform) {
    this->camera.camera = &cameraPerspective;
    this->camera.transform = &transform;
    this->interpolationTransforms[&transform].pushTransform(transform);
}


void Renderer::remove(const ColorMesh& mesh, const Transform::Transform& transform) {
    interpolationTransforms.erase(&transform);
}
