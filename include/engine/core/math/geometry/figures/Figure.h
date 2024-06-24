/**************************************************************************************************
 * @file   Figure.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <engine/core/math/geometry/figures/polyhedron/Polyhedron.h>
#include "engine/core/math/geometry/figures/plane/Plane.h"

namespace GLESC::Math {
    /**
     * @brief Base class for all geometric figures
     */
    class Figure {
    public:
        virtual ~Figure() = default;

        /**
         * @brief Checks if the figure intersects with the given plane
         * @param plane The plane to check intersection with
         * @return True if the figure intersects with the plane, false otherwise
         */
        [[nodiscard]] virtual bool intersects(const Plane &plane) const = 0;

        /**
         * @brief Checks if the figure intersects with the given line
         * @param line The line to check intersection with
         * @return True if the figure intersects with the line, false otherwise
         */
        [[nodiscard]] virtual bool intersects(const Line & line) const = 0;

        /**
         * @brief Checks if the figure intersects with the given face.
         * @param face The face to check intersection with.
         * @return True if the figure intersects with the face, false otherwise.
         */
        [[nodiscard]] virtual bool intersects(const PolyhedronFace & face) const = 0;

        /**
         * @brief Checks if the figure intersects with the given polyhedron
         * @param polyhedron The polyhedron to check intersection with
         * @return True if the figure intersects with the polyhedron, false otherwise
         */
        [[nodiscard]] virtual bool intersects(const Polyhedron &polyhedron) const = 0;

        /**
         * @brief Checks if the figure intersects with the given point
         * @param point The point to check intersection with
         * @return True if the figure intersects with the point, false otherwise
         */
        [[nodiscard]] virtual bool intersects(const Point &point) const = 0;
    }; // class Figure
} // namespace GLESC::Math