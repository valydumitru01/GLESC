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

#include "Mesh.h"

class MeshMaterialKey {
public:
    GLESC::ColorMesh mesh;
    GLESC::Material material;
    
    MeshMaterialKey(const GLESC::ColorMesh& m, const GLESC::Material& mat)
            : mesh(m), material(mat) {}
    
    // Equality operator
    bool operator==(const MeshMaterialKey& other) const {
        return mesh == other.mesh && material == other.material;
    }
};

class MeshMaterialHash {
public:
    std::size_t operator()(const MeshMaterialKey& key) const {
        std::size_t hash = std::hash<GLESC::ColorMesh>()(key.mesh);
        GLESC::Hasher::hashCombine(hash, std::hash<GLESC::Material>()(key.material));
        return hash;
    }
};
