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

CameraSystem::CameraSystem(Render::Renderer& renderer, WindowManager& windowManager, ECSCoordinator& ecs) :
    System(ecs, "CameraSystem"), renderer(renderer), windowManager(windowManager) {
    addComponentRequirement<CameraComponent>();
    addComponentRequirement<TransformComponent>();
}

void CameraSystem::update() {
    auto entities = getAssociatedEntities();
    D_ASSERT_TRUE(entities.size() == 1,
                  "For now, only (and at least) one camera is supported.");
    // TODO: Add support for multiple cameras
    for (auto& entity : entities) {
        auto& transform = getComponent<TransformComponent>(entity);
        auto& camera = getComponent<CameraComponent>(entity);
        camera.perspective.setViewWidth(static_cast<float>(windowManager.getSize().width));
        camera.perspective.setViewHeight(static_cast<float>(windowManager.getSize().height));
        renderer.setCamera(camera.perspective, transform.transform);
        if (cameraCache.find(&camera) != cameraCache.end()) continue;
        // Nothing to cache for now
        cameraCache.insert(&camera);
    }
}
