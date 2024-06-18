/**************************************************************************************************
 * @file   Sphere.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/geometry/figures/Figure.h"
#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"

namespace GLESC::Math {
    class Sphere : public Figure {
    public:
        /**
         * @brief Creates a sphere with the given center and radius
         * @param centerParam The center of the sphere
         * @param radiusParam The radius of the sphere
         */
        Sphere(Point centerParam, Distance radiusParam);
        
        /**
         * @brief Checks if the sphere intersects with the given plane
         * @param plane The plane to check intersection with
         * @return True if the sphere intersects with the plane, false otherwise
         */
        [[nodiscard]] bool intersects(const Plane &plane) const override;
        
        [[nodiscard]] bool intersects(const Line & line) const override;
        
        
        /**
         * @brief Checks if the sphere intersects with the given face.
         * @param face The face to check intersection with.
         * @return True if the sphere intersects with the face, false otherwise.
         */
        [[nodiscard]] bool intersects(const PolyhedronFace &face) const override;
        
        /**
         * @brief Checks if the sphere intersects with the given figure
         * @param polyhedron The figure to check intersection with
         * @return True if the sphere intersects with the figure, false otherwise
         */
        [[nodiscard]] bool intersects(const Polyhedron &polyhedron) const override;
        
        /**
         * @brief Checks if the sphere intersects with the given point
         * @param point The point to check intersection with
         * @return True if the sphere intersects with the point, false otherwise
         */
        [[nodiscard]] bool intersects(const Point &point) const override;
        
        
        
        
    private:
        /**
         * @brief Checks if the sphere intersects with an edge defined by two points.
         * @param startPoint The start point of the edge.
         * @param endPoint The end point of the edge.
         * @return True if the sphere intersects with the edge, false otherwise.
         */
        [[nodiscard]] bool intersects(const Point &startPoint, const Point &endPoint) const;
        /**
         * @brief The center of the sphere
         */
        Point center;
        /**
         * @brief The radius of the sphere
         */
        float radius;
    }; // class Sphere
} // namespace GLESC::Math