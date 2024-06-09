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

#include "engine/ecs/frontend/component/CollisionComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/physics/CollisionManager.h"
using namespace GLESC::ECS;

PhysicsSystem::PhysicsSystem(Physics::PhysicsManager& physicsManager,
                             Physics::CollisionManager& collisionManager,
                             ECSCoordinator& ecs) :
    collisionManager(collisionManager), physicsManager(physicsManager),
    System(ecs, "PhysicsSystem") {
    addComponentRequirement<PhysicsComponent>();
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<CollisionComponent>();
}

void PhysicsSystem::update() {
    auto& entities = getAssociatedEntities();
    // TODO: Get the component array from the ecs so we don't need to iterate over the entities
    for (auto& entity : entities) {
        getComponent<CollisionComponent>(entity).collider.setOwnerName(getEntityName(entity).c_str());
        getComponent<PhysicsComponent>(entity).physics.setOwnerName(getEntityName(entity).c_str());
        collisionManager.addCollider(getComponent<CollisionComponent>(entity).collider,
                                     getComponent<PhysicsComponent>(entity).physics,
                                     getComponent<TransformComponent>(entity).transform);
    }
    for (auto& entity : entities) {
        auto& physics = getComponent<PhysicsComponent>(entity);
        auto& collision = getComponent<CollisionComponent>(entity);
        auto& transform = getComponent<TransformComponent>(entity);

        physicsManager.applyForces(physics.physics);
        Transform::Transform hypNextFrameTransform =
            GLESC::Physics::PhysicsManager::updateTransform(transform.transform, physics.physics);
        collisionManager.checkAndUpdateColliders(collision.collider,
                                                 transform.transform,
                                                 hypNextFrameTransform);
        if (collision.collider.getCollisionInformation().isColliding()) {
            physicsManager.handleCollisions(collision.collider, physics.physics);
            transform.transform = GLESC::Physics::PhysicsManager::updateTransform(transform.transform, physics.physics);
        } else {
            transform.transform = hypNextFrameTransform;
        }
    }
    collisionManager.clearColliders();
}
