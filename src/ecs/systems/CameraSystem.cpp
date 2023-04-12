#include <utility>

#include "ecs/systems/CameraSystem.h"


void CameraSystem::init() {
    addComponentRequirement <CameraComponent>();
    addComponentRequirement <TransformComponent>();
    
    // Set up the projection matrix
    // Only needs to be done once
    // Only one camera is supported at the moment
    // TODO: Support multiple cameras
    for (auto &entity: getAssociatedEntities()) {
        auto &camera = getComponent <CameraComponent>(entity);
        projection = makeProjectionMatrix(camera);
    }
}

void CameraSystem::update() {
    for (auto &entity: getAssociatedEntities()) {
        auto &transform = getComponent <TransformComponent>(entity);
        auto &camera = getComponent <CameraComponent>(entity);
        view = makeViewMatrix(transform);
        
        renderer->setProjectionMatrix(projection);
        renderer->setViewMatrix(view);
        
    }
}

glm::mat4 CameraSystem::makeProjectionMatrix(CameraComponent &camera) {
    float aspectRatio = static_cast<float>(camera.viewWidth) / static_cast<float>(camera.viewHeight);
    return glm::perspective(glm::radians(camera.fov), aspectRatio, camera.nearPlane, camera.farPlane);
}

glm::mat4 CameraSystem::makeViewMatrix(TransformComponent &transform) {
    return glm::inverse(transform.model);
}

void CameraSystem::setRenderer(shared_ptr <Renderer> &rendererParam) {
    renderer = std::move(rendererParam);
}

