#include "engine/ecs/frontend/system/systems/LightSystem.h"

#include "engine/ecs/frontend/component/LightComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/subsystems/ingame-debug/HudItemsManager.h"

namespace GLESC::ECS {
    LightSystem::LightSystem(ECSCoordinator& ecs, Render::Renderer& renderer) : System(ecs, "LightSystem"),
        renderer(renderer) {
        addComponentRequirement<LightComponent>();
        addComponentRequirement<TransformComponent>();
    }

    void LightSystem::update() {
        if (renderer.hasRenderBeenCalledThisFrame()) {
            renderer.clearLightData();
            for (const auto& entity : getAssociatedEntities()) {
                auto& light = getComponent<LightComponent>(entity);
                auto& transform = getComponent<TransformComponent>(entity);
                renderer.sendLightPoint(light.light, transform.transform);
                HudItemsManager::addItem(HudItemType::LIGHT_SPOT, transform.transform.getPosition());
            }
        }
    }
} // namespace GLESC::ECS
