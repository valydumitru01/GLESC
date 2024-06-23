/**************************************************************************************************
 * @file   Frustum.cpp
 * @author Valentin Dumitru
 * @date   14/06/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/math/Frustum.h"
using namespace GLESC::Render;

void Frustum::extractPlanes(const VP& VPMatrix) {
    if constexpr (Math::MatrixAlgorithms::columnMajorMatrix) [[maybe_unused]]  {
        // Left clipping plane
        planes[0].setNormal(Math::Direction(VPMatrix[0][3] + VPMatrix[0][0],
                                            VPMatrix[1][3] + VPMatrix[1][0],
                                            VPMatrix[2][3] + VPMatrix[2][0]));
        planes[0].setDistance(VPMatrix[3][3] + VPMatrix[3][0]);
        planes[0].normalize();

        // Right clipping plane
        planes[1].setNormal(Math::Direction(VPMatrix[0][3] - VPMatrix[0][0],
                                            VPMatrix[1][3] - VPMatrix[1][0],
                                            VPMatrix[2][3] - VPMatrix[2][0]));
        planes[1].setDistance(VPMatrix[3][3] - VPMatrix[3][0]);
        planes[1].normalize();

        // Top clipping plane
        planes[2].setNormal(Math::Direction(VPMatrix[0][3] - VPMatrix[0][1],
                                            VPMatrix[1][3] - VPMatrix[1][1],
                                            VPMatrix[2][3] - VPMatrix[2][1]));
        planes[2].setDistance(VPMatrix[3][3] - VPMatrix[3][1]);
        planes[2].normalize();

        // Bottom clipping plane
        planes[3].setNormal(Math::Direction(VPMatrix[0][3] + VPMatrix[0][1],
                                            VPMatrix[1][3] + VPMatrix[1][1],
                                            VPMatrix[2][3] + VPMatrix[2][1]));
        planes[3].setDistance(VPMatrix[3][3] + VPMatrix[3][1]);
        planes[3].normalize();

        // Near clipping plane
        planes[4].setNormal(Math::Direction(VPMatrix[0][3] + VPMatrix[0][2],
                                            VPMatrix[1][3] + VPMatrix[1][2],
                                            VPMatrix[2][3] + VPMatrix[2][2]));
        planes[4].setDistance(VPMatrix[3][3] + VPMatrix[3][2]);
        planes[4].normalize();

        // Far clipping plane
        planes[5].setNormal(Math::Direction(VPMatrix[0][3] - VPMatrix[0][2],
                                            VPMatrix[1][3] - VPMatrix[1][2],
                                            VPMatrix[2][3] - VPMatrix[2][2]));
        planes[5].setDistance(VPMatrix[3][3] - VPMatrix[3][2]);
        planes[5].normalize();
    }
    else [[maybe_unused]] {
        // Left clipping plane
        planes[0].setNormal(Math::Direction(VPMatrix[3][0] + VPMatrix[0][0],
                                            VPMatrix[3][1] + VPMatrix[0][1],
                                            VPMatrix[3][2] + VPMatrix[0][2]));
        planes[0].setDistance(VPMatrix[3][3] + VPMatrix[0][3]);
        planes[0].normalize();

        // Right clipping plane
        planes[1].setNormal(Math::Direction(VPMatrix[3][0] - VPMatrix[0][0],
                                            VPMatrix[3][1] - VPMatrix[0][1],
                                            VPMatrix[3][2] - VPMatrix[0][2]));
        planes[1].setDistance(VPMatrix[3][3] - VPMatrix[0][3]);
        planes[1].normalize();

        // Top clipping plane
        planes[2].setNormal(Math::Direction(VPMatrix[3][0] - VPMatrix[1][0],
                                            VPMatrix[3][1] - VPMatrix[1][1],
                                            VPMatrix[3][2] - VPMatrix[1][2]));
        planes[2].setDistance(VPMatrix[3][3] - VPMatrix[1][3]);
        planes[2].normalize();

        // Bottom clipping plane
        planes[3].setNormal(Math::Direction(VPMatrix[3][0] + VPMatrix[1][0],
                                            VPMatrix[3][1] + VPMatrix[1][1],
                                            VPMatrix[3][2] + VPMatrix[1][2]));
        planes[3].setDistance(VPMatrix[3][3] + VPMatrix[1][3]);
        planes[3].normalize();

        // Near clipping plane
        planes[4].setNormal(Math::Direction(VPMatrix[3][0] + VPMatrix[2][0],
                                            VPMatrix[3][1] + VPMatrix[2][1],
                                            VPMatrix[3][2] + VPMatrix[2][2]));
        planes[4].setDistance(VPMatrix[3][3] + VPMatrix[2][3]);
        planes[4].normalize();

        // Far clipping plane
        planes[5].setNormal(Math::Direction(VPMatrix[3][0] - VPMatrix[2][0],
                                            VPMatrix[3][1] - VPMatrix[2][1],
                                            VPMatrix[3][2] - VPMatrix[2][2]));
        planes[5].setDistance(VPMatrix[3][3] - VPMatrix[2][3]);
        planes[5].normalize();
    }
}

bool Frustum::contains(const Position& position) const {
    for (const Math::Plane& plane : planes) {
        if (!plane.hasInside(position)) {
            return false;
        }
    }
    return true;
}

bool Frustum::contains(const Math::BoundingVolume& volume) const {
    const auto& bbox = volume.getBoundingBox();
    for (const auto& plane : planes) {
        // Check if all points of the AABB are outside a plane
        if (!plane.hasInside({bbox.min.getX(), bbox.min.getY(), bbox.min.getZ()}) &&
            !plane.hasInside({bbox.max.getX(), bbox.min.getY(), bbox.min.getZ()}) &&
            !plane.hasInside({bbox.min.getX(), bbox.max.getY(), bbox.min.getZ()}) &&
            !plane.hasInside({bbox.max.getX(), bbox.max.getY(), bbox.min.getZ()}) &&
            !plane.hasInside({bbox.min.getX(), bbox.min.getY(), bbox.max.getZ()}) &&
            !plane.hasInside({bbox.max.getX(), bbox.min.getY(), bbox.max.getZ()}) &&
            !plane.hasInside({bbox.min.getX(), bbox.max.getY(), bbox.max.getZ()}) &&
            !plane.hasInside({bbox.max.getX(), bbox.max.getY(), bbox.max.getZ()})) {
            return false;
        }
    }
    return true;
}
