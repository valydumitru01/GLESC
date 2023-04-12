
#include "ecs/systems/PhysicsSystem.h"

void PhysicsSystem::update() {
    for (auto const &entity: getAssociatedEntities()) {
        auto &rigidBody = getComponent <RigidBodyComponent>(entity);
        auto &transform = getComponent <TransformComponent>(entity);
        
        transform.position += rigidBody.velocity;
        
        rigidBody.velocity += gravity;
    }
}


void PhysicsSystem::init() {
    addComponentRequirement <RigidBodyComponent>();
    addComponentRequirement <TransformComponent>();
}

