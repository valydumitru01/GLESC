/**************************************************************************************************
 * @file   Plane.cpp
 * @author Valentin Dumitru
 * @date   2023-12-24
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/core/math/geometry/figures/plane/Plane.h"

using namespace GLESC::Math;

Plane::Plane() : Plane(Direction(0, 0, 1), 0) {}


Plane::Plane(const Direction& normalParam, double distanceParam) {
    setNormal(normalParam);
    setDistance(distanceParam);
}

Plane::Plane(const Point& point, const Direction& normalParam) {
    setNormal(normalParam);
    setDistance(calculateDistanceFromPointAndNormal(point, normalParam));
}

Plane::Plane(const Point& point1, const Point& point2, const Point& point3) {
    D_ASSERT_TRUE((point1 != point2 && point1 != point3 && point2 != point3), "Points must be different");
    D_ASSERT_TRUE(!VectorMixedAlgorithms::areCollinear(point1.data, point2.data, point3.data),
                  "Points must not lie on the same line");

    setNormal(calculateNormalFromPoints(point1, point2, point3));
    setDistance(calculateDistanceFromPoints(point1, point2, point3));
}

Plane::Plane(const Point& point, const Line& line) {
    D_ASSERT_TRUE(!line.intersects(point), "Point must not lie on the line");
    setNormal(calculateNormalFromPointAndLine(point, line));
    setDistance(calculateDistanceFromPointAndLine(point, line));
}

void Plane::setNormal(const Direction& normalParam) {
    D_ASSERT_FALSE(normalParam.isZero(), "Normal cannot be a zero vector");

    if (normalParam.length() > 1)
        normal = normalParam.normalize();
    else
        normal = normalParam;
}

void Plane::setDistance(double distanceParam) {
    distance = distanceParam;
}


[[nodiscard]] const Direction& Plane::getNormal() const {
    return normal;
}

[[nodiscard]] double Plane::getDistance() const {
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
[[nodiscard]] double Plane::distanceToPoint(const Point& point) const {
    return normal.dot(point) + distance;
}

[[nodiscard]] bool Plane::intersects(const Point& point) const {
    return eq(distanceToPoint(point), 0);
}

[[nodiscard]] bool Plane::intersects(const Plane& plane) const {
    bool isParallel = normal.isParallel(plane.normal);
    // When the dot product is 1, the planes are parallel
    // So we check if the dot product is not 1, which means the planes are not parallel
    return !isParallel ||
        // And if they are parallel we check if the distance between the planes is 0,
        // which means the planes are the same, so they intersect
        (eq(distance, plane.distance) && isParallel);
}

[[nodiscard]] bool Plane::intersects(const Line& line) const {
    // Check if the line direction is parallel to the plane normal
    // This is determined by checking if their dot product is close to zero
    double dotProduct = normal.dot(line.getDirection());
    bool isParallel = eq(dotProduct, 0);

    if (isParallel) {
        // If the line is parallel to the plane, check if any point on the line lies in the plane
        // Use the distance formula: d = (n ⋅ p) + D
        // If the distance is close to 0, the line lies in the plane
        return eq(abs(distanceToPoint(line.getPoint())), 0);
    }
    else {
        // If the line is not parallel to the plane, it will intersect the plane at some point
        return true;
    }
}

[[nodiscard]] bool Plane::intersects(const Line& line, Point& intersectionPoint) const {
    if (!intersects(line)) {
        return false;
    }
    double t = -(normal.dot(line.getPoint()) + distance) / normal.dot(line.getDirection());
    intersectionPoint = line.getPoint() + line.getDirection() * t;
    return true;
}

bool Plane::operator==(const Plane& other) const {
    return eq(normal.dot(other.normal), 1) && eq(distance, other.distance);
}


Direction Plane::calculateNormalFromPoints(const Point& firstPoint,
                                           const Point& secondPoint,
                                           const Point& thirdPoint) {
    Direction vectorFromFirstToSecond = secondPoint - firstPoint;
    Direction vectorFromFirstToThird = thirdPoint - firstPoint;
    return vectorFromFirstToSecond.cross(vectorFromFirstToThird).normalize();
}


Direction Plane::calculateNormalFromPointAndLine(const Point& point, const Line& line) {
    Direction vectorFromLineToPoint = point - line.getPoint();
    return line.getDirection().cross(vectorFromLineToPoint).normalize();
}


double Plane::calculateDistanceFromPointAndNormal(const Point& point, const Direction& normal) {
    return -normal.dot(point);
}


double Plane::calculateDistanceFromPointAndLine(const Point& point, const Line& line) {
    Direction vectorFromLineToPoint = point - line.getPoint();
    Direction normal = line.getDirection().cross(vectorFromLineToPoint).normalize();
    return -normal.dot(point);
}

double
Plane::calculateDistanceFromPoints(const Point& point1, const Point& point2, const Point& point3) {
    Direction normal = calculateNormalFromPoints(point1, point2, point3);
    return -normal.dot(point1);
}





