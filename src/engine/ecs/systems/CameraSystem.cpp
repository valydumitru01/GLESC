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

CameraSystem::CameraSystem(Renderer &renderer, ECSCoordinator &ecs) :
    System(ecs, "CameraSystem"), renderer(renderer) {
    addComponentRequirement<CameraComponent>();
    addComponentRequirement<TransformComponent>();


    StatsManager::registerStatSource("Camera Data:", [&]() -> std::string {
        std::stringstream ss;
        for (auto &entity : getAssociatedEntities()) {
            auto &camera = getComponent<CameraComponent>(entity);
            // Position
            ss << "\n - Position: " << Stringer::toString(camera.viewWidth);
            // Rotation
            ss << "\n - Rotation: " << Stringer::toString(camera.viewHeight);
            // Scale
            ss << "\n - Fov: " << Stringer::toString(camera.fovDegrees);
            ss << "\n - Near plane: " << Stringer::toString(camera.nearPlane);
            ss << "\n - Far plane: " << Stringer::toString(camera.farPlane);
            ss << "\n - Aspect Ratio" << Stringer::toString(camera.viewWidth) << "\\" <<
                    Stringer::toString(camera.viewHeight) << "=" << Stringer::toString(
                        camera.viewWidth / camera.viewHeight);
        }
        if (getAssociatedEntities().empty()) {
            return "No camera found";
        }
        return ss.str();
    });
}

void CameraSystem::update() {
    // TODO: Add support for multiple cameras
    for (auto &entity : getAssociatedEntities()) {
        auto entityNumber = getAssociatedEntities().size();
        D_ASSERT_TRUE(entityNumber == 1,
                      "For now, only (and at least) one camera is supported.");
        auto &transform = getComponent<TransformComponent>(entity);
        auto &camera = getComponent<CameraComponent>(entity);
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
