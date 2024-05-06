/**************************************************************************************************
 * @file   BoundingVolume.h
 * @author Valentin Dumitru
 * @date   13/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "RendererTypes.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"
#include "engine/subsystems/renderer/mesh/Vertex.h"

namespace GLESC::Transform {
    class Transformer;
}

namespace GLESC::Render {
    /**
     * @brief A bounding volume is a geometric shape that encloses a set of points.
     * @details This class updates the bounding cuboid to fit the points it encloses.
     */
    class BoundingVolume {
        friend class GLESC::Transform::Transformer;

    public:
        BoundingVolume() = default;

        /**
         * @brief Updates the bounding volume to fit the points it encloses.
         * @param data The data to update the bounding volume with
         * @param size The size of the data
         * @param stride The stride (size of each vertex) of the data
         * @param offset The offset (position of the position attribute) of the data
         */
        void updateTopology(const void* data, unsigned int size, unsigned int stride, unsigned int offset) {
            // Find bounds
            float minX, maxX, minY, maxY, minZ, maxZ;
            minX = minY = minZ = std::numeric_limits<float>::max();
            maxX = maxY = maxZ = std::numeric_limits<float>::lowest();

            for (unsigned int i = 0; i < size; i += stride) {
                Position::ValueType x =
                    *reinterpret_cast<const Position::ValueType*>(reinterpret_cast<const char*>(data) + i + offset);
                Position::ValueType y =
                    *reinterpret_cast<const Position::ValueType*>
                    (reinterpret_cast<const char*>(data) + i + offset + sizeof(Position::ValueType));
                Position::ValueType z =
                    *reinterpret_cast<const Position::ValueType*>
                    (reinterpret_cast<const char*>(data) + i + offset + 2 * sizeof(Position::ValueType));
                minX = Math::min(minX, x);
                maxX = Math::max(maxX, x);
                minY = Math::min(minY, y);
                maxY = Math::max(maxY, y);
                minZ = Math::min(minZ, z);
                maxZ = Math::max(maxZ, z);
            }

            // Check if the bounding volume valid (not empty)
            if (minX == maxX || minY == maxY || minZ == maxZ) {
                return;
            }

            buildBoundingVolume(maxX, minX, maxY, minY, maxZ, minZ);
        }


        [[nodiscard]] const Math::Polyhedron& getTopology() const {
            return topology;
        }

        void operator=(const BoundingVolume& other) {
            topology = other.topology;
        }

    private:
        /**
         * @brief Builds the bounding volume from the given dimensions
         * @details This builds a cuboid with the given dimensions relative to the origin or center.
         * @param maxX The maximum x value
         * @param minX The minimum x value
         * @param maxY The maximum y value
         * @param minY The minimum y value
         * @param maxZ The maximum z value
         */
        void buildBoundingVolume(float maxX, float minX, float maxY, float minY, float maxZ,
                                 float minZ) {
            topology.clear();

            // Calculate Vertices (assuming origin-centered)
            topology.addVertex({minX, minY, minZ}); // 0
            topology.addVertex({maxX, minY, minZ}); // 1
            topology.addVertex({maxX, maxY, minZ}); // 2
            topology.addVertex({minX, maxY, minZ}); // 3
            topology.addVertex({minX, minY, maxZ}); // 4
            topology.addVertex({maxX, minY, maxZ}); // 5
            topology.addVertex({maxX, maxY, maxZ}); // 6
            topology.addVertex({minX, maxY, maxZ}); // 7

            // If the max - min of any axis is larger than step, put another vertex in the middle. Do this for each
            // times the axis is larger than step (e.g. if the difference is 11 and step is 5, add 2 vertices)
            // This is so when we do frustum culling, we can check if the frustum intersects with the bounding volume
            // by checking if any point is inside all the planes.
            // If its too big, we need extra points to check for intersection
            int step = 5;
            auto xAddVertices = static_cast<int>((maxX - minX) / step);
            auto yAddVertices = static_cast<int>((maxY - minY) / step);
            auto zAddVertices = static_cast<int>((maxZ - minZ) / step);

            // X-axis
            for (int i = 1; i <= xAddVertices - 1; i++) {
                float stepX = minX + i * (maxX - minX) / (xAddVertices + 1);
                topology.addVertex({stepX, minY, minZ});
                topology.addVertex({stepX, maxY, minZ});
                topology.addVertex({stepX, minY, maxZ});
                topology.addVertex({stepX, maxY, maxZ});
            }

            // Y-axis
            for (int i = 1; i <= yAddVertices - 1; i++) {
                float stepY = minY + i * (maxY - minY) / (yAddVertices + 1);
                topology.addVertex({minX, stepY, minZ});
                topology.addVertex({maxX, stepY, minZ});
                topology.addVertex({minX, stepY, maxZ});
                topology.addVertex({maxX, stepY, maxZ});
            }

            // Z-axis
            for (int i = 1; i <= zAddVertices - 1; i++) {
                float stepZ = minZ + i * (maxZ - minZ) / (zAddVertices + 1);
                topology.addVertex({minX, minY, stepZ});
                topology.addVertex({maxX, minY, stepZ});
                topology.addVertex({minX, maxY, stepZ});
                topology.addVertex({maxX, maxY, stepZ});
            }

            // Define Faces (adjustments here to maintain winding order)
            topology.addFace({0, 1, 2}); // Front
            topology.addFace({0, 2, 3});
            topology.addFace({0, 4, 5}); // Bottom
            topology.addFace({0, 5, 1});
            topology.addFace({1, 5, 6}); // Right
            topology.addFace({1, 6, 2});
            topology.addFace({3, 2, 6}); // Top
            topology.addFace({3, 6, 7});
            topology.addFace({4, 0, 3}); // Left
            topology.addFace({4, 3, 7});
            topology.addFace({4, 7, 6}); // Back
            topology.addFace({4, 6, 5});
        }

        Math::Polyhedron topology;
    }; // class BoundingVolume
}
