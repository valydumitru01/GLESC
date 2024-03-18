/**************************************************************************************************
 * @file   InstanceMeshes.h
 * @author Valentin Dumitru
 * @date   16/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/transform/Transform.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/material/Material.h"

struct MeshInstanceSharedData {
    const GLESC::Material* material;
    const GLESC::ColorMesh* mesh;

    bool operator<(const MeshInstanceSharedData& other) const {
        if (material < other.material) {
            return true;
        }
        if (material > other.material) {
            return false;
        }
        return mesh < other.mesh;
    }
};

struct MeshInstanceData {
    const GLESC::Transform* transform;

    bool operator==(const MeshInstanceData& other) const {
        return transform == other.transform;
    }

    static std::vector<GAPI::Types> getDataLayout() {
        return {GAPI::Types::Vec3D, GAPI::Types::Vec3F, GAPI::Types::Vec3F};
    }

};

class InstanceMeshes {
public:
    void addInstance(const GLESC::ColorMesh& mesh, const GLESC::Material& material, const GLESC::Transform &transform) {
        instances[{&material, &mesh}].push_back({&transform});
    }

    void removeInstance(const GLESC::ColorMesh& mesh, const GLESC::Material& material,
                    const GLESC::Transform& transform) {
        // Create the shared data key from the pointers to the provided mesh and material.
        MeshInstanceSharedData key{&material, &mesh};

        // Find the vector of individual instances in the map using the shared data key.
        auto it = instances.find(key);
        if (it != instances.end()) {
            // Create an instance of individual data to match against.
            MeshInstanceData to_remove{&transform};

            // Use remove-erase idiom to remove the individual instance data from the vector.
            it->second.erase(std::remove(it->second.begin(), it->second.end(), to_remove), it->second.end());

            // Optionally, if the vector is now empty, you can remove the key from the map as well.
            if (it->second.empty()) {
                instances.erase(it);
            }
        }
    }

    auto getInstances() const {
        return instances;
    }

private:
    std::map<MeshInstanceSharedData, std::vector<MeshInstanceData>> instances{};
}; // class MeshInstanceBatch
