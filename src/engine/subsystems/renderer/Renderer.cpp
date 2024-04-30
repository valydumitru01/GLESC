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
    windowManager(windowManager), shader(GAPI::Shader("Shader.glsl")),
    lightSpots(LightSpots()), globalSuns(GlobalSuns()), globalAmbienLight(GlobalAmbienLight()),
    projection(makeDefaultProjection()), view(makeDefaultView()),
    cameraTransform(Transform::Transform(Position(0.0f, 0.0f, 3.0f),
                                         Transform::Rotation(0.0f, 0.0f, 0.0f),
                                         Transform::Scale(1.0f, 1.0f, 1.0f))) {}


void Renderer::swapBuffers() const {
    getGAPI().swapBuffers(windowManager.getWindow());
}

void Renderer::clear() const {
    getGAPI().clear({
        Enums::ClearBits::Color,
        Enums::ClearBits::Depth,
        Enums::ClearBits::Stencil
    });
    getGAPI().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::renderMeshes(double timeOfFrame) {
    meshRenderCounter.startFrame();

    View viewMat = getView();
    Projection projMat = getProjection();
    VP viewProj = viewMat * projMat;

    // Don't render anything if the view matrix is not valid
    frustum.update(viewProj);

    /*
    for (const auto& batch : meshBatches.getBatches()) {
        const ColorMesh& batchedMesh = batch.second;
        if (!frustum.intersects(batchedMesh.getBoudingVolume())) continue;
        const Material& material = *batch.first;


        if (isMeshNotCached(batchedMesh))
            cacheMesh(batchedMesh, MeshAdapter::adaptMesh(batchedMesh));
        applyMaterial(material);
        renderMesh(batchedMesh);
    }
    for (const auto& instances : meshInstances.getInstances()) {
        const MeshInstanceSharedData& sharedData = instances.first;
        const ColorMesh& mesh = *sharedData.mesh;
        if (!frustum.intersects(mesh.getBoudingVolume())) continue;
        const Material& material = *sharedData.material;
        const std::vector<MeshInstanceData>& individualData = instances.second;


        if (isMeshNotCached(mesh))
            cacheMesh(mesh, MeshAdapter::adaptInstances(mesh, individualData));
        applyMaterial(material);
        renderInstances(mesh, individualData);
    }*/
    for (auto& dynamicMesh : dynamicMeshes.getDynamicMeshes()) {
        ColorMesh& mesh = *dynamicMesh.mesh;
        const Transform::Transform& transform = *dynamicMesh.transform;
        interpolationTransforms[&transform].pushTransform(transform);
        const Transform::Transform& interpolatedTransform =
            interpolationTransforms[&transform].interpolate(timeOfFrame);

        Model modelMat;
        modelMat.makeModelMatrix(
            interpolatedTransform.getPosition(), interpolatedTransform.getRotation(), interpolatedTransform.getScale());
        MV modelView = modelMat * viewMat;
        MVP modelViewProj = modelView * projMat;
        NormalMat normalMat;
        normalMat.makeNormalMatrix(modelView);


        BoundingVolume transformedBoundingVol =
            Transform::Transformer::transformBoundingVolume(mesh.getBoundingVolume(), modelMat);

        if (!frustum.contains(transformedBoundingVol)) continue;
        const Material& material = *dynamicMesh.material;

        if (isMeshNotCached(mesh))
            cacheMesh(mesh, MeshAdapter::adaptMesh(mesh));

        shader.bind(); // Activate the shader program before transform, material and lighting
        applyTransform(modelView, modelViewProj, normalMat);
        applyMaterial(material);
        applyLighting(lightSpots, globalSuns, globalAmbienLight, timeOfFrame);
        renderMesh(mesh);
    }


    skybox.draw(view, projMat);
}


void Renderer::applyLighting(const LightSpots& lightSpotsParam, const GlobalSuns& suns,
                             const GlobalAmbienLight& ambientLight, double timeOfFrame) const {

    // Apply global suns
    size_t sunCount = suns.getSuns().size();
    shader.setUniform("uGlobalSuns.count", sunCount);
    for (size_t i = 0; i < sunCount; i++) {
        const GlobalSunData& sunData = suns.getSuns()[i];
        std::string iStr = std::to_string(i);

        if (!sunData.sun->isDirty()) continue;
        shader.setUniform("uGlobalSuns.color["+iStr+"]", sunData.sun->getColor());
        shader.setUniform("uGlobalSuns.intensity["+iStr+"]", sunData.sun->getIntensity());
        shader.setUniform("uGlobalSuns.direction["+iStr+"]", sunData.sun->getDirection());
        sunData.sun->setClean();
    }

    // Apply spot lights
    size_t lightCount = static_cast<int>(lightSpotsParam.getLights().size());
    shader.setUniform("uLights.count", lightCount);
    for (size_t i = 0; i < lightCount; i++) {
        const LightSpot& light = *lightSpotsParam.getLights()[i].light;
        std::string iStr = std::to_string(i);
        const Transform::Transform& transform = *lightSpotsParam.getLights()[i].transform;
        interpolationTransforms[&transform].pushTransform(transform);
        const Transform::Transform& interpolatedTransform =
            interpolationTransforms[&transform].interpolate(timeOfFrame);

        Position lightPosViewSpace =
            Transform::Transformer::worldToCamera(interpolatedTransform.getPosition(), getView());
        shader.setUniform("uLights.posInViewSpace[" + iStr + "]", lightPosViewSpace);

        if (!light.isDirty()) continue;

        Vec3F lightColor = light.getColor().getRGBVec3FNormalized();
        float lightIntensity = light.getIntensity();
        float lightRadius = light.getRadius();
        shader.setUniform("uLights.color[" + iStr + "]", lightColor);
        shader.setUniform("uLights.intensity[" + iStr + "]", lightIntensity);

        shader.setUniform("uLights.radius[" + iStr + "]", lightRadius);
        light.setClean();
    }

    //shader.setUniform("uGlobalSunLight.lightProperties.color",sun.getColor().toVec3F());
    //shader.setUniform("uGlobalSunLight.lightProperties.intensity",sun.getIntensity());
    //shader.setUniform("uGlobalSunLight.direction",sun.getTransform().forward());
    if (ambientLight.isDirty()) {
        shader.setUniform("uAmbient.color", ambientLight.getColor().getRGBVec3FNormalized());
        shader.setUniform("uAmbient.intensity", ambientLight.getIntensity());
        ambientLight.setClean();
    }
}

void Renderer::applyMaterial(const Material& material) const {
    //shader.setUniform("uMaterial.diffuseIntensity",material.getDiffuseIntensity());
    //
    shader.setUniform("uMaterial.specularColor", material.getSpecularColor().getRGBVec3FNormalized());
    shader.setUniform("uMaterial.specularIntensity", material.getSpecularIntensity());
    //
    //shader.setUniform("uMaterial.emissionColor",material.getEmissionColor());
    //shader.setUniform("uMaterial.emissionIntensity",material.getEmmisionIntensity());
    //
    shader.setUniform("uMaterial.shininess", material.getShininess());
}

void Renderer::applyTransform(const MV& modelView, const MVP& mvp, const NormalMat& normalMat) const {
    shader.setUniform("uMVP", mvp);
    shader.setUniform("uMV", modelView);
    shader.setUniform("uNormalMat", normalMat);
}

Renderer::~Renderer() {
    getGAPI().deleteContext();
}


void Renderer::transformMeshCPU(ColorMesh& mesh,
                                const Model& modelMat) {
    Transform::Transformer::transformMesh(mesh, modelMat);
}

void Renderer::renderInstances(const ColorMesh& mesh,
                               const std::vector<MeshInstanceData>& instances) {
    AdaptedInstances& adptInstcs = adaptedInstances[&mesh];
    // Bind the VAO before drawing
    adptInstcs.vertexArray->bind();
    getGAPI().drawTrianglesIndexedInstanced(mesh.getIndices().size(), instances.size());
}

void Renderer::renderMesh(const ColorMesh& mesh) {
    AdaptedMesh& adaptedMesh = adaptedMeshes[&mesh];
    // Bind the VAO before drawing
    adaptedMesh.vertexArray->bind();
    getGAPI().drawTrianglesIndexed(adaptedMesh.indexBuffer->getCount());
    meshRenderCounter.addToCounter(1);
}


void Renderer::cacheMesh(const ColorMesh& mesh,
                         AdaptedMesh adaptedMesh) {
    adaptedMeshes[&mesh] = std::move(adaptedMesh);
    mesh.setClean();
}

void Renderer::cacheMesh(const ColorMesh& mesh,
                         AdaptedInstances adaptedInstancesParam) {
    adaptedInstances[&mesh] = std::move(adaptedInstancesParam);
    mesh.setClean();
}

bool Renderer::isMeshNotCached(const ColorMesh& mesh) const {
    return mesh.isDirty() || adaptedMeshes.find(&mesh) == adaptedMeshes.end();
}


void Renderer::addData(const Render::Material& material,
                       ColorMesh& mesh,
                       const Transform::Transform& transform) {
    if (mesh.getVertices().empty()) {
        Console::warn("Mesh has no vertices");
        return;
    }
    RenderType renderType = mesh.getRenderType();
    // We store the meshes in the appropriate data structure
    if (renderType == RenderType::Static) {
        Model modelMat;
        modelMat.makeModelMatrix(transform.getPosition(), transform.getRotation(), transform.getScale());
        transformMeshCPU(mesh, modelMat);
        meshBatches.attatchMesh(material, mesh);
    }
    else if (renderType == RenderType::InstancedStatic) {
        meshInstances.addInstance(mesh, material, transform);
    }
    else if (renderType == RenderType::InstancedDynamic) {
        // TODO: Differentiate between static and dynamic instances
        meshInstances.addInstance(mesh, material, transform);
    }
    else if (renderType == RenderType::Dynamic) {
        dynamicMeshes.addDynamicMesh(mesh, material, transform);
    }
    else {
        D_ASSERT_TRUE(false, "Unknown render type");
    }
}

void Renderer::addLight(const LightSpot& light, const Transform::Transform& transform) {
    lightSpots.addLight(light, transform);
}

void Renderer::addSun(const GlobalSun& sun, const Transform::Transform& transform) {
    globalSuns.addSun(sun, transform);
}