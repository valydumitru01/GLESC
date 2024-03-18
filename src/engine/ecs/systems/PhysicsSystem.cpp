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
using namespace GLESC::ECS;

PhysicsSystem::PhysicsSystem(PhysicsManager& physicsManager, ECSCoordinator& ecs) :
    System(ecs, "PhysicsSystem"), gravity(0.f, 8.91f, 0.f),
    physicsManager(physicsManager) {
    addComponentRequirement<PhysicsComponent>();
    addComponentRequirement<TransformComponent>();

    for (auto const& entity : getAssociatedEntities()) {
        auto& rigidBody = getComponent<PhysicsComponent>(entity);
        rigidBody.velocity = gravity;
    }
}

void PhysicsSystem::update() {
    for (auto const& entity : getAssociatedEntities()) {
        auto& rigidBody = getComponent<PhysicsComponent>(entity);
        auto& transform = getComponent<TransformComponent>(entity);

        transform.transform.position += rigidBody.velocity;
    }
}
