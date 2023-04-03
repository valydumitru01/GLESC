#include "ecs/systems/CameraSystem.h"

CameraSystem::CameraSystem() : view{}, projection{} {
    addComponentRequirement <CameraComponent>();
    addComponentRequirement <TransformComponent>();
}

void CameraSystem::update() {
    for (auto &entity: getAssociatedEntities()) {
        auto &transform = getComponent <TransformComponent>(entity);
        auto &camera = getComponent <CameraComponent>(entity);
        projection = makeProjectionMatrix(camera);
        view = makeViewMatrix(transform);
        
    }
}

glm::mat4 CameraSystem::makeProjectionMatrix(CameraComponent &camera) {
    float aspectRatio = static_cast<float>(camera.viewWidth) / static_cast<float>(camera.viewHeight);
    return glm::perspective(glm::radians(camera.fov), aspectRatio, camera.nearPlane, camera.farPlane);
}

glm::mat4 CameraSystem::makeViewMatrix(TransformComponent &transform) {
    glm::vec3 eye = transform.position;
    glm::vec3 center = transform.position + transform.rotation;
    glm::vec3 up = glm::vec3(0.0F, 1.0F, 0.0F);
    return glm::lookAt(eye, center, up);
    
}