
#include "engine/ecs/frontend/system/systems/PhysicsSystem.h"

#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"


using namespace GLESC::ECS;

PhysicsSystem::PhysicsSystem(Physics::PhysicsManager& physicsManager,
                             ECSCoordinator& ecs) : physicsManager(physicsManager),
    System(ecs, "PhysicsSystem") {
 addComponentRequirement<PhysicsComponent>();
 addComponentRequirement<TransformComponent>();
}


void PhysicsSystem::update() {
    auto& entities = getAssociatedEntities();
    for (auto& entity : entities) {
        auto& physics = getComponent<PhysicsComponent>(entity);
        auto& transform = getComponent<TransformComponent>(entity);
        physics.oldTransform = transform.transform;
        physicsManager.applyForces(physics.physics);
        transform.transform =
            GLESC::Physics::PhysicsManager::updateTransform(transform.transform, physics.physics);

    }

}
