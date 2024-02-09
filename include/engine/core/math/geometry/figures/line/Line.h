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

#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/core/math/geometry/GeometryTypes.h"

namespace GLESC::Math {
    class Line {
    public:
        enum class Construct {
            PointPoint, PointDirection
        };
        /**
         * @brief Construct a new Line object.
         * @param pointParam
         * @param directionParam
         * @param construct
         */
        Line(const Point &pointParam,
             const Direction &directionParam,
             Construct construct = Construct::PointDirection);
        
        void setPoint(const Point &pointParam);
        /**
         * @brief Set the Direction vector
         * @details This accepts any vector, but it will normalize it.
         * @param directionParam
         */
        void setDirection(const Direction &directionParam);
        
        const Direction& getDirection() const {return direction;}
        
        const Point& getPoint() const {return point;}
        
        [[nodiscard]] bool intersects(const Line &line) const;
        
        [[nodiscard]] bool intersects(const Vec3D &pointParam) const;
    
    
    private:
        
        void setDirectionFromPoints(const Point &pointParam, const Point &otherPoint);
        
        /**
        * @brief A point in the line
        */
        Point point;
        /**
         * @brief The direction of the line
         * @details This is normalized when calculated, set or modified. This way the direction can be get with the
         * getter without having to normalize it every time.
         */
        Direction direction;
    };
}