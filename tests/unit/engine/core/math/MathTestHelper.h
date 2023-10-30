/******************************************************************************
 * @file   MathTestHelper.h
 * @author Valentin Dumitru
 * @date   2023-10-26
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include "engine/core/math/Math.h"
#include "engine/core/math/Matrix.h"

#define EXPECT_EQ_F(a, b) \
    EXPECT_NEAR(a,b,GLESC::Math::FLOAT_COMPARISON_EPSILON \
    *std::max(static_cast<float>(std::abs(a)),static_cast<float>(std::abs(b))))
#define EXPECT_EQ_D(a, b) \
    ASSERT_NEAR(a,b,GLESC::Math::DOUBLE_COMPARISON_EPSILON*std::max(std::abs(a),std::abs(b)))


#define EXPECT_EQ_CUSTOM(a, b) \
    do {                       \
        if (std::is_same_v<decltype(a), float>) \
            EXPECT_NEAR((a), (b),               \
            GLESC::Math::FLOAT_COMPARISON_EPSILON \
            * std::max(static_cast<float>(std::fabs(a)), static_cast<float>(std::fabs(b)))); \
        else if (std::is_same_v<decltype(a), double>) \
            EXPECT_NEAR((a), (b),               \
            GLESC::Math::DOUBLE_COMPARISON_EPSILON \
            * std::max(static_cast<double>(std::fabs(a)), static_cast<double>(std::fabs(b)))); \
        else \
            EXPECT_EQ((a), (b)); \
    } while (false)

#define EXPECT_EQ_MAT(a, b) \
    do {                    \
        std::cout<< "Comparing matrices:\n"; \
        std::cout<< "Left matrix: \n" << a.toString(); \
        std::cout<< "Right matrix: \n" << b.toString(); \
        for (size_t i = 0; i < a.rows(); ++i) \
            for (size_t j = 0; j < a.cols(); ++j) \
                EXPECT_EQ_CUSTOM((a).get(i, j), (b).get(i, j)); \
        std::cout<< "Matrices are equal\n"; \
    } while (false)

#define EXPECT_EQ_VEC(a, b) \
    do { \
        for (size_t i = 0; i < a.size(); ++i) \
            EXPECT_EQ_CUSTOM((a).get(i), (b).get(i)); \
    } while (false)


template<typename Type, size_t N>
inline Matrix<Type, N, N> gaussianInverse(const Matrix<Type, N, N>& inputMatrix) {
    Matrix<Type, N, 2 * N> augmentedMatrix; // Resized to hold original and identity matrix
    Matrix<Type, N, N> identityMatrix; // Initialize with identity matrix
    Matrix<Type, N, N> inverseResult;
    
    // Initialize identityMatrix
    for (size_t i = 0; i < N; ++i)
        identityMatrix[i][i] = 1;
    
    // Augment the original matrix with identity matrix
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            augmentedMatrix[i][j] = inputMatrix[i][j];
            augmentedMatrix[i][N + j] = identityMatrix[i][j];
        }
    }
    
    // Perform Gaussian Elimination
    for (size_t i = 0; i < N; ++i) {
        // Adding checks for singular (non-invertible) matrix
        if (augmentedMatrix[i][i] == 0) {
            // Search for a row with non-zero entry in current column
            size_t swapRow = i + 1;
            while (swapRow < N && augmentedMatrix[swapRow][i] == 0)
                ++swapRow;
            
            // If no such row found, then all entries in this column are 0
            if (swapRow == N) {
                std::cout << "Matrix is singular (non-invertible)\n";
                return inverseResult;
            }
            
            // Swap the current row with the found non-zero entry row
            for (size_t j = 0; j < 2 * N; ++j)
                std::swap(augmentedMatrix[i][j], augmentedMatrix[swapRow][j]);
        }
        
        // Scale the row
        Type rowScale = Type(1) / augmentedMatrix[i][i];
        for (size_t j = 0; j < 2 * N; ++j) {
            augmentedMatrix[i][j] *= rowScale;
        }
        
        // Eliminate other entries in this column
        for (size_t j = 0; j < N; ++j) {
            if (i == j) continue;
            Type scale = augmentedMatrix[j][i];
            for (size_t k = 0; k < 2 * N; ++k) {
                augmentedMatrix[j][k] -= scale * augmentedMatrix[i][k];
            }
        }
    }
    
    // Extract the inverse matrix from the augmented matrix
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j)
            inverseResult[i][j] = augmentedMatrix[i][N + j];
    
    return inverseResult;
}