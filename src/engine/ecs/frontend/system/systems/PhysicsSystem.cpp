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
    auto& entities = getAssociatedEntities();
    // TODO: Get the component array from the ecs so we don't need to iterate over the entities
    for (auto& entity : entities) {
        getComponent<PhysicsComponent>(entity).collider.setOwnerName(getEntityName(entity).c_str());
        physicsManager.addPhysics(getComponent<PhysicsComponent>(entity).collider,
                                  getComponent<PhysicsComponent>(entity).physics);
    }
    for (auto& entity : getAssociatedEntities()) {
        auto& physics = getComponent<PhysicsComponent>(entity);
        auto& transform = getComponent<TransformComponent>(entity);

        physicsManager.updatePhysics(physics.physics);
        physicsManager.checkCollisions(physics.collider, transform.transform, physics.physics);
    }
    physicsManager.clearPhysics();
}
