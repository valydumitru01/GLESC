
#include "engine/ecs/frontend/system/systems/PhysicsCollisionSystem.h"

#include "engine/ecs/frontend/component/CollisionComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/physics/CollisionManager.h"
using namespace GLESC::ECS;

PhysicsCollisionSystem::PhysicsCollisionSystem(Physics::PhysicsManager& physicsManager,
                                               Physics::CollisionManager& collisionManager,
                                               ECSCoordinator& ecs) :
    collisionManager(collisionManager), physicsManager(physicsManager),
    System(ecs, "PhysicsCollisionSystem") {
    addComponentRequirement<PhysicsComponent>();
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<CollisionComponent>();
}

void PhysicsCollisionSystem::update() {
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

        collisionManager.checkAndUpdateColliderInformation(collision.collider,
                                                 physics.oldTransform,
                                                 transform.transform);
        if (collision.collider.getCollisionInformation().isColliding()) {
            physicsManager.handleCollisions(collision.collider, physics.physics);
            transform.transform = GLESC::Physics::PhysicsManager::updateTransform(physics.oldTransform,
                physics.physics);
        }
    }
    collisionManager.clearColliders();
}
