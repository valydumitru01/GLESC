#include "engine/subsystems/renderer/Renderer.h"

#include "engine/subsystems/ingame-debug/Console.h"
#include "engine/subsystems/renderer/math/Frustum.h"
#include "engine/subsystems/renderer/mesh/Vertex.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"

using namespace GLESC;

Renderer::Renderer(WindowManager& windowManager) :
    windowManager(windowManager), shader(Shader("Shader.glsl")) {
    float windowWidth = static_cast<float>(windowManager.getWindowSize().width);
    float windowHeight = static_cast<float>(windowManager.getWindowSize().height);
    // Set the projection matrix
    projection.makeProjectionMatrix(45.0f, 0.1f, 100.0f, windowWidth, windowHeight);
    // Set the view matrix
    view.makeViewMatrix(Vec3D(0.0f, 0.0f, 0.0f), Vec3D(0.0f, 0.0f, 0.0f));
    frustum = Frustum(getView(), getProjection());

}

void Renderer::swapBuffers() const {
    getGAPI().swapBuffers(windowManager.getWindow());
}

void Renderer::clear() const {
    getGAPI().clear({
        GAPI::ClearBits::Color, GAPI::ClearBits::Depth,
        GAPI::ClearBits::Stencil
    });
    getGAPI().clearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::applyMaterial(const Material& material) const {
    shader.bind(); // Activate the shader program

    /*
    for(const std::string& uniform: getGAPI().getAllUniforms()) {
        std::cout << uniform << std::endl;
    }
    */

    // Set material properties as uniforms
    shader.setUniform("uAmbientColor").u3F(material.getAmbientColor());
    shader.setUniform("uAmbientIntensity").u1F(material.getAmbientIntensity());

    shader.setUniform("uDiffuseColor").u3F(material.getDiffuseColor());
    shader.setUniform("uDiffuseIntensity").u1F(material.getDiffuseIntensity());

    shader.setUniform("uSpecularColor").u3F(material.getSpecularColor());
    shader.setUniform("uSpecularIntensity").u1F(material.getSpecularIntensity());

    shader.setUniform("uEmissionColor").u3F(material.getEmissionColor());
    shader.setUniform("uEmissionIntensity").u1F(material.getEmmisionIntensity());

    shader.setUniform("uShininess").u1F(material.getShininess());
}

Renderer::~Renderer() {
    getGAPI().deleteContext();
}

void Renderer::applyTransform(ColorMesh &mesh, const Transform& transform) const {
    Mat4D model;
    model.makeModelMatrix(transform.position, transform.rotation, transform.scale);

    Mat4D mvp = getProjection() * getView() * model;

    Transformer::transformBoundingVolume(mesh.getBoundingVolumeMutable(), transform);

    shader.setUniform("uMVP").uMat4D(mvp);
}

void Renderer::transformMeshCPU(ColorMesh& mesh,
                                const Transform& transform) {
    Transformer::transformMesh(mesh, transform);
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
        const Transform& transform = *dynamicMesh.transform;


        if (isMeshNotCached(mesh))
            cacheMesh(mesh, MeshAdapter::adaptMesh(mesh));
        applyMaterial(material);
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


void Renderer::setData(const Material& material, ColorMesh& mesh,
                       const Transform& transform) {
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
