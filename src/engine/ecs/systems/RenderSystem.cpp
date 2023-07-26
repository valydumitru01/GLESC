#include <utility>

#include "engine/ecs/systems/RenderSystem.h"


void RenderSystem::init() {
    addComponentRequirement <TransformComponent>();
    addComponentRequirement <RenderComponent>();
    // TODO: Initialize the meshes and textures
}

void RenderSystem::update(const double timeOfFrame) {
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    renderer->getShaderManager().use();
    
    for (auto &entity: getAssociatedEntities()) {
        auto &render = getComponent <RenderComponent>(s entity);
        auto &transform = getComponent <TransformComponent>(entity);
        
        renderer->renderMesh(render.mesh, transform.position, transform.rotation, transform.scale);
        
        renderer->renderTexture(render.textureID, transform.position, transform.rotation, transform.scale);
        
        render.textureID = renderer->getTextureManager().loadTexture(render.texturePath);
        
        renderer->getTextureManager().bindTexture(render.textureID);
        
        // Set the texture uniform
        renderer->getShaderManager().setInt("texture1", static_cast<int>(render.textureID));
        
        // Draw the vertices
        GlApi::drawElements(render.mesh.getIndexCount());
        
        // TODO: Batch rendering
    }
    renderer->swapBuffers();
}



void RenderSystem::bindMeshBuffers(Mesh &mesh) {
    GlApi::bindVertexArray(mesh.VAO);
    GlApi::bindVertexBuffer(mesh.VBO);
    GlApi::bindElementBuffer(mesh.EBO);
}

void RenderSystem::setRenderer(std::shared_ptr <Renderer> &rendererParam) {
    renderer = rendererParam;
}

