/******************************************************************************
 * @file   RenderSystem.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/system/systems/RenderSystem.h"
using namespace GLESC::ECS;

RenderSystem::RenderSystem(Renderer& renderer, ECSCoordinator& ecs) :
    System(ecs, "RenderSystem"), renderer(renderer) {
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<RenderComponent>();
};


void RenderSystem::update() {
    for (auto& entity : getAssociatedEntities()) {
        auto& render = getComponent<RenderComponent>(entity);

        auto& transform = getComponent<TransformComponent>(entity);

        renderer.setData(render.material, render.mesh, transform.transform);
    }
}
