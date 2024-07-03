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

#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"
#include "../../../core/math/geometry/figures/BoundingVolume.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class Frustum {
    public:
        Frustum() = delete;

        [[nodiscard]] const std::array<Math::Plane, 6>& getPlanes() const {
            return planes;
        }

        /**
         * @brief Constructs a frustum from a camera transform and perspective.
         *
         * @param VPMatrix The combined view-projection matrix.
         */
        explicit Frustum(const VP& VPMatrix) {
            extractPlanes(VPMatrix);
        }

        /**
         * @brief Updates the frustum planes based on new view and projection matrices.
         *
         * @param VPMat The combined view-projection matrix.
         */
        void update(const VP& VPMat) {
            extractPlanes(VPMat);
        }

        /**
         * @brief Checks if the frustum intersects with a given bounding volume.
         * @details Returns true if any point is inside all the planes
         *
         * @param volume The bounding volume to test for intersection.
         * @return true If the frustum intersects the volume.
         * @return false If the frustum does not intersect the volume.
         */
        [[nodiscard]] bool contains(const Math::BoundingVolume& volume) const;

        [[nodiscard]] bool contains(const Position& position) const;

    private:
       /**
        * @brief Extracts the frustum planes from a combined view-projection matrix. Uses Hartmann & Gribbs method.
        * It's done with colum-major matrices (OpenGL).
        * @see https://web.archive.org/web/20210226045225/http://www.cs.otago.ac.nz/postgrads/alexis/planeExtraction.pdf
        *
        * @param VPMatrix The combined view-projection matrix.
        */
        void extractPlanes(const VP& VPMatrix);

        std::array<Math::Plane, 6> planes{};
    }; // class Frustum
} // namespace GLESC::Render
