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
#include "engine/core/math/algebra/matrix/MatrixAlgorithms.h"

namespace VectorAlgorithms {
    
    
    
    /**
     * @brief Checks if points are collinear.
     *
     * @tparam ParamType Data type of the points (e.g., double, float).
     * @tparam ParamN Dimension of space.
     * @param referencePoint Reference for forming direction vectors.
     * @param points Points to be checked for collinearity.
     * @return true if points are collinear, false otherwise.
     */
    template<typename ParamType, size_t ParamN>
    bool areCollinear(const ParamType referencePoint[], const std::vector<ParamType*>& points) {
        if (points.size() < 2) {
            return true;
        }
        
        // Create a 2D array to store the vectors from referencePoint to each point
        ParamType vectors[ParamN][ParamN - 1];
        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = 0; j < ParamN; ++j) {
                vectors[j][i] = points[i][j] - referencePoint[j];
            }
        }
        
        // Use the existing rank function to determine if the vectors are collinear
        return MatrixAlgorithms::gaussianEliminationData(vectors).rank == 1;
    }
}