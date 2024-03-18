/**************************************************************************************************
 * @file   MeshAdapter.cpp
 * @author Valentin Dumitru
 * @date   22/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/renderer/MeshAdapter.h"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBufferLayout.h"
#include "engine/subsystems/renderer/RendererTypes.h"

AdaptedMesh MeshAdapter::adaptMesh(const GLESC::ColorMesh& mesh) {
    AdaptedMesh adaptedMesh;

    adaptedMesh.vertexArray = std::make_unique<GLESC::VertexArray>();

    // Assuming VertexBuffer's constructor appropriately allocates and manages buffer memory
    adaptedMesh.vertexBuffer = std::make_unique<GLESC::VertexBuffer>(
        mesh.getVertices().data(),
        mesh.getVertices().size(),
        mesh.getVertices().size() * sizeof(GLESC::ColorMesh::Vertex),
        getBufferUsage(mesh.getRenderType())
    );

    adaptedMesh.indexBuffer = std::make_unique<GLESC::IndexBuffer>(
        mesh.getIndices().data(),
        mesh.getIndices().size());

    GLESC::VertexBufferLayout layout;
    for (GAPI::Types type : mesh.getVertexLayout()) {
        layout.push(type);
    }

    // Bind VertexArray to configure it
    adaptedMesh.vertexArray->bind();
    // Assumes addBuffer binds and configures the VBO appropriately
    adaptedMesh.vertexArray->addBuffer(*adaptedMesh.vertexBuffer, layout);
    adaptedMesh.indexBuffer->bind(); // Ensure the IndexBuffer is bound

    // Note: Unbinding is not shown but may be done if needed

    return adaptedMesh;
}

AdaptedInstances MeshAdapter::adaptInstances(const GLESC::ColorMesh& mesh,
                                             const std::vector<MeshInstanceData>& instances) {
    // First, adapt the mesh to get a VAO and attached VBOs for vertex and index data.
    AdaptedMesh adapterMesh = adaptMesh(mesh);
    AdaptedInstances adaptedInstances;


    using InstanceTransform = Mat4F;

    // Calculate the total size needed for all instance transformations.
    size_t instanceDataSize = instances.size() * sizeof(InstanceTransform); // Assuming InstanceTransform is a struct

    // Create a buffer for instance data.
    std::vector<InstanceTransform> instanceTransforms;
    instanceTransforms.reserve(instances.size());

    // Fill the buffer with transformation data from instances.
    for (const auto& instance : instances) {
        InstanceTransform transform;
        // Assuming you have a function to convert position, rotation, and scale
        // into a 4x4 transformation matrix:
        transform.makeModelMatrix(instance.transform->position, instance.transform->rotation,
                                  instance.transform->scale);
        instanceTransforms.push_back(transform);
    }

    adaptedInstances.instanceBuffer = std::make_unique<GLESC::VertexInstanceBuffer>(
        instanceTransforms.data(), instances.size(), instanceDataSize,
        // We will update the instance data frequently.
        GAPI::BufferUsages::DynamicDraw);


    GLESC::VertexBufferLayout instanceLayout;
    for (GAPI::Types type : MeshInstanceData::getDataLayout()) {
        instanceLayout.push(type);
    }
    // TODO: This is probably wrong, must be fixed
    adaptedInstances.instanceBuffer->setupInstanceAttributes(instanceLayout, mesh.getVertexLayout().size());


    adaptedInstances.instanceCount = instances.size();
    // Add the instance buffer to the VAO with the correct layout.
    //vertexArrayPtr->addBuffer(instanceBuffer, instanceLayout);

    return adaptedInstances;
}
