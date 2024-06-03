/**************************************************************************************************
 * @file   FogSystem.cpp
 * @author Valentin Dumitru
 * @date   05/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/ecs/frontend/system/systems/FogSystem.h"

#include "engine/ecs/frontend/component/FogComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/HudItemsManager.h"

namespace GLESC::ECS {
    FogSystem::FogSystem(Render::Renderer& renderer, ECSCoordinator& ecs) : System(ecs, "FogSystem"),
                                                                            renderer(renderer) {
        addComponentRequirement<FogComponent>();
        addComponentRequirement<TransformComponent>();
    }

    void FogSystem::update() {
        auto entities = getAssociatedEntities();
        D_ASSERT_TRUE(entities.size() <= 1, "For now, only one fog is supported.");
        for (auto& entity : entities) {
            auto& fog = getComponent<FogComponent>(entity);
            auto& transform = getComponent<TransformComponent>(entity);
            renderer.setFog(fog.fog, transform.transform);
            if (fogCache.find(&fog) != fogCache.end()) continue;
            HudItemsManager::addItem(HudItemType::FOG, transform.transform.getPosition());
            fogCache.insert(&fog);
        }
    }
} // namespace GLESC::ECS
