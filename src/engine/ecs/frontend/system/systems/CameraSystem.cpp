
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
    }
}
