/**************************************************************************************************
 * @file   Line.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
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
         * @param pointParam The point in the line
         * @param pointOrDir The second point or the direction of the line
         * @param construct The type of construction
         */
        Line(const Point& pointParam,
             const Vec3F& pointOrDir,
             Construct construct = Construct::PointDirection);

        Line() = default;

        void setPoint(const Point& pointParam);
        /**
         * @brief Set the Direction vector
         * @details This accepts any vector, but it will normalize it.
         * @param directionParam
         */
        void setDirection(const Direction& directionParam);

        /**
         * @brief Get the Direction vector
         * @details This will return the normalized direction vector.
         * @return const Direction&
         */
        [[nodiscard]] const Direction& getDirection() const { return direction; }

        /**
         * @brief Get the Point object
         * @return const Point&
         */
        [[nodiscard]] const Point& getPoint() const { return point; }

        /**
         * @brief Check if a line intersects with another line.
         * @brief This function checks if the lines intersect by checking if the cross product of the directions is not
         * the zero vector. It also uses an epsilon value to account for floating point errors.
         * @param line The line to check for intersection.
         * @return true If the lines intersect.
         * @return false If the lines do not intersect.
         */
        [[nodiscard]] bool intersects(const Line& line) const;

        /**
         * @brief Check if a line intersects with a point.
         * @brief This function checks if the point is on the line by checking if the cross product of the direction of
         * the line and the vector from the point to the line is the zero vector. It uses an epsilon value to account
         * for floating point errors.
         * @param pointParam The point to check for intersection.
         * @return true If the point is on the line.
         * @return false If the point is not on the line.
         */
        [[nodiscard]] bool intersects(const Point& pointParam) const;

        /**
         * @brief Get the distance from a point to the line.
         * @param pointParam The point to calculate the distance to.
         * @return Distance The distance from the point to the line.
         */
        [[nodiscard]] Distance distance(const Point& pointParam) const;

    private:
        /**
         * @brief Set the direction of the line from two points.
         * @param pointParam The point in the line
         * @param otherPoint The second point
         */
        void setDirectionFromPoints(const Point& pointParam, const Point& otherPoint);

        /**
        * @brief A point in the line
        */
        Point point{{0, 0}};
        /**
         * @brief The direction of the line
         * @details This is normalized when calculated, set or modified. This way the direction can be get with the
         * getter without having to normalize it every time.
         */
        Direction direction{{0, 1}};
    };
}
