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
#include "engine/core/math/algebra/matrix/MatrixAlgorithms.h"
#include "engine/core/math/algebra/vector/VectorTypes.h"
#include "engine/core/math/algebra/matrix/MatrixTypes.h"

namespace GLESC::Math {
    class VectorMixedAlgorithms {
    public:
        // =============================================================================================================
        // ========================================= Vector operations =================================================
        // =============================================================================================================
        
        
        
        
        /**
         * @brief Checks if points are collinear.
         *
         * @tparam Type Data type of the points (e.g., double, float).
         * @tparam N Dimension of space.
         * @param referencePoint Reference for forming direction vectors.
         * @param points Points to be checked for collinearity.
         * @return true if points are collinear, false otherwise.
         */
        template<typename Type, size_t N>
        static inline bool areCollinear(const VectorData<Type, N> &referencePoint,
                                        const std::vector<const VectorData<Type, N> *> &points) {
            if (points.size() < 2) {
                return true;
            }
            
            // Create a 2D array to store the vectors from referencePoint to each point
            MatrixData<Type, N, N - 1> vectors;
            for (size_t i = 0; i < points.size(); ++i) {
                for (size_t j = 0; j < N; ++j) {
                    vectors[j][i] = points[i]->at(j) - referencePoint[j];
                }
            }
            
            // Use the existing rank function to determine if the vectors are collinear
            return MatrixAlgorithms::gaussianElimination(vectors).rank == 1;
        }
    }; // class VectorAlgorithms
} // namespace GLESC::Math