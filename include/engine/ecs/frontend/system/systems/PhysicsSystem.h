/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/System.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/physics/PhysicsManager.h"

class PhysicsSystem : public System {
public:
    explicit PhysicsSystem(PhysicsManager &physicsManager, GLESC::ECS &ecs);
    void update();
private:
    Vec3D gravity;
    PhysicsManager &physicsManager;
};

