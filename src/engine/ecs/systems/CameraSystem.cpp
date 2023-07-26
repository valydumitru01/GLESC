#include "engine/ecs/systems/CameraSystem.h"
#include <utility>

CameraSystem::CameraSystem(Renderer &renderer) : System("CameraSystem"), renderer(renderer) {
    addComponentRequirement <CameraComponent>();
    addComponentRequirement <TransformComponent>();
}


void CameraSystem::update() {
    for (auto &entity: getAssociatedEntities()) {
        auto &transform = getComponent <TransformComponent>(entity);
        auto &camera = getComponent <CameraComponent>(entity);
        renderer.setProjection(
                renderer.calculateProjectionMatrix(camera.fov, camera.nearPlane, camera.farPlane, camera.viewWidth,
                                                   camera.viewHeight));
        renderer.setView(renderer.calculateViewMatrix(transform.position, transform.rotation, transform.scale));
    }
}
