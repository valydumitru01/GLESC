/**************************************************************************************************
 * @file   DynamicMeshes.h
 * @author Valentin Dumitru
 * @date   20/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/renderer/material/Material.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/transform/Transform.h"

struct DynamicMesh {
    const GLESC::ColorMesh* mesh;
    const GLESC::Material* material;
    const GLESC::Transform* transform;
    bool operator==(const DynamicMesh& other) const {
        return mesh == other.mesh && material == other.material && transform == other.transform;
    }

    bool operator<(const DynamicMesh& other) const {
        if (mesh < other.mesh) {
            return true;
        }
        if (mesh > other.mesh) {
            return false;
        }
        if (material < other.material) {
            return true;
        }
        if (material > other.material) {
            return false;
        }
        return transform < other.transform;
    }
};

class DynamicMeshes {
public:
    void addDynamicMesh(const GLESC::ColorMesh& mesh, const GLESC::Material& material,
                        const GLESC::Transform& transform) {
        dynamicMeshes.insert({&mesh, &material, &transform});
    }

    std::set<DynamicMesh>& getDynamicMeshes() {
        return dynamicMeshes;
    }

private:
    std::set<DynamicMesh> dynamicMeshes;
}; // class DynamicMeshes
