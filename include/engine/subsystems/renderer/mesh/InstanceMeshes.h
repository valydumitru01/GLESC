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

namespace GLESC::Render {
    struct MeshInstanceSharedData {
        const Material *material;
        const ColorMesh *mesh;

        bool operator<(const MeshInstanceSharedData &other) const {
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
        const Transform::Transform *transform;

        bool operator==(const MeshInstanceData &other) const {
            return transform == other.transform;
        }

        static std::vector<GAPI::Enums::Types> getDataLayout() {
            return {GAPI::Enums::Types::Vec3D, GAPI::Enums::Types::Vec3F, GAPI::Enums::Types::Vec3F};
        }
    };

    class InstanceMeshes {
    public:
        void addInstance(const ColorMesh &mesh,
                         const Material &material,
                         const Transform::Transform &transform) {
            instances[{&material, &mesh}].push_back({&transform});
        }

        void removeInstance(const ColorMesh &mesh,
                            const Material &material,
                            const Transform::Transform &transform) {
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
}
