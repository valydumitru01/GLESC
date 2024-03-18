/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/ecs/frontend/system/System.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/physics/PhysicsManager.h"

namespace GLESC::ECS {
    class PhysicsSystem : public System {
    public:
        explicit PhysicsSystem(PhysicsManager& physicsManager, ECSCoordinator& ecs);
        void update();

    private:
        Vec3D gravity;
        PhysicsManager& physicsManager;
    };
} // namespace GLESC::ECS
