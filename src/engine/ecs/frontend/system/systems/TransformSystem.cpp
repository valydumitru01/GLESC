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
    TransformSystem::TransformSystem(ECSCoordinator& ecs) : System(ecs, "TransformSystem") {
        addComponentRequirement<TransformComponent>();
    }

    void TransformSystem::update() {
        for (auto& entity : getAssociatedEntities()) {
            auto& transform = getComponent<TransformComponent>(entity);
            Transform::Rotation rotation = transform.transform.getRotation();
            // Use of fmod to avoid floating point errors
            if (rotation.getX() < -360.0f)
                transform.transform.addRotation(Transform::RotationAxis::Pitch, 720.0f);
            if (rotation.getY() < -360.0f)
                transform.transform.addRotation(Transform::RotationAxis::Yaw, 720.0f);
            if (rotation.getZ() < -360.0f)
                transform.transform.addRotation(Transform::RotationAxis::Roll, 720.0f);

            if (rotation.getX() > 360.0f)
                transform.transform.addRotation(Transform::RotationAxis::Pitch, -720.0f);
            if (rotation.getY() > 360.0f)
                transform.transform.addRotation(Transform::RotationAxis::Yaw, -720.0f);
            if (rotation.getZ() > 360.0f)
                transform.transform.addRotation(Transform::RotationAxis::Roll, -720.0f);

        }
    }
} // namespace GLESC::ECS
