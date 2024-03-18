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
#include "engine/core/low-level-renderer/buffers/vertex/VertexInstanceBuffer.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/mesh/InstanceMeshes.h"

struct AdaptedMesh {
    std::unique_ptr<GLESC::VertexArray> vertexArray; // For mesh vertex data
    std::unique_ptr<GLESC::IndexBuffer> indexBuffer;
    std::unique_ptr<GLESC::VertexBuffer> vertexBuffer;
};

struct AdaptedInstances {
    std::unique_ptr<GLESC::VertexArray> vertexArray; // For shared mesh vertex data
    std::unique_ptr<GLESC::IndexBuffer> indexBuffer; // For shared mesh index data
    std::unique_ptr<GLESC::VertexBuffer> vertexBuffer; // For shared mesh vertex data
    std::unique_ptr<GLESC::VertexInstanceBuffer> instanceBuffer; // For instance-specific data
    unsigned int instanceCount; // Number of instances
};
class MeshAdapter {
public:
 [[nodiscard]] static AdaptedMesh adaptMesh(const GLESC::ColorMesh& mesh);
 [[nodiscard]] static AdaptedInstances adaptInstances(const GLESC::ColorMesh& mesh,
                             const std::vector<MeshInstanceData>& instances);
}; // class MeshAdapter


