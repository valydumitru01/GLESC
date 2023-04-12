#include "ecs/systems/TransformSystem.h"

void TransformSystem::init() {
    addComponentRequirement <TransformComponent>();
}

void TransformSystem::update() {
    for (EntityID entityId: getAssociatedEntities()) {
        auto &transformComponent = getComponent <TransformComponent>(entityId);
        transformComponent.model = calculateModelMatrix(transformComponent.position, transformComponent.rotation,
                                                        transformComponent.scale);
    }
}

glm::mat4
TransformSystem::calculateModelMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}

