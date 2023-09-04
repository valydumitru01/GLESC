/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <utility>

#include "engine/ecs/frontend/system/systems/RenderSystem.h"

RenderSystem::RenderSystem(GLESC::Renderer &renderer, GLESC::ECS &ecs) :
        System(ecs, "RenderSystem"), renderer(renderer) {
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<RenderComponent>();
};


void RenderSystem::update(double timeOfFrame) {
    renderer.getShaderManager().use();
    
    for (auto &entity : getAssociatedEntities()) {
        auto &render = getComponent<RenderComponent>(entity);
        auto &transform = getComponent<TransformComponent>(entity);
        
        renderer.renderMesh(render.mesh, transform.position, transform.rotation, transform.scale);
        
        //renderer.renderTexture(render.textureID, transform.position, transform.rotation, transform.scale);
        
        //render.textureID = renderer.getTextureManager().loadTexture(render.texturePath);
        
        //renderer.getTextureManager().bindTexture(render.textureID);
        
        // Set the texture uniform
        //renderer.getShaderManager().setInt("texture1", static_cast<int>(render.textureID));
        
        // Draw the vertices
        //GlApi::drawElements(render.mesh.getIndexCount());
        
        // TODO: Batch rendering
    }
}

