/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/systems/CameraSystem.h"
#include <utility>

CameraSystem::CameraSystem(GLESC::Renderer &renderer) : renderer(renderer) {
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
