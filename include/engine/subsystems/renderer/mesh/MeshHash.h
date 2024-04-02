/**************************************************************************************************
 * @file   MeshHash.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <utility>

#include "Mesh.h"
#include "engine/subsystems/renderer/material/Material.h"

namespace GLESC::Render {
    class MeshMaterialKey {
    public:
        ColorMesh mesh;
        Material material;

        MeshMaterialKey(const ColorMesh &m, Material mat) : mesh(m), material(std::move(mat)) {
        }

        // Equality operator
        bool operator==(const MeshMaterialKey &other) const {
            return mesh == other.mesh && material == other.material;
        }
    }; // class MeshMaterialKey

    class MeshMaterialHash {
    public:
        std::size_t operator()(const MeshMaterialKey &key) const {
            std::size_t hash = std::hash<ColorMesh>()(key.mesh);
            Hasher::hashCombine(hash, std::hash<Material>()(key.material));
            return hash;
        }
    }; // class MeshMaterialHash
} // namespace GLESC::Render
