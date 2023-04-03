#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ecs/systems/System.h"
#include "ecs/components/TransformComponent.h"

class TransformSystem : System {
public:
    TransformSystem();

    void update();

};

TransformSystem::TransformSystem() {
    addComponentRequirement<TransformComponent>();
}

void TransformSystem::update() {
    for (EntityID entityId: getAssociatedEntities()) {
        auto &transformComponent = getComponent<TransformComponent>(entityId);

    }
}