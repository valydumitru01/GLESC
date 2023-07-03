
#include "ecs/systems/PhysicsSystem.h"

void PhysicsSystem::update() {
    for (auto const &entity: getAssociatedEntities()) {
        auto &rigidBody = getComponent <RigidBodyComponent>(entity);
        auto &transform = getComponent <TransformComponent>(entity);
        
        transform.position += rigidBody.velocity;
    }
}


void PhysicsSystem::init() {
    addComponentRequirement <RigidBodyComponent>();
    addComponentRequirement <TransformComponent>();
    
    for(auto const &entity: getAssociatedEntities()) {
        auto &rigidBody = getComponent <RigidBodyComponent>(entity);
        rigidBody.velocity = gravity;
    }
}

