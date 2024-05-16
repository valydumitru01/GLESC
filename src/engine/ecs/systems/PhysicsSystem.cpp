/******************************************************************************
 * @file   PhysicsSystem.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/systems/PhysicsSystem.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
using namespace GLESC::ECS;

PhysicsSystem::PhysicsSystem(Physics::PhysicsManager& physicsManager, ECSCoordinator& ecs) :
    System(ecs, "PhysicsSystem"),
    physicsManager(physicsManager) {
    addComponentRequirement<PhysicsComponent>();
    addComponentRequirement<TransformComponent>();
}

void PhysicsSystem::update() {
    for (auto const& entity : getAssociatedEntities()) {
        auto& physics = getComponent<PhysicsComponent>(entity);
        auto& transform = getComponent<TransformComponent>(entity);

        physicsManager.updatePhysics(physics.physics,physics.collider, transform.transform);
    }
}
