/**************************************************************************************************
 * @file   MeshAdapter.h
 * @author Valentin Dumitru
 * @date   22/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/low-level-renderer/buffers/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/VertexInstanceBuffer.h"
#include "engine/subsystems/renderer/material/Material.h"

#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Render {
    struct AdaptedMesh {
        std::unique_ptr<GAPI::VertexArray> vertexArray; // For mesh vertex data
        std::unique_ptr<GAPI::IndexBuffer> indexBuffer;
        std::unique_ptr<GAPI::VertexBuffer> vertexBuffer;
        const Material* material;
        const Transform::Transform* transform;
        const BoundingVolume* boundingVolume;
    };

    struct AdaptedInstances {
        std::unique_ptr<GAPI::VertexArray> vertexArray; // For shared mesh vertex data
        std::unique_ptr<GAPI::IndexBuffer> indexBuffer; // For shared mesh index data
        std::unique_ptr<GAPI::VertexBuffer> vertexBuffer; // For shared mesh vertex data
        std::unique_ptr<GAPI::VertexInstanceBuffer> instanceBuffer; // For instance-specific data
        unsigned int instanceCount; // Number of instances
    };

    class MeshAdapter {
    public:
        [[nodiscard]] static AdaptedMesh adaptMesh(const ColorMesh& mesh,
                                       const Material& material, Transform::Transform& transform);
        /*
                [[nodiscard]] static AdaptedInstances adaptInstances(const ColorMesh& mesh,
                                                                     const std::vector<MeshInstanceData>& instances);*/
    }; // class MeshAdapter
} // namespace Render
