#include "engine/ecs/systems/CameraSystem.h"
#include <utility>



void CameraSystem::init() {
    addComponentRequirement <CameraComponent>();
    addComponentRequirement <TransformComponent>();
    // TODO: Support multiple cameras
}

void CameraSystem::update() {
    for (auto &entity: getAssociatedEntities()) {
        auto &transform = getComponent <TransformComponent>(entity);
        auto &camera = getComponent <CameraComponent>(entity);
        renderer->setProjection(renderer->makeProjectionMatrix(camera.fov, camera.nearPlane, camera.farPlane, camera.viewWidth,
                                                     camera.viewHeight));
        renderer->setView(renderer->makeViewMatrix(transform.position, transform.rotation, transform.scale));
    }
}

void CameraSystem::setRenderer(shared_ptr <Renderer> &rendererParam) {
    renderer = rendererParam;
}

