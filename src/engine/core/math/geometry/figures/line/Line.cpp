/**************************************************************************************************
 * @file   Line.cpp
 * @author Valentin Dumitru
 * @date   2023-12-25
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/core/math/geometry/figures/line/Line.h"


using namespace GLESC::Math;
Line::Line(const Point& pointParam, const Direction& directionParam,
     Construct construct /*= Construct::PointDirection */){
    
    if (construct == Construct::PointDirection) {
        setPoint(pointParam);
        setDirection(directionParam);
    } else {
        setPoint(pointParam);
        setDirectionFromPoints(pointParam, directionParam);
    }
}


bool Line::intersects(const Line &line) const {
    return !eq(direction.cross(line.direction).length(), 0);
}

bool Line::intersects(const Vec3D &pointParam) const {
    return GLESC::Math::eq(direction.cross(pointParam - this->point).length(), 0);
}

void Line::setPoint(const Point &pointParam) {
    point = pointParam;
}

void Line::setDirection(const Direction &directionParam) {
    D_ASSERT_NOT_EQUAL(directionParam.length(), 0, "Direction cannot be a zero vector");
    direction = directionParam.normalize();
}

void Line::setDirectionFromPoints(const Point &pointParam, const Point &otherPoint) {
    direction = otherPoint - pointParam;
}
