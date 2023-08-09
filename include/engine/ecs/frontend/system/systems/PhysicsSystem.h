/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/System.h"
#include "engine/ecs/ECSContainer.h"
#include "engine/ecs/backend/component/components/TransformComponent.h"
#include "engine/ecs/backend/component/components/RigidBodyComponent.h"
#include "engine/subsystems/physics/PhysicsManager.h"

class PhysicsSystem : public System {
private:
    glm::vec3 gravity;
    PhysicsManager &physicsManager;
public:
    explicit PhysicsSystem(PhysicsManager &physicsManager);
    void update();
};

