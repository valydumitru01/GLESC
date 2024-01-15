/**************************************************************************************************
 * @file   Plane.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <utility>

#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/core/math/geometry/figures/line/Line.h"
#include "engine/core/math/geometry/GeometryTypes.h"


namespace GLESC::Math {
    class Plane {
    public:
        /**
         * @brief Construct a new Plane object.
         * @details The default constructor creates a plane with the normal vector (0, 0, 1) and
         * distance 0. Constructs a "zero plane".
         */
        Plane();
        
        /**
         * @brief Construct a new Plane object from a normal vector and a distance.
         * @details The normal vector is normalized if its length is greater than 1.
         * The normal cannot be a zero vector.
         * The distance is the distance from the origin to the plane. It can be any real number
         * (positive, negative or zero).
         * @param normalParam The normal vector of the plane.
         * @param distanceParam The distance from the origin to the plane.
         */
        Plane(const Direction &normalParam, double distanceParam);
        
        /**
         * @brief
         * @param point
         * @param normalParam
         */
        Plane(const Point &point, const Direction &normalParam) noexcept;
        
        Plane(const Point &point1, const Point &point2, const Point &point3) noexcept;
        
        Plane(const Point &point, const Line &line) noexcept;
        
        
        
        
        Plane(const Plane &plane) noexcept = default;
        
        Plane(Plane &&plane) noexcept = default;
        
        Plane &operator=(const Plane &plane) noexcept= default;
        
        Plane &operator=(Plane &&plane) noexcept = default;
        
        ~Plane() = default;
        
        void setNormal(const Direction &normalParam);
        
        void setDistance(double distanceParam);
        
        [[nodiscard]] const Direction &getNormal() const;
        
        [[nodiscard]] double getDistance() const;
        
        /**
         * @brief Calculate the distance from the plane to a point.
         * @details The formula for calculating the distance from a plane to a point is:
         * d = (n ⋅ p) + D
         * Where:
         *      n is the normalized normal vector of the plane.
         *      p is the point.
         *      D is the distance of the plane from the origin along its normal.
         * @param point
         * @return
         */
        [[nodiscard]] double distanceToPoint(const Point &point) const;
        
        [[nodiscard]] bool intersects(const Point &point) const;
        
        [[nodiscard]] bool intersects(const Plane &plane) const;
        
        /**
         * @brief Checks if the plane intersects with a given line.
         * @param line The line to check for intersection with the plane.
         * @return True if the plane intersects with the line, false otherwise.
         */
        [[nodiscard]] bool intersects(const Line &line) const;
        
        /**
         * @brief Checks if the plane intersects with a given line and sets the intersection point
         * if it exists. The parameter intersectionPoint is set to the intersection point.
         * @param line The line to check for intersection with the plane.
         * @param intersectionPoint The intersection point that is overwritten if it exists.
         * @return True if the plane intersects with the line, false otherwise.
         */
        [[nodiscard]] bool intersects(const Line &line, Point &intersectionPoint) const;
        
        /**
         * @brief Compare two planes for equality.
         * @param other The plane to compare with.
         * @return True if the planes are equal, false otherwise.
         */
        bool operator==(const Plane &other) const;
    
    private:
        
        /**
         * @brief Calculate the normal vector of the plane defined by three distinct points.
         *
         * @param firstPoint The first point.
         * @param secondPoint The second point.
         * @param thirdPoint The third point.
         * @return Direction The normal vector of the plane.
         */
        [[nodiscard]] static Direction calculateNormalFromPoints(
                const Point &firstPoint, const Point &secondPoint, const Point &thirdPoint);
        
        /**
         * @brief Calculate the normal vector of the plane defined by a point and a line.
         *
         * @param point A point not on the line.
         * @param line A line not containing the point.
         * @return Direction The normal vector of the plane.
         */
        [[nodiscard]] static Direction calculateNormalFromPointAndLine(
                const Point &point, const Line &line);
        
        /**
         * @brief Calculate the distance from the origin to the plane defined by a point on the
         * plane and the plane's normal vector.
         *
         * @param point A point on the plane.
         * @param normal The normal vector of the plane.
         * @return double The distance from the origin to the plane.
         */
        [[nodiscard]] static double calculateDistanceFromPointAndNormal(
                const Point &point, const Direction &normal);
        
        /**
         * @brief Calculate the distance from the origin to the plane defined by a point and a line.
         *
         * @param point A point not on the line.
         * @param line A line not containing the point.
         * @return double The distance from the origin to the plane.
         */
        [[nodiscard]] static double calculateDistanceFromPointAndLine(
                const Point &point, const Line &line);
        
        /**
         * @brief Calculate the distance from the origin to the plane defined by three distinct
         * points.
         *
         * @param point1 The first point.
         * @param point2 The second point.
         * @param point3 The third point.
         * @return double The distance from the origin to the plane.
         */
        [[nodiscard]] static double calculateDistanceFromPoints(
                const Point &point1, const Point &point2, const Point &point3);
        
        /**
         * @brief Check if three points can define a plane.
         *
         * This function ensures that the three points are distinct and do not lie on a single line,
         * which is a necessary condition for defining a plane.
         *
         * @param point1 The first point.
         * @param point2 The second point.
         * @param point3 The third point.
         * @return true If the points are distinct and do not lie on a single line.
         * @return false Otherwise.
         */
        [[nodiscard]] static bool
        isPlaneCorrectFromPoints(const Point &point1, const Point &point2, const Point &point3);
        
        /**
         * @brief Check if a point and a normal vector can define a plane.
         *
         * This function verifies that the normal vector is not a zero vector,
         * which is necessary for a valid plane definition.
         *
         * @param point A point on the plane.
         * @param normalParam The normal vector of the plane.
         * @return true If the normal vector is not a zero vector.
         * @return false Otherwise.
         */
        [[nodiscard]] static bool
        isPlaneCorrectFromPointAndNormal(const Point &point, const Direction &normalParam);
        
        /**
         * @brief Check if a point and a line can define a plane.
         *
         * This function checks if the given point is not on the line,
         * which is a condition for the point and line to define a plane.
         *
         * @param point A point not on the line.
         * @param line A line in space.
         * @return true If the point is not on the line.
         * @return false If the point is on the line.
         */
        [[nodiscard]] static bool
        isPlaneCorrectFromPointAndLine(const Point &point, const Line &line);
        
        
        /**
         * @brief The unit vector normal to the plane. Defines the orientation of the plane.
         */
        Direction normal{};
        /**
         * @brief The distance from the origin to the plane.
         */
        double distance{};
        
        
    }; // class Plane
    
} // namespace GLESC::Math
