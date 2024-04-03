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

CameraSystem::CameraSystem(Render::Renderer &renderer, WindowManager &windowManager, ECSCoordinator &ecs) :
    System(ecs, "CameraSystem"), renderer(renderer), windowManager(windowManager) {
    addComponentRequirement<CameraComponent>();
    addComponentRequirement<TransformComponent>();


    StatsManager::registerStatSource("Camera Data:", [&]() -> std::string {
        std::stringstream ss;
        for (auto &entity : getAssociatedEntities()) {
            auto &camera = getComponent<CameraComponent>(entity);
            auto &transform = getComponent<TransformComponent>(entity);
            // Position
            ss << "\n - Position: " << Stringer::toString(transform.transform.getPosition());
            // Rotation
            ss << "\n - Rotation: " << Stringer::toString(transform.transform.getRotation());
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
        camera.viewWidth = static_cast<float>(windowManager.getSize().width);
        camera.viewHeight = static_cast<float>(windowManager.getSize().height);
        renderer.setCameraTransform(transform.transform);

        Render::Projection projection;
        projection.makeProjectionMatrix(camera.fovDegrees, camera.nearPlane,
                                        camera.farPlane,
                                        camera.viewWidth,
                                        camera.viewHeight);
        // TODO: Enable the renderer to work with multiple projection and view matrices
        renderer.setProjection(projection);
        Render::View view;
        view.makeViewMatrixPosRot(transform.transform.getPosition(),
                            transform.transform.getRotation());
        renderer.setView(view);
    }
}
