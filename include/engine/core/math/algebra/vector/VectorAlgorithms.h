/******************************************************************************
 * @file   VectorAlgorithms.h
 * @author Valentin Dumitru
 * @date   2023-10-31
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cstddef>
#include <vector>
#include "engine/core/math/algebra/matrix/MatrixBasicAlgorithms.h"
#include "engine/core/math/algebra/vector/VectorTypes.h"
#include "engine/core/math/algebra/matrix/MatrixTypes.h"

namespace GLESC::Math {
    class VectorAlgorithms {
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
            return MatrixBasicAlgorithms::gaussianEliminationData(vectors).rank == 1;
        }
    }; // class VectorAlgorithms
} // namespace GLESC::Math