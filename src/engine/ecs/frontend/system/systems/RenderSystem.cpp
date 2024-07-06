
#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/system/systems/RenderSystem.h"
using namespace GLESC::ECS;

RenderSystem::RenderSystem(Render::Renderer& renderer, ECSCoordinator& ecs) :
    System(ecs, "RenderSystem"), renderer(renderer) {
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<RenderComponent>();
}


void RenderSystem::update() {
    if (renderer.hasRenderBeenCalledThisFrame()) {
        renderer.clearMeshData();
        for (auto& entity : getAssociatedEntities()) {
            auto& render = getComponent<RenderComponent>(entity);
            auto& transform = getComponent<TransformComponent>(entity);
            render.getMesh().setOwnerName(getEntityName(entity).c_str());
            renderer.sendMeshData(render.getMesh(), render.getMaterial(), transform.transform);
        }
    }
}
