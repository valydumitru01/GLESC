/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/systems/PhysicsSystem.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"

PhysicsSystem::PhysicsSystem(PhysicsManager &physicsManager, GLESC::ECS &ecs) : System(ecs, "PhysicsSystem"),
        gravity({0, 8.91, 0}), physicsManager(physicsManager){
    addComponentRequirement<PhysicsComponent>();
    addComponentRequirement<TransformComponent>();
    
    for (auto const &entity : getAssociatedEntities()) {
        auto &rigidBody = getComponent<PhysicsComponent>(entity);
        rigidBody.velocity = gravity;
    }
}

void PhysicsSystem::update() {
    for (auto const &entity : getAssociatedEntities()) {
        auto &rigidBody = getComponent<PhysicsComponent>(entity);
        auto &transform = getComponent<TransformComponent>(entity);
        
        transform.position += rigidBody.velocity;
    }
}


