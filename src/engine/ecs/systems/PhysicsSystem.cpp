/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/systems/PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(PhysicsManager &physicsManager) :
        gravity({0, 8.91, 0}), physicsManager(physicsManager) {
    addComponentRequirement<RigidBodyComponent>();
    addComponentRequirement<TransformComponent>();
    
    for (auto const &entity : getAssociatedEntities()) {
        auto &rigidBody = getComponent<RigidBodyComponent>(entity);
        rigidBody.velocity = gravity;
    }
}

void PhysicsSystem::update() {
    for (auto const &entity : getAssociatedEntities()) {
        auto &rigidBody = getComponent<RigidBodyComponent>(entity);
        auto &transform = getComponent<TransformComponent>(entity);
        
        transform.position += rigidBody.velocity;
    }
}


