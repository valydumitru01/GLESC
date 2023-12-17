/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include <utility>
#include "engine/subsystems/renderer/shaders/Shader.h"

#include "engine/ecs/frontend/system/systems/RenderSystem.h"

RenderSystem::RenderSystem(GLESC::Renderer &renderer, GLESC::ECS &ecs) :
        System(ecs, "RenderSystem"), renderer(renderer) {
    addComponentRequirement<TransformComponent>();
    addComponentRequirement<RenderComponent>();
};


void RenderSystem::update(double timeOfFrame) {
    renderer.getDefaultShader().bind();
    /*
    // Maps for batched rendering and instanced rendering
    std::unordered_map<MeshMaterialKey, std::vector<Entity>, MeshMaterialKeyHash> staticBatches;
    std::unordered_map<MeshMaterialKey, std::vector<InstanceData>, MeshMaterialKeyHash> instancedBatches;
    
    Frustum frustum = calculateFrustum(renderer.getCamera().getViewProjectionMatrix());
    
    // Populate the maps with entities that share the same mesh and material
    for (auto &entity : getAssociatedEntities()) {
        auto &render = getComponent<RenderComponent>(entity);
        auto &transform = getComponent<TransformComponent>(entity);
        
        MeshMaterialKey key(render.mesh, render.material);
        BoundingVolume boundingVolume = calculateBoundingVolume(render.mesh, transform);
        
        // Decide whether to batch, instance, or render individually
        if (render.mesh.isStatic() && !render.mesh.dirtyFlag) {
            staticBatches[key].push_back(entity);
        } else {
            // For dynamic objects or instances, prepare instance data
            InstanceData data = {transform.position, transform.rotation, transform.scale};
            instancedBatches[key].push_back(data);
        }
    }
    
    // Render static batches
    for (auto &batch : staticBatches) {
        const auto &key = batch.first;
        // Render the pre-batched mesh
        renderer.renderBatch(key.mesh);
    }
    
    // Render instanced batches
    for (auto &batch : instancedBatches) {
        const auto &key = batch.first;
        const auto &instances = batch.second;
        
        // Setup instance data buffer and render all instances
        renderer.setupInstanceBuffer(instances);
        renderer.renderInstanced(key.mesh, instances.size());
    }*/
    
    // Render dynamic entities individually if any are left (not shown in this snippet)
}
