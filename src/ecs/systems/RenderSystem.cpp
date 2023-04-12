#include <utility>

#include "ecs/systems/RenderSystem.h"


void RenderSystem::init() {
    addComponentRequirement <TransformComponent>();
    addComponentRequirement <RenderComponent>();
}

void RenderSystem::update(const double timeOfFrame) {
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    renderer->getShaderManager().use();
    
    for (auto &entity: getAssociatedEntities()) {
        
        auto &render = getComponent <RenderComponent>(entity);
        auto &transform = getComponent <TransformComponent>(entity);
        
        // Bind the vertex array and buffer objects
        
        
        renderer->getShaderManager().setMat4("model", transform.model);
        
        bindMeshBuffers(render.mesh);
        
        render.textureID = renderer->getTextureManager().loadTexture(render.texturePath);
        
        // Set the texture uniform
        renderer->getShaderManager().setInt("texture1", static_cast<int>(render.textureID));
        
        // Draw the vertices
        GlWrapper::drawElements(render.mesh.getIndexCount());
        
        // TODO: Batch rendering
    }
    renderer->getWindowManager()->swapBuffers();
}


void RenderSystem::bindMeshBuffers(Mesh &mesh) {
    GlWrapper::bindVertexArray(mesh.VAO);
    GlWrapper::bindVertexBuffer(mesh.VBO);
    GlWrapper::bindElementBuffer(mesh.EBO);
}

void RenderSystem::setRenderer(std::shared_ptr <Renderer> &rendererParam) {
    renderer = std::move(rendererParam);
}

