/**************************************************************************************************
 * @file   Line.h
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
#include "GeometryTypes.h"

namespace GLESC::Math {
    class Line {
    public:
        enum class Construct {
            PointPoint,
            PointDirection
        };
        /**
         * @brief A point in the line
         */
        Point point;
        /**
         * @brief The direction of the line (should be normalized)
         */
        Direction direction;
        
        Line(const Point& pointParam, const Direction& directionParam,
             Construct construct = Construct::PointDirection){
            
            if (construct == Construct::PointDirection) {
                setPoint(pointParam);
                setDirection(directionParam);
            } else {
                setPoint(pointParam);
                setDirectionFromPoints(pointParam, directionParam);
            
            }
        }
        
        
        [[nodiscard]] bool intersects(const Line &line) const {
            return !eq(direction.cross(line.direction).length(), 0);
        }
        
        [[nodiscard]] bool intersects(const Vec3D &otherPoint) const {
            return eq(direction.cross(otherPoint - this->point).length(), 0);
        }
        
        
    private:
            void setPoint(const Point &pointParam) {
                point = pointParam;
            }
            
            void setDirection(const Direction &directionParam) {
                direction = directionParam;
            }
            
            void setDirectionFromPoints(const Point &pointParam, const Point &otherPoint) {
                direction = otherPoint - pointParam;
            }
    };
}