/**************************************************************************************************
 * @file   MeshAdapter.cpp
 * @author Valentin Dumitru
 * @date   22/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/renderer/mesh/MeshAdapter.h"
#include "engine/core/low-level-renderer/buffers/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexBufferLayout.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    template<typename Type>
    void printRawBufferData(const Type *data, size_t size) {
        size_t typeCount = size / sizeof(Type); // Calculate how many types are in the buffer
        std::cout << "Raw Vertex Data:\n";
        std::cout << std::fixed << std::setprecision(3); // Set precision for floating-point numbers
        for (size_t i = 0; i < typeCount; ++i) {
            if (i % 8 == 0 && i != 0) std::cout << "\n"; // New line every 8 types for readability
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    AdaptedMesh MeshAdapter::adaptMesh(const ColorMesh &mesh) {
        AdaptedMesh adaptedMesh;

        adaptedMesh.vertexArray = std::make_unique<GAPI::VertexArray>();

        const void *bufferData = mesh.getVertices().data();
        size_t bufferCount = mesh.getVertices().size();
        size_t vertexBytes = sizeof(ColorMesh::Vertex);
        size_t bufferBytes = bufferCount * vertexBytes;
        GAPI::Enums::BufferUsages bufferUsage = getBufferUsage(mesh.getRenderType());

        std::vector<float> adaptedData;
        // TODO: This is ugly and inefficient, must be fixed
        //    The solution is to have already the data inside the vertices in the correct format and order
        //    For some reason if you try to pass mesh.getVertices().data() directly to the buffer it will not work
        //    as the data gets sent to the GPU inverted (first noramls, then colors and then positions)
        for (const ColorMesh::Vertex &vertex : mesh.getVertices()) {
            adaptedData.push_back(getVertexPositionAttr(vertex).x());
            adaptedData.push_back(getVertexPositionAttr(vertex).y());
            adaptedData.push_back(getVertexPositionAttr(vertex).z());

            adaptedData.push_back(getVertexColorAttr(vertex).x());
            adaptedData.push_back(getVertexColorAttr(vertex).y());
            adaptedData.push_back(getVertexColorAttr(vertex).z());
            adaptedData.push_back(getVertexColorAttr(vertex).w());

            adaptedData.push_back(getVertexNormalAttr(vertex).x());
            adaptedData.push_back(getVertexNormalAttr(vertex).y());
            adaptedData.push_back(getVertexNormalAttr(vertex).z());
        }
        // This is needed to bind the vbo and ibo to the vao, so when we call draw we can draw the mesh
        adaptedMesh.vertexArray->bind();

        adaptedMesh.vertexBuffer = std::make_unique<GAPI::VertexBuffer>(
            adaptedData.data(),
            bufferCount,
            bufferBytes,
            bufferUsage
        );

        adaptedMesh.indexBuffer = std::make_unique<GAPI::IndexBuffer>(
            mesh.getIndices().data(),
            mesh.getIndices().size());

        GAPI::VertexBufferLayout layout;
        for (GAPI::Enums::Types type : mesh.getVertexLayout()) {
            layout.push(type);
        }


        adaptedMesh.vertexArray->addBuffer(*adaptedMesh.vertexBuffer, layout);

        return adaptedMesh;
    }

    AdaptedInstances MeshAdapter::adaptInstances(const ColorMesh &mesh,
                                                 const std::vector<MeshInstanceData> &instances) {
        // First, adapt the mesh to get a VAO and attached VBOs for vertex and index data.
        AdaptedMesh adapterMesh = adaptMesh(mesh);
        AdaptedInstances adaptedInstances;


        using InstanceTransform = Mat4F;

        // Calculate the total size needed for all instance transformations.
        size_t instanceDataSize = instances.size() * sizeof(InstanceTransform);
        // Assuming InstanceTransform is a struct

        // Create a buffer for instance data.
        std::vector<InstanceTransform> instanceTransforms;
        instanceTransforms.reserve(instances.size());

        // Fill the buffer with transformation data from instances.
        for (const auto &instance : instances) {
            InstanceTransform transform;
            // Assuming you have a function to convert position, rotation, and scale
            // into a 4x4 transformation matrix:
            transform.makeModelMatrix(instance.transform->getPosition(), instance.transform->getRotation(),
                                      instance.transform->getScale());
            instanceTransforms.push_back(transform);
        }

        adaptedInstances.instanceBuffer = std::make_unique<GAPI::VertexInstanceBuffer>(
            instanceTransforms.data(), instances.size(), instanceDataSize,
            // We will update the instance data frequently.
            GAPI::Enums::BufferUsages::DynamicDraw);


        GAPI::VertexBufferLayout instanceLayout;
        for (GAPI::Enums::Types type : MeshInstanceData::getDataLayout()) {
            instanceLayout.push(type);
        }
        // TODO: This is probably wrong, must be fixed
        adaptedInstances.instanceBuffer->setupInstanceAttributes(instanceLayout, mesh.getVertexLayout().size());


        adaptedInstances.instanceCount = instances.size();
        // Add the instance buffer to the VAO with the correct layout.
        //vertexArrayPtr->addBuffer(instanceBuffer, instanceLayout);

        return adaptedInstances;
    }
}
