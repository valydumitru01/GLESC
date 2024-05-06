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
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Render {
    template <typename Type>
    void printRawBufferData(const Type* data, size_t size) {
        size_t typeCount = size / sizeof(Type); // Calculate how many types are in the buffer
        std::cout << "Raw Vertex Data:\n";
        std::cout << std::fixed << std::setprecision(3); // Set precision for floating-point numbers
        for (size_t i = 0; i < typeCount; ++i) {
            if (i % 8 == 0 && i != 0) std::cout << "\n"; // New line every 8 types for readability
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    AdaptedMesh MeshAdapter::adaptMesh(const ColorMesh& mesh,
                                       const Material& material, Transform::Transform& transform) {
        AdaptedMesh adaptedMesh;
        adaptedMesh.material = &material;
        adaptedMesh.boundingVolume = &mesh.getBoundingVolume();
        adaptedMesh.transform = &transform;
        adaptedMesh.vertexArray = std::make_unique<GAPI::VertexArray>();

        const void* bufferData = mesh.getVertices().data();
        size_t bufferCount = mesh.getVertices().size();
        size_t vertexBytes = sizeof(ColorVertex);
        GAPI::Enums::BufferUsages bufferUsage = getBufferUsage(mesh.getRenderType());
        // This is needed to bind the vbo and ibo to the vao, so when we call draw we can draw the mesh
        adaptedMesh.vertexArray->bind();

        adaptedMesh.vertexBuffer = std::make_unique<GAPI::VertexBuffer>(
            bufferData,
            bufferCount,
            vertexBytes,
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

}
