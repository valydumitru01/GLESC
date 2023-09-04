/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/System.h"
#include "engine/ecs/backend/component/components/TransformComponent.h"
#include "engine/subsystems/physics/PhysicsManager.h"

class PhysicsSystem : public System {
public:
    explicit PhysicsSystem(PhysicsManager &physicsManager, GLESC::ECS &ecs);
    void update();
private:
    glm::vec3 gravity;
    PhysicsManager &physicsManager;
};

