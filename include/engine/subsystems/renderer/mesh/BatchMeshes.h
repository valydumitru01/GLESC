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

namespace GLESC::Render {
    class MeshBatches {
    public:
        MeshBatches() = default;

        void attatchMesh(const Material &material, const ColorMesh &mesh) {
            for (const auto &vertex : mesh.getVertices()) {
                this->batches[&material].addAutoFaceVertex(vertex);
            }
        }

        auto getBatches() const {
            return batches;
        }

    private:
        std::map<const Material *, ColorMesh> batches{};
    }; // class MeshBatch
} // namespace GLESC::Render
