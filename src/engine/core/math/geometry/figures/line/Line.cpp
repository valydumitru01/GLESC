#include "engine/core/math/geometry/figures/line/Line.h"


using namespace GLESC::Math;

Line::Line(const Point& pointParam,
           const Vec3F& pointOrDir,
           Construct construct /*= Construct::PointDirection */) {
    if (construct == Construct::PointDirection) {
        setPoint(pointParam);
        setDirection(pointOrDir);
    }
    else {
        setPoint(pointParam);
        setDirectionFromPoints(pointParam, pointOrDir);
    }
}


bool Line::intersects(const Line& line) const {
    return !eq(direction.cross(line.direction).length(), 0);
}

bool Line::intersects(const Point& pointParam) const {
    return eq(distance(pointParam), 0);
}

Distance Line::distance(const Point& pointParam) const {
    // Calculate the cross product vector
    auto crossProduct = direction.cross(pointParam - this->point);

    // Return the length of the cross product vector,
    // which represents the area of the parallelogram formed by the two vectors
    // and is equal to the distance times the length of the direction vector
    // Because the direction vector is normalized, its length is 1, and the length of the cross product
    // is the distance from the point to the line.
    return crossProduct.length();
}

void Line::setPoint(const Point& pointParam) {
    point = pointParam;
}

void Line::setDirection(const Direction& directionParam) {
    D_ASSERT_NOT_EQUAL(directionParam.length(), 0, "Direction cannot be a zero vector");
    direction = directionParam.normalize();
}

void Line::setDirectionFromPoints(const Point& pointParam, const Point& otherPoint) {
    auto dir = otherPoint - pointParam;
    D_ASSERT_NOT_EQUAL(dir.length(), 0, "Direction cannot be a zero vector");
    direction = dir.normalize();
}
