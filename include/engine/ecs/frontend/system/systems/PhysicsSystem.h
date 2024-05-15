/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/physics/PhysicsManager.h"
#include "engine/subsystems/physics/PhysicsTypes.h"

namespace GLESC::ECS {
    class PhysicsSystem : public System {
    public:
        explicit PhysicsSystem(Physics::PhysicsManager& physicsManager, ECSCoordinator& ecs);
        void update() override;

    private:
        Physics::PhysicsManager& physicsManager;
    };
} // namespace GLESC::ECS
