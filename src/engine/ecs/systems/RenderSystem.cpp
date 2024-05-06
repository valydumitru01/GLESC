/******************************************************************************
 * @file   RenderSystem.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/system/systems/RenderSystem.h"
using namespace GLESC::ECS;

RenderSystem::RenderSystem(Render::Renderer& renderer, ECSCoordinator& ecs) :
        System(ecs, "RenderSystem"), renderer(renderer) {
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<RenderComponent>();
};


void RenderSystem::update() {
    Render::ColorMesh batch;
    for (auto& entity : getAssociatedEntities()) {
        auto& render = getComponent<RenderComponent>(entity);
        
        auto& transform = getComponent<TransformComponent>(entity);

        batches[render.material].push_back(&render.mesh);
    }

    // For each different material, create a batch and attatch all the meshes with that material to it
    for (auto& [material, meshes] : batches) {
        meshBatches.push_back(Render::ColorMesh());
        renderer.attatchMeshToBatch(meshBatches, meshes);
    }

}
