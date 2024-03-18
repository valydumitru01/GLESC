/******************************************************************************
 * @file   CameraSystem.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/system/systems/CameraSystem.h"
#include "engine/subsystems/ingame-debug/StatsManager.h"
using namespace GLESC::ECS;

CameraSystem::CameraSystem(Renderer& renderer, ECSCoordinator& ecs) :
    System(ecs, "CameraSystem"), renderer(renderer) {
    addComponentRequirement<CameraComponent>();
    addComponentRequirement<TransformComponent>();

    StatsManager::registerStatSource("Camera position", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& transform = getComponent<TransformComponent>(entity);
            Stringer::setFloatPrecision(2);
            return Stringer::toString(transform.transform.position);
        }
        return "No camera found";
    });

    StatsManager::registerStatSource("Camera rotation", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& transform = getComponent<TransformComponent>(entity);
            Stringer::setFloatPrecision(2);
            return Stringer::toString(transform.transform.rotation);
        }
        return "No camera found";
    });

    StatsManager::registerStatSource("Camera fov", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& camera = getComponent<CameraComponent>(entity);
            return Stringer::toString(camera.fovDegrees);
        }
        return "No camera found";
    });

    StatsManager::registerStatSource("Camera near plane", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& camera = getComponent<CameraComponent>(entity);
            return Stringer::toString(camera.nearPlane);
        }
        return "No camera found";
    });

    StatsManager::registerStatSource("Camera far plane", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& camera = getComponent<CameraComponent>(entity);
            return Stringer::toString(camera.farPlane);
        }
        return "No camera found";
    });

    StatsManager::registerStatSource("Camera view width", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& camera = getComponent<CameraComponent>(entity);
            return Stringer::toString(camera.viewWidth);
        }
        return "No camera found";
    });

    StatsManager::registerStatSource("Camera view height", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& camera = getComponent<CameraComponent>(entity);
            return Stringer::toString(camera.viewHeight);
        }
        return "No camera found";
    });

    StatsManager::registerStatSource("Camera aspect ratio", [&]() -> std::string {
        for (auto& entity : getAssociatedEntities()) {
            auto& camera = getComponent<CameraComponent>(entity);
            return Stringer::toString(camera.viewWidth / camera.viewHeight);
        }
        return "No camera found";
    });
}

void CameraSystem::update() {
    // TODO: Add support for multiple cameras
    for (auto& entity : getAssociatedEntities()) {
        auto entityNumber = getAssociatedEntities().size();
        D_ASSERT_TRUE(entityNumber == 1,
                      "For now, only (and at least) one camera is supported.");
        auto& transform = getComponent<TransformComponent>(entity);
        auto& camera = getComponent<CameraComponent>(entity);
        Mat4D projection;
        projection.makeProjectionMatrix(Math::radians(camera.fovDegrees), camera.nearPlane,
                                        camera.farPlane,
                                        camera.viewWidth,
                                        camera.viewHeight);
        // TODO: Enable the renderer to work with multiple projection and view matrices
        renderer.setProjection(projection);
        Mat4D view;
        view.makeViewMatrix(transform.transform.position, transform.transform.rotation);
        renderer.setView(view);
    }
}
