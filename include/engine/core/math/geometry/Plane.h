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

#include "engine/core/math/Vector.h"
#include "Line.h"
#include "GeometryTypes.h"


namespace GLESC::Math {
    class Plane {
    public:
        /**
         * @brief Construct a new Plane object.
         * @details The default constructor creates a plane with the normal vector (0, 0, 0) and
         * distance 0. Constructs a "zero plane".
         */
        Plane() : normal(0, 0, 0), distance(0) {};
        
        /**
         * @brief Construct a new Plane object from a normal vector and a distance.
         * @details The normal vector is normalized if its length is greater than 1.
         * The normal cannot be a zero vector.
         * The distance is the distance from the origin to the plane. It can be any real number
         * (positive, negative or zero).
         * @param normalParam The normal vector of the plane.
         * @param distanceParam The distance from the origin to the plane.
         */
        Plane(const Direction& normalParam, double distanceParam) {
            setNormal(normalParam);
            setDistance(distanceParam);
        }
        
        /**
         * @brief
         * @param point
         * @param normalParam
         */
        Plane(const Point &point, const Direction &normalParam) :
                Plane(normalParam, calculateDistanceFromPointAndNormal(point, normalParam)) {
            D_ASSERT_TRUE(isPlaneCorrectFromPointAndNormal(point, normalParam),
                          "Invalid plane definition from point and normal");
        }
        
        Plane(const Point &point1, const Point &point2, const Point &point3) :
                Plane((calculateNormalFromPoints(point1, point2, point3)),
                      calculateDistanceFromPoints(point1, point2, point3)) {
            
            D_ASSERT_TRUE(isPlaneCorrectFromPoints(point1, point2, point3),
                          "Invalid plane definition from 3 points");
        }
        
        Plane(const Point &point, const Line &line) :
                Plane(calculateNormalFromPointAndLine(point, line),
                      calculateDistanceFromPointAndLine(point, line)) {
            D_ASSERT_TRUE(isPlaneCorrectFromPointAndLine(point, line),
                          "Invalid plane definition from point and line");
        }
        
        Plane(const Plane &plane) = default;
        
        Plane(Plane &&plane) noexcept = default;
        
        Plane &operator=(const Plane &plane) = default;
        
        Plane &operator=(Plane &&plane) noexcept = default;
        
        ~Plane() = default;
        
        void setNormal(const Direction &normalParam) {
            D_ASSERT_FALSE(eq(normalParam.length(), 0),
                           "Normal cannot be a zero vector");
            
            if (normalParam.length() > 1)
                normal = normalParam.normalize();
            
            normal = normalParam;
        }
        
        void setDistance(double distanceParam) {
            distance = distanceParam;
        }
        
        
        [[nodiscard]] const Direction &getNormal() const {
            return normal;
        }
        
        [[nodiscard]] double getDistance() const {
            return distance;
        }
        
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
        [[nodiscard]] double distanceToPoint(const Point &point) const {
            return normal.dot(point) + distance;
        }
        
        [[nodiscard]] bool intersects(const Point &point) const {
            return eq(distanceToPoint(point), 0);
        }
        
        [[nodiscard]] bool intersects(const Plane &plane) const {
            return eq(normal.dot(plane.normal), 0);
        }
        
        [[nodiscard]] bool intersects(const Point &point, const Direction &direction) const {
            return eq(normal.dot(direction), 0);
        }
        
        [[nodiscard]] bool intersects(const Line &line) const {
            return normal.dot(line.direction) != 0;
        }
        
        [[nodiscard]] bool intersects(const Line &line, Point &intersectionPoint) const {
            if (!intersects(line)) {
                return false;
            }
            double t = -(normal.dot(line.point) + distance) / normal.dot(line.direction);
            intersectionPoint = line.point + line.direction * t;
            return true;
        }
        
        bool operator==(const Plane &other) const {
            return eq(normal.dot(other.normal), 1) && eq(distance, other.distance);
        }
    
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
                const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) {
            Direction vectorFromFirstToSecond = secondPoint - firstPoint;
            Direction vectorFromFirstToThird = thirdPoint - firstPoint;
            return vectorFromFirstToSecond.cross(vectorFromFirstToThird).normalize();
        }
        
        /**
         * @brief Calculate the normal vector of the plane defined by a point and a line.
         *
         * @param point A point not on the line.
         * @param line A line not containing the point.
         * @return Direction The normal vector of the plane.
         */
        [[nodiscard]] static Direction calculateNormalFromPointAndLine(
                const Point& point, const Line& line) {
            Direction vectorFromLineToPoint = point - line.point;
            return line.direction.cross(vectorFromLineToPoint).normalize();
        }
        
        /**
         * @brief Calculate the distance from the origin to the plane defined by a point on the
         * plane and the plane's normal vector.
         *
         * @param point A point on the plane.
         * @param normal The normal vector of the plane.
         * @return double The distance from the origin to the plane.
         */
        [[nodiscard]] static double calculateDistanceFromPointAndNormal(
                const Point& point, const Direction& normal) {
            return -normal.dot(point);
        }
        
        /**
         * @brief Calculate the distance from the origin to the plane defined by a point and a line.
         *
         * @param point A point not on the line.
         * @param line A line not containing the point.
         * @return double The distance from the origin to the plane.
         */
        [[nodiscard]] static double calculateDistanceFromPointAndLine(
                const Point& point, const Line& line) {
            Direction vectorFromLineToPoint = point - line.point;
            Direction normal = line.direction.cross(vectorFromLineToPoint).normalize();
            return -normal.dot(point);
        }
        
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
                const Point& point1, const Point& point2, const Point& point3) {
            Direction normal = calculateNormalFromPoints(point1, point2, point3);
            return -normal.dot(point1);
        }
        
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
        [[nodiscard]] static bool isPlaneCorrectFromPoints(const Point &point1, const Point &point2, const Point &point3) {
            bool pointsAreDifferent = !(point1 == point2 || point1 == point3 || point2 == point3);
            bool pointsDontLieOnLine = !Line(point1, point2).intersects(point3);
            return pointsAreDifferent && pointsDontLieOnLine;
        }
        
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
        [[nodiscard]] static bool isPlaneCorrectFromPointAndNormal(const Point &point, const Direction &normalParam) {
            bool isNormalCorrect = !eq(normalParam.length(), 0);
            return isNormalCorrect;
        }
        
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
        [[nodiscard]] static bool isPlaneCorrectFromPointAndLine(const Point &point, const Line &line) {
            bool pointIsNotOnLine = !line.intersects(point);
            return pointIsNotOnLine;
        }
        
        
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
