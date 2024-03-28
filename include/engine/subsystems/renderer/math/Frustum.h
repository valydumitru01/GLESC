/**************************************************************************************************
 * @file   Frustum.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Class for representing a frustum and performing intersection tests.
 *
 * This class represents a viewing frustum, which can be used for frustum culling
 * or visibility determination in 3D scenes. The frustum is defined by six planes.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/geometry/figures/Figure.h"
#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"
#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/geometry/figures/plane/Plane.h"

class Frustum {
public:
    Frustum() = default;

    [[nodiscard]] const std::array<GLESC::Math::Plane, 6> getPlanes() const {
        return planes;
    }

    /**
     * @brief Construct a new Frustum object from view and projection matrices.
     *
     * @param viewMatrix The view matrix.
     * @param projMatrix The projection matrix.
     */
    Frustum(const Mat4F &viewMatrix, const Mat4F &projMatrix) {
        D_ASSERT_TRUE(viewMatrix.isValidViewMatrix(), "Invalid view matrix");
        update(viewMatrix, projMatrix);
    }

    /**
     * @brief Updates the frustum planes based on new view and projection matrices.
     *
     * @param viewMatrix The view matrix.
     * @param projMatrix The projection matrix.
     */
    void update(const Mat4F &viewMatrix, const Mat4F &projMatrix) {
        D_ASSERT_TRUE(viewMatrix.isValidViewMatrix(), "Invalid view matrix");
        extractPlanesFromMatrices(viewMatrix, projMatrix);
    }

    /**
     * @brief Checks if the frustum intersects with a given bounding volume.
     *
     * @param volume The bounding volume to test for intersection.
     * @return true If the frustum intersects the volume.
     * @return false If the frustum does not intersect the volume.
     */
    [[nodiscard]] bool intersects(const BoundingVolume &volume) const {
        for (const auto &plane : planes) {
            if (!volume.getTopology().intersects(plane)) {
                return false;
            }
        }
        return true;
    }

private:
    void extractPlanesFromMatrices(const Mat4F &viewMatrix, const Mat4F &projMatrix) {
        VP vpMatrix = projMatrix * viewMatrix; // Combine view and projection matrices

        // Extract frustum planes using the combined view-projection matrix (vpMatrix)
        // Left Plane
        planes[0] = GLESC::Math::Plane(GLESC::Math::Direction(vpMatrix[0][3] + vpMatrix[0][0],
                                                              vpMatrix[1][3] + vpMatrix[1][0],
                                                              vpMatrix[2][3] + vpMatrix[2][0]),
                                       vpMatrix[3][3] + vpMatrix[3][0]);
        // Right Plane
        planes[1] = GLESC::Math::Plane(GLESC::Math::Direction(vpMatrix[0][3] - vpMatrix[0][0],
                                                              vpMatrix[1][3] - vpMatrix[1][0],
                                                              vpMatrix[2][3] - vpMatrix[2][0]),
                                       vpMatrix[3][3] - vpMatrix[3][0]);
        // Bottom Plane
        planes[2] = GLESC::Math::Plane(GLESC::Math::Direction(vpMatrix[0][3] + vpMatrix[0][1],
                                                              vpMatrix[1][3] + vpMatrix[1][1],
                                                              vpMatrix[2][3] + vpMatrix[2][1]),
                                       vpMatrix[3][3] + vpMatrix[3][1]);
        // Top Plane
        planes[3] = GLESC::Math::Plane(GLESC::Math::Direction(vpMatrix[0][3] - vpMatrix[0][1],
                                                              vpMatrix[1][3] - vpMatrix[1][1],
                                                              vpMatrix[2][3] - vpMatrix[2][1]),
                                       vpMatrix[3][3] - vpMatrix[3][1]);
        // Near Plane
        planes[4] = GLESC::Math::Plane(GLESC::Math::Direction(vpMatrix[0][3] + vpMatrix[0][2],
                                                              vpMatrix[1][3] + vpMatrix[1][2],
                                                              vpMatrix[2][3] + vpMatrix[2][2]),
                                       vpMatrix[3][3] + vpMatrix[3][2]);
        // Far Plane
        planes[5] = GLESC::Math::Plane(GLESC::Math::Direction(vpMatrix[0][3] - vpMatrix[0][2],
                                                              vpMatrix[1][3] - vpMatrix[1][2],
                                                              vpMatrix[2][3] - vpMatrix[2][2]),
                                       vpMatrix[3][3] - vpMatrix[3][2]);
    }

    std::array<GLESC::Math::Plane, 6> planes{};
}; // class Frustum
