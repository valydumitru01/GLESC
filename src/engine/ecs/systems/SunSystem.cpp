/**************************************************************************************************
 * @file   SunSystem.cpp
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/ecs/frontend/system/systems/SunSystem.h"

#include "engine/ecs/frontend/component/SunComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/HudItemsManager.h"

namespace GLESC::ECS {
    SunSystem::SunSystem(Render::Renderer& renderer, ECSCoordinator& ecs) :
            System(ecs, "SunSystem"), renderer(renderer) {
        addComponentRequirement<SunComponent>();
        addComponentRequirement<TransformComponent>();
    };

    void SunSystem::update() {
        for (auto& entity : getAssociatedEntities()) {
            auto& sun = getComponent<SunComponent>(entity);
            auto& transform = getComponent<TransformComponent>(entity);
            renderer.addSun(sun.sun, transform.transform);
            HudItemsManager::addItem(HudItemType::SUN, transform.transform.getPosition());
        }
    }
} // namespace GLESC::ECS
