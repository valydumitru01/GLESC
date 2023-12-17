/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/systems/CameraSystem.h"
#include "engine/subsystems/renderer/math/RenderMath.h"

CameraSystem::CameraSystem(GLESC::Renderer &renderer, GLESC::ECS ecs) :
        System(ecs, "CameraSystem"), renderer(renderer) {
    addComponentRequirement<CameraComponent>();
    addComponentRequirement<TransformComponent>();
}


void CameraSystem::update() {
    for (auto &entity : getAssociatedEntities()) {
        auto &transform = getComponent<TransformComponent>(entity);
        auto &camera = getComponent<CameraComponent>(entity);
        auto projection = RenderMath::calculateProjectionMatrix(camera.fov, camera.nearPlane,
                                                                camera.farPlane,
                                                                camera.viewWidth,
                                                                camera.viewHeight);
        renderer.setProjection(projection);
        auto view = RenderMath::calculateViewMatrix(transform.position,
                                                    transform.rotation,
                                                    transform.scale);
        renderer.setView(view);
    }
}
