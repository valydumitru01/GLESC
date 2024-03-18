/**************************************************************************************************
 * @file   MeshBatches.h
 * @author Valentin Dumitru
 * @date   16/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"

class MeshBatches {

public:
    MeshBatches() = default;

    void attatchMesh(const GLESC::Material& material, const GLESC::ColorMesh& mesh) {
        for (const auto& vertex : mesh.getVertices()) {
            this->batches[&material].addVertex(vertex);
        }
    }

    auto getBatches() const {
        return batches;
    }

private:
    std::map<const GLESC::Material*, GLESC::ColorMesh> batches{};
}; // class MeshBatch
