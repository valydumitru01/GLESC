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
    GLESC::Mesh mesh;
    GLESC::Material material;
    
    MeshMaterialKey(const Mesh& m, const Material& mat)
            : mesh(m), material(mat) {}
    
    // Equality operator
    bool operator==(const MeshMaterialKey& other) const {
        return mesh == other.mesh && material == other.material;
    }
};

// Custom hash function for MeshMaterialKey
class MeshMaterialKeyHash {
public:
    size_t operator()(const MeshMaterialKey& key) const {
        return std::hash<Mesh>()(key.mesh) ^ std::hash<Material>()(key.material);
    }
};