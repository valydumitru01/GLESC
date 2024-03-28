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

/**
 * @brief A bounding volume is a geometric shape that encloses a set of points.
 * @details This class updates the bounding cuboid to fit the points it encloses.
 */
class BoundingVolume {
public:
    BoundingVolume() = default;

    /**
     * @brief Updates the bounding volume to fit the points it encloses.
     * @param vertices The points to enclose
     */
    template <typename... Attributes>
    void updateTopology(const std::vector<GLESC::Vertex<Attributes...>>& vertices) {
        // Ensure the first element of attributes is a Vec3D
        S_ASSERT_TRUE((std::is_same_v<typename std::tuple_element<0, std::tuple<Attributes...>>::type, Position>),
                      "First attribute must be render type: position");
        if (vertices.empty()) return;

        // Find bounds
        float minX, maxX, minY, maxY, minZ, maxZ;
        minX = minY = minZ = std::numeric_limits<float>::max();
        maxX = maxY = maxZ = std::numeric_limits<float>::lowest();

        for (const auto& point : vertices) {
            minX = GLESC::Math::min(minX, getVertexPositionAttr(point).getX());
            maxX = GLESC::Math::max(maxX, getVertexPositionAttr(point).getX());
            minY = GLESC::Math::min(minY, getVertexPositionAttr(point).getY());
            maxY = GLESC::Math::max(maxY, getVertexPositionAttr(point).getY());
            minZ = GLESC::Math::min(minZ, getVertexPositionAttr(point).getZ());
            maxZ = GLESC::Math::max(maxZ, getVertexPositionAttr(point).getZ());
        }

        // Check if the bounding volume valid (not empty)
        if (minX == maxX || minY == maxY || minZ == maxZ) {
            return;
        }
        buildBoundingVolume(maxX, minX, maxY, minY, maxZ, minZ);
    }


    [[nodiscard]] const GLESC::Math::Polyhedron& getTopology() const {
        return topology;
    }

    [[nodiscard]] GLESC::Math::Polyhedron& getTopologyMutable() {
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

    GLESC::Math::Polyhedron topology;
}; // class BoundingVolume
