/**************************************************************************************************
 * @file   TransformSystem.cpp
 * @author Valentin Dumitru
 * @date   2024-03-21
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/ecs/frontend/system/systems/TransformSystem.h"

#include "engine/ecs/frontend/component/TransformComponent.h"

namespace GLESC::ECS {
    TransformSystem::TransformSystem(ECSCoordinator &ecs) : System(ecs, "TransformSystem") {
        addComponentRequirement<TransformComponent>();
    }

    void TransformSystem::update() {
        for (auto &entity : getAssociatedEntities()) {
            auto &transform = getComponent<TransformComponent>(entity);
            if (transform.transform.rotation.x() > 360.0f) {
                transform.transform.rotation.x() = 0.0f;
            }
            if (transform.transform.rotation.y() > 360.0f) {
                transform.transform.rotation.y() = 0.0f;
            }
            if (transform.transform.rotation.z() > 360.0f) {
                transform.transform.rotation.z() = 0.0f;
            }

            if (transform.transform.rotation.x() < 0.0f) {
                transform.transform.rotation.x() = 360.0f;
            }
            if (transform.transform.rotation.y() < 0.0f) {
                transform.transform.rotation.y() = 360.0f;
            }
            if (transform.transform.rotation.z() < 0.0f) {
                transform.transform.rotation.z() = 360.0f;
            }
        }
    }
} // namespace GLESC::ECS
