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

}

void CameraSystem::update() {
    // TODO: Add support for multiple cameras
    for (auto &entity : getAssociatedEntities()) {
        auto entityNumber = getAssociatedEntities().size();
        D_ASSERT_TRUE(entityNumber == 1,
                      "For now, only (and at least) one camera is supported.");
        auto &transform = getComponent<TransformComponent>(entity);
        auto &camera = getComponent<CameraComponent>(entity);
        camera.perspective.viewWidth = static_cast<float>(windowManager.getSize().width);
        camera.perspective.viewHeight = static_cast<float>(windowManager.getSize().height);
        renderer.setCameraTransform(transform.transform);
        renderer.setCameraPerspective(camera.perspective);

        Render::Projection projection;
        projection.makeProjectionMatrix(camera.perspective.fovDegrees, camera.perspective.nearPlane,
                                        camera.perspective.farPlane,
                                        camera.perspective.viewWidth,
                                        camera.perspective.viewHeight);
        // TODO: Enable the renderer to work with multiple projection and view matrices
        renderer.setProjection(projection);
        Render::View view;
        view.makeViewMatrixPosRot(transform.transform.getPosition(),
                            transform.transform.getRotation());
        renderer.setView(view);
    }
}
