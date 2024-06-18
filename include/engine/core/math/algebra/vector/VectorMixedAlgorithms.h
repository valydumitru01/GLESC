/******************************************************************************
 * @file   VectorAlgorithms.h
 * @author Valentin Dumitru
 * @date   2023-10-31
 * @brief  This is needed to avoid circular dependencies between MatrixAlgorithms and VectorAlgorithms.
 * The circular dependency arrives due to the fact that MatrixMixedAlgorithms uses vector operations and
 * VectoMixedAlgorithms uses matrix operations. For example, the collinearity of two vectors is checked making use of a
 * matrix. Matrix operations could be implemented inside VectorAlgorithms, but this would be a bad design choice. The
 * solution is to create a new class VectorBasicAlgorithms that contains only the basic vector operations.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cstddef>
#include <vector>
#include "engine/core/math/algebra/vector/VectorTypes.h"
#include "engine/core/math/algebra/vector/VectorAlgorithms.h"
#include "engine/core/math/algebra/matrix/MatrixTypes.h"

namespace GLESC::Math {
    class VectorMixedAlgorithms {
    public:
        // =============================================================================================================
        // ========================================= Vector operations =================================================
        // =============================================================================================================
        template<typename Type, size_t N>
        static void
        vectorToMatrix(const VectorData<Type, N> &vector, MatrixData<Type, N, 1> &matrix) {
            for (size_t i = 0; i < N; ++i) {
                matrix[i][0] = vector[i];
            }
        }
        /**
         * @brief Checks if points are collinear.
         * @details This function checks if a set of points are collinear.
         * The points are collinear if cross product of the direction vectors from the reference point to each point is
         * the zero vector.
         * @tparam Type Data type of the points (e.g., double, float).
         * @param p1 First point.
         * @param p2 Second point.
         * @param p3 Third point.
         */
        template <typename Type>
        static bool areCollinear(const VectorData<Type, 3>& p1, const VectorData<Type, 3>& p2,
                                 const VectorData<Type, 3>& p3) {
            // Compute two vectors from the points
            VectorData<Type, 3> v1;
            VectorAlgorithms::vectorSub(p2, p1, v1);
            VectorData<Type, 3> v2;
            VectorAlgorithms::vectorSub(p3, p1, v2);

            // Early return if either vector is zero, indicating two points are the same
            // and therefore collinear with any third point
            if (VectorAlgorithms::isZero(v1) || VectorAlgorithms::isZero(v2)) {
                return true;
            }

            // Calculate the cross product of v1 and v2
            VectorData<Type, 3> crossProduct;
            VectorAlgorithms::crossProduct(v1, v2, crossProduct);

            // If the cross product is almost (0,0,0), the points are collinear
            return VectorAlgorithms::isZero(crossProduct);
        }

        /**
         * @brief Checks if points are collinear.
         * @details This function checks if a set of points are collinear.
         * @see areCollinear(p1, p2, p3)
         * @tparam Type Data type of the points (e.g., double, float).
         * @tparam N Dimension of space.
         * @param referencePoint Reference for forming direction vectors.
         * @param points Points to be checked for collinearity.
         * @return true if points are collinear, false otherwise.
         */
        template <typename Type>
        static bool areCollinear(const VectorData<Type, 3>& referencePoint,
                                 const std::vector<const VectorData<Type, 3>*>& points) {
            if (points.size() < 2) {
                // Fewer than two points, trivially collinear
                return true;
            }


            // Iterate over each set of three points including the reference point
            for (size_t i = 0; i < points.size() - 1; ++i) {
                for (size_t j = i + 1; j < points.size(); ++j) {
                    // Use the three-point collinearity check
                    if (!VectorMixedAlgorithms::areCollinear(referencePoint, *points[i], *points[j])) {
                        return false;
                    }
                }
            }

            // If all direction vectors are parallel, the points are collinear
            return true;
        }
    }; // class VectorAlgorithms
} // namespace GLESC::Math
