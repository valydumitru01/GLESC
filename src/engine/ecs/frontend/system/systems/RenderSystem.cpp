/******************************************************************************
 * @file   RenderSystem.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/system/systems/RenderSystem.h"
using namespace GLESC::ECS;

RenderSystem::RenderSystem(Render::Renderer& renderer, ECSCoordinator& ecs) :
    System(ecs, "RenderSystem"), renderer(renderer) {
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<RenderComponent>();
}


void RenderSystem::update() {
    if (renderer.hasRenderBeenCalledThisFrame()) {
        renderer.clearMeshData();
        for (auto& entity : getAssociatedEntities()) {
            auto& render = getComponent<RenderComponent>(entity);
            auto& transform = getComponent<TransformComponent>(entity);
            render.getMesh().setOwnerName(getEntityName(entity).c_str());
            renderer.sendMeshData(render.getMesh(), render.getMaterial(), transform.transform);
        }
    }
}
