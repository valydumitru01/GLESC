#include "engine/subsystems/renderer/Renderer.h"

#include "engine/subsystems/transform/Transform.h"
#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/math/Frustum.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
#include "engine/subsystems/renderer/lighting/LightSpot.h"

using namespace GLESC::Render;

Renderer::Renderer(WindowManager& windowManager) :
    windowManager(windowManager), shader(GAPI::Shader("Shader.glsl")),
    cameraTransform(Transform::Transform(Position(0.0f, 0.0f, 3.0f),
                                         Transform::Rotation(0.0f, 0.0f, 0.0f),
                                         Transform::Scale(1.0f, 1.0f, 1.0f))),
    view(View()), projection(Projection()),
    lightSpots(LightSpots()), globalSun(GlobalSun()), globalAmbienLight(GlobalAmbienLight()) {
    float windowWidth = static_cast<float>(windowManager.getSize().width);
    float windowHeight = static_cast<float>(windowManager.getSize().height);
    // Set the projection matrix
    projection.makeProjectionMatrix(45.0f, 0.1f, 100.0f, windowWidth, windowHeight);
    // Set the view matrix
    view.makeViewMatrixEye(cameraTransform.getPosition(),
                           cameraTransform.forward(),
                           Transform::Transform::worldUp);
    frustum = Frustum(view, projection);
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

void Renderer::applyLighting(LightSpots& lightSpots, GlobalSun& sun, GlobalAmbienLight ambientLight) const {
    // Apply lighting
    for (int i = 0; i < lightSpots.getLights().size(); i++) {
        const LightSpot& light = *lightSpots.getLights()[i].light;
        const Transform::Transform& transform = *lightSpots.getLights()[i].transform;
        std::string lightUniform = "uLightSpots.lights[" + std::to_string(i) + "]";

        shader.setUniform(lightUniform + ".lightProperties.position").u3F(transform.getPosition());
        shader.setUniform(lightUniform + ".lightProperties.color").u3F(light.color.toVec3F());
        shader.setUniform(lightUniform + ".lightProperties.intensity").u1F(light.intensity);

        shader.setUniform(lightUniform + ".radius").u1F(transform.getScale().length());
    }

    shader.setUniform("uGlobalSunLight.lightProperties.color").u3F(sun.getColor().toVec3F());
    shader.setUniform("uGlobalSunLight.lightProperties.intensity").u1F(sun.getIntensity());
    shader.setUniform("uGlobalSunLight.direction").u3F(sun.getTransform().forward());

    shader.setUniform("uGlobalAmbient.color").u3F(ambientLight.getColor().toVec3F());
    shader.setUniform("uGlobalAmbient.intensity").u1F(ambientLight.getIntensity());
}

void Renderer::applyMaterial(const Material& material) const {
    shader.bind(); // Activate the shader program

    /*
    for(const std::string& uniform: getGAPI().getAllUniforms()) {
        std::cout << uniform << std::endl;
    }
    */

    shader.setUniform("uMaterial.diffuseIntensity").u1F(material.getDiffuseIntensity());

    shader.setUniform("uMaterial.specularColor").u3F(material.getSpecularColor());
    shader.setUniform("uMaterial.specularIntensity").u1F(material.getSpecularIntensity());

    shader.setUniform("uMaterial.emissionColor").u3F(material.getEmissionColor());
    shader.setUniform("uMaterial.emissionIntensity").u1F(material.getEmmisionIntensity());

    shader.setUniform("uMaterial.shininess").u1F(material.getShininess());
}

Renderer::~Renderer() {
    getGAPI().deleteContext();
}

void Renderer::applyTransform(ColorMesh& mesh, const Transform::Transform& transform) const {
    Model model;
    model.makeModelMatrix(transform.getPosition(), transform.getRotation(), transform.getScale());

    MVP mvp = model * getView() * getProjection();

    Transform::Transformer::transformBoundingVolume(mesh.getBoundingVolumeMutable(), transform);

    shader.setUniform("uMVP").uMat4F(mvp);
}

void Renderer::transformMeshCPU(ColorMesh& mesh,
                                const Transform::Transform& transform) {
    Transform::Transformer::transformMesh(mesh, transform);
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
}

void Renderer::renderMeshes(double timeOfFrame) {
    // Don't render anything if the view matrix is not valid
    frustum.update(getView(), getProjection());
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
        //if (!frustum.intersects(mesh.getBoudingVolume())) continue;
        const Material& material = *dynamicMesh.material;
        const Transform::Transform& transform = *dynamicMesh.transform;


        if (isMeshNotCached(mesh))
            cacheMesh(mesh, MeshAdapter::adaptMesh(mesh));
        applyMaterial(material);
        applyLighting(lightSpots, globalSun, globalAmbienLight);
        applyTransform(mesh, transform);
        Console::log("Rendering dynamic mesh");
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
        transformMeshCPU(mesh, transform);
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
