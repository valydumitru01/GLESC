/**************************************************************************************************
 * @file   PhysicsSystem.h
 * @author Valentin Dumitru
 * @date   09/06/2024
 * @brief  System that updates the physics of the entities
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/physics/PhysicsManager.h"

namespace GLESC::ECS {
    class PhysicsSystem : public System {
    public:
        explicit PhysicsSystem(Physics::PhysicsManager& physicsManager,
                               ECSCoordinator& ecs);
        void update() override;

    private:
        Physics::PhysicsManager& physicsManager;
    };
} // namespace GLESC::ECS
