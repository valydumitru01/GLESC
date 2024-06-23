/**************************************************************************************************
* @file   LightSystem.h
 * @author Valentin Dumitru
 * @date   2024-03-31
 * @brief  System that updates the collision physics of the entities
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/physics/PhysicsManager.h"
#include "engine/subsystems/physics/CollisionManager.h"

namespace GLESC::ECS {
    /**
     * @details The update of this class must be called after the update of the PhysicsSystem
     */
    class PhysicsCollisionSystem : public System {
    public:
        explicit PhysicsCollisionSystem(Physics::PhysicsManager& physicsManager,
                               Physics::CollisionManager& collisionManager,
                               ECSCoordinator& ecs);
        void update() override;

    private:
        Physics::PhysicsManager& physicsManager;
        Physics::CollisionManager& collisionManager;
    };
} // namespace GLESC::ECS
