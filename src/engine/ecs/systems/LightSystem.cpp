/**************************************************************************************************
 * @file   LightSystem.cpp
 * @author Valentin Dumitru
 * @date   2024-03-31
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/ecs/frontend/system/systems/LightSystem.h"

#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"

namespace GLESC::ECS {
    LightSystem::LightSystem(ECSCoordinator& ecs, Render::Renderer& renderer) : System(ecs, "LightSystem"),
        renderer(renderer) {
        addComponentRequirement<LightComponent>();
        addComponentRequirement<TransformComponent>();
    }

    void LightSystem::update() {
        for (const auto& entity : getAssociatedEntities()) {
            auto& light = getComponent<LightComponent>(entity);
            auto& transform = getComponent<TransformComponent>(entity);
            renderer.addLight(light.light, transform.transform);
        }
    }
} // namespace GLESC::ECS
