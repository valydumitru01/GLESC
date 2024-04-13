#include "engine/subsystems/renderer/Renderer.h"

#include "engine/subsystems/transform/Transform.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/math/Frustum.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
#include "engine/subsystems/renderer/lighting/LightSpot.h"

using namespace GLESC::Render;

Renderer::Renderer(WindowManager& windowManager) :
    windowManager(windowManager), shader(GAPI::Shader("Shader.glsl")),
    lightSpots(LightSpots()), globalSun(GlobalSun()), globalAmbienLight(GlobalAmbienLight()),
    projection(Projection()), view(View()),
    cameraTransform(Transform::Transform(Position(0.0f, 0.0f, 3.0f),
                                         Transform::Rotation(0.0f, 0.0f, 0.0f),
                                         Transform::Scale(1.0f, 1.0f, 1.0f))) {

}

void Renderer::swapBuffers() const {
    getGAPI().swapBuffers(windowManager.getWindow());
}

void Renderer::clear() const {
    getGAPI().clear({
        GAPI::Enums::ClearBits::Color, GAPI::Enums::ClearBits::Depth,
        GAPI::Enums::ClearBits::Stencil
    });
    getGAPI().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::applyLighting(LightSpots& lightSpotsParam, GlobalSun& sun, GlobalAmbienLight ambientLight) const {
    // Apply lighting
    shader.setUniform("uSpotLights.count").u1I(static_cast<int>(lightSpotsParam.getLights().size()));
    for (size_t i = 0; i < lightSpotsParam.getLights().size(); i++) {
        const LightSpot& light = *lightSpotsParam.getLights()[i].light;
        const Transform::Transform& transform = *lightSpotsParam.getLights()[i].transform;
        std::string lightUniform = "uSpotLights.lights[" + std::to_string(i) + "]";

        Vec4F lightPosViewSpace = getView() * transform.getPosition().homogenize();
        Vec3F lightPosViewSpace3 = lightPosViewSpace.dehomogenize();
        Vec3F lightColor = light.color.getRGBVec3FNormalized();
        float lightIntensity = light.intensity;
        shader.setUniform(lightUniform + ".lightProperties.posInViewSpace").u3F(lightPosViewSpace3);
        shader.setUniform(lightUniform + ".lightProperties.color").u3F(lightColor);
        shader.setUniform(lightUniform + ".lightProperties.intensity").u1F(lightIntensity);

        //shader.setUniform(lightUniform + ".radius").u1F(transform.getScale().length());
    }

    //shader.setUniform("uGlobalSunLight.lightProperties.color").u3F(sun.getColor().toVec3F());
    //shader.setUniform("uGlobalSunLight.lightProperties.intensity").u1F(sun.getIntensity());
    //shader.setUniform("uGlobalSunLight.direction").u3F(sun.getTransform().forward());

    shader.setUniform("uAmbient.color").u3F(ambientLight.getColor().getRGBVec3FNormalized());
    shader.setUniform("uAmbient.intensity").u1F(ambientLight.getIntensity());
}

void Renderer::applyMaterial(const Material& material) const {
    /*
    for(const std::string& uniform: getGAPI().getAllUniforms()) {
        std::cout << uniform << std::endl;
    }
    */

    //shader.setUniform("uMaterial.diffuseIntensity").u1F(material.getDiffuseIntensity());
    //
    shader.setUniform("uMaterial.specularColor").u3F(material.getSpecularColor().getRGBVec3FNormalized());
    shader.setUniform("uMaterial.specularIntensity").u1F(material.getSpecularIntensity());
    //
    //shader.setUniform("uMaterial.emissionColor").u3F(material.getEmissionColor());
    //shader.setUniform("uMaterial.emissionIntensity").u1F(material.getEmmisionIntensity());
    //
    shader.setUniform("uMaterial.shininess").u1F(material.getShininess());
}

void Renderer::applyTransform(const MV& modelView, const MVP& mvp, const NormalMat& normalMat) const {
    shader.setUniform("uMVP").uMat4F(mvp);
    shader.setUniform("uMV").uMat4F(modelView);
    shader.setUniform("uNormalMat").uMat3F(normalMat);
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

void Renderer::renderMeshes(double timeOfFrame) {
    meshRenderCounter.startFrame();

    View viewMat = getView();
    Projection projMat = getProjection();

    // Don't render anything if the view matrix is not valid
    frustum.update(viewMat * projMat);

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

        Model modelMat;
        modelMat.makeModelMatrix(transform.getPosition(), transform.getRotation(), transform.getScale());
        MV modelView = modelMat * viewMat;
        MVP modelViewProj = modelView * projMat;
        NormalMat normalMat;
        normalMat.makeNormalMatrix(modelView);
        // IMPORTANT! We need to transpose the matrix for in-cpu transformation.
        // In the cpu we're using row-major matrices while in gpu we're using column-major matrices
        BoundingVolume transformedBoundingVol =
            Transform::Transformer::transformBoundingVolume(mesh.getBoundingVolumeMutable(), modelMat.transpose());

        if (!frustum.contains(transformedBoundingVol)) continue;
        const Material& material = *dynamicMesh.material;

        if (isMeshNotCached(mesh))
            cacheMesh(mesh, MeshAdapter::adaptMesh(mesh));

        shader.bind(); // Activate the shader program before transform, material and lighting
        applyTransform(modelView, modelViewProj, normalMat);
        applyMaterial(material);
        applyLighting(lightSpots, globalSun, globalAmbienLight);
        renderMesh(mesh);
    }
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
