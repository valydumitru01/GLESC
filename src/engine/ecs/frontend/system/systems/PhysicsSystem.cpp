/**************************************************************************************************
 * @file   PhysicsSystem.cpp
 * @author Valentin Dumitru
 * @date   09/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

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
