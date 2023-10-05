/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
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
        
        renderer.transformMesh(render.mesh, transform.position,
                               transform.rotation, transform.scale);
        
        renderer.renderMesh(render.mesh);
        
        // TODO: Batch rendering
    }
}

