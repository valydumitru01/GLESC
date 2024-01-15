/******************************************************************************
 * @file   MatrixAlgorithm.h
 * @author Valentin Dumitru
 * @date   2023-10-31
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cstddef>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include "engine/core/math/Math.h"
#include "engine/core/exceptions/core/math/MathException.h"

namespace MatrixAlgorithms {
    /**
     * @brief Dot product matrix multiplication.
     * @tparam Type The data type of the matrix and vector elements (e.g., float, double).
     * @tparam N The number of rows of the first matrix.
     * @tparam M The number of columns of the first matrix.
     * @tparam X The number of columns of the second matrix.
     * @param matrix1 The first matrix.
     * @param matrix2 The second matrix.
     * @param result The result matrix.
     */
    template<typename Type, size_t N, size_t M, size_t X>
    void matrixMul(const Type (&matrix1)[N][M], const Type (&matrix2)[M][X], Type (&result)[N][N]) {
        S_ASSERT(M == X, "Matrix multiplication requires the number of columns of the first matrix to be equal to "
                         "the number of rows of the second matrix.");
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < X; ++j) {
                // Set the value to zero before adding the products
                result[i][j] = 0;
                for (size_t k = 0; k < M; ++k) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
    }
    
    
    template<typename Type, size_t N>
    struct GaussianEliminationExtractedData {
        GaussianEliminationExtractedData(const Type (&inverse)[N][N], unsigned int rank, Type determinant) :
                inverse(inverse), rank(rank), determinant(determinant) {}
        
        Type inverse[N][N];
        unsigned int rank;
        Type determinant;
    };
    
    template<typename Type, size_t N, size_t M>
    struct GaussianEliminationTrackedResult {
        std::array<std::array<Type, M>, N> resultMatrix;
        std::map<std::tuple<size_t, size_t>, std::tuple<size_t, size_t>> rowSwaps;
        std::vector<std::tuple<size_t, size_t, Type>> rowMultipleAdditions;
        std::vector<std::tuple<size_t, Type>> rowMultiplications;
    };
    
    template<typename Type, size_t N, size_t M>
    GaussianEliminationTrackedResult<Type, N, M> gaussianElimination(const Type (&inputMatrix)[N][M]) {
        GaussianEliminationTrackedResult<Type, N, M> tracking;
        
        // Copy input matrix to tracking result matrix
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                tracking.resultMatrix[i][j] = inputMatrix[i][j];
            }
        }
        
        // Gaussian elimination process
        for (size_t i = 0; i < N; ++i) {
            // Search for maximum in this column
            size_t maxRow = i;
            for (size_t k = i + 1; k < N; ++k) {
                if (GLESC::Math::abs(tracking.resultMatrix[k][i]) >
                    GLESC::Math::abs(tracking.resultMatrix[maxRow][i])) {
                    maxRow = k;
                }
            }
            
            // Swap maximum row with current row (column by column)
            for (size_t k = i; k < M; ++k) {
                std::swap(tracking.resultMatrix[maxRow][k], tracking.resultMatrix[i][k]);
            }
            tracking.rowSwaps[{i, maxRow}] = {maxRow, i};
            
            // Make all rows below this one 0 in current column
            for (size_t k = i + 1; k < N; ++k) {
                Type c = -tracking.resultMatrix[k][i] / tracking.resultMatrix[i][i];
                for (size_t j = i; j < M; ++j) {
                    if (i == j) {
                        tracking.resultMatrix[k][j] = 0;
                    } else {
                        tracking.resultMatrix[k][j] += c * tracking.resultMatrix[i][j];
                    }
                }
                tracking.rowMultipleAdditions.push_back({k, i, c});
            }
        }
        
        // Normalize each row
        for (size_t i = 0; i < N; ++i) {
            Type c = 1 / tracking.resultMatrix[i][i];
            for (size_t j = 0; j < M; ++j) {
                tracking.resultMatrix[i][j] *= c;
            }
            tracking.rowMultiplications.push_back({i, c});
        }
        
        return tracking;
    }
    
    template<typename Type, size_t N>
    inline GaussianEliminationExtractedData<Type, N> gaussianEliminationData(const Type (&inputMatrix)[N][N]) {
        Type augmentedMatrix[N][N * 2]; // Resized to hold original and identity matrix
        Type identityMatrix[N][N];
        Type inverseResult[N][N];
        
        // Initialize identity matrix
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j)
                identityMatrix[i][j] = (i == j) ? Type(1) : Type(0);
        }
        
        
        // Augment the original matrix with identity matrix
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                augmentedMatrix[i][j] = inputMatrix[i][j];
                augmentedMatrix[i][N + j] = identityMatrix[i][j];
            }
        }
        
        // Perform Gaussian elimination on the augmented matrix
        auto result = gaussianElimination(augmentedMatrix);
        
        // Extract the inverse matrix from the augmented matrix
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                inverseResult[i][j] = augmentedMatrix[i][N + j];
        
        // Extract the rank of the matrix
        // Rank is the number of non-zero rows in the matrix
        unsigned int rank = 0;
        for (size_t i = 0; i < N; ++i) {
            bool isZeroRow = true;
            for (size_t j = 0; j < N; ++j) {
                if (augmentedMatrix[i][j] != 0) {
                    isZeroRow = false;
                    break;
                }
            }
            if (!isZeroRow)
                ++rank;
        }
        
        // Extract the determinant of the matrix
        // Determinant is the product of diagonal entries of the matrix
        // Also, the result must be multiplied by -1 if the number of row swaps is odd
        Type determinant = Type(1);
        for (size_t i = 0; i < N; ++i) {
            determinant *= augmentedMatrix[i][i];
        }
        
        bool isRowSwapOdd = result.rowSwaps.size() % 2 == 1;
        determinant *= isRowSwapOdd ? Type(-1) : Type(1);
        
        GaussianEliminationExtractedData<Type, N> extractedData;
        extractedData.rank = rank;
        extractedData.determinant = determinant;
        extractedData.inverse = inverseResult;
        return extractedData;
    }
    
    // Forward declaration of cofactor for recursive call
    template<typename Type, size_t N>
    Type cofactor(const Type (&inputMatrix)[N][N], size_t row, size_t col);
    
    template<class Type, size_t N>
    Type laplaceExpansionDeterminant(const Type (&matrix)[N][N]) {
        if constexpr (N == 1) {
            return matrix[0][0];
        } else if constexpr (N == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else if constexpr (N == 3) {
            return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                   matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                   matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        } else if constexpr (N == 4) {
            Type det;
            det = matrix[0][0] * (matrix[1][1] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) -
                                  matrix[1][2] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) +
                                  matrix[1][3] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]));
            
            det -= matrix[0][1] * (matrix[1][0] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) -
                                   matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) +
                                   matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]));
            
            det += matrix[0][2] * (matrix[1][0] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) -
                                   matrix[1][1] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) +
                                   matrix[1][3] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));
            
            det -= matrix[0][3] * (matrix[1][0] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]) -
                                   matrix[1][1] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]) +
                                   matrix[1][2] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));
            
            return det;
        } else {
            Type result = Type();
            Type sign = 1;
            
            for (size_t j = 0; j < N; ++j) {
                result += sign * matrix[0][j] * cofactor(matrix, Type(0), j);
                sign = -sign; // Alternate sign for cofactor expansion
            }
            return result;
        }
    }
    
    template<class Type, size_t N>
    Type cofactor(const Type (&matrix)[N][N], size_t row, size_t col) {
        Type subMatrix[N - 1][N - 1];
        
        size_t subI = 0;
        for (size_t i = 0; i < N; ++i) {
            if (i == row)
                continue;
            
            size_t subJ = 0;
            for (size_t j = 0; j < N; ++j) {
                if (j == col)
                    continue;
                
                subMatrix[subI][subJ] = matrix[i][j];
                subJ++;
            }
            subI++;
        }
        
        return laplaceExpansionDeterminant(subMatrix);
    }
    
    
    template<typename T>
    void rotate2D(const T (&matrix)[3][3], T dgrs, const T (&resMatrix)[3][3]) {
        T result[3][3] = {{matrix[0][0], matrix[0][1], matrix[0][2]},
                          {matrix[1][0], matrix[1][1], matrix[1][2]},
                          {matrix[2][0], matrix[2][1], matrix[2][2]}};
        T c = cos(dgrs);
        T s = sin(dgrs);
        
        T rotation[3][3] = {{T(c), T(-s), T(0)},
                            {T(s), T(c),  T(0)},
                            {T(0), T(0),  T(1)}};
        
        matrixMul(rotation, result, resMatrix);
    }
    
    /**
     * @brief Rotate a 3D matrix around the X, Y, and Z axis.
     * This function applies sequential rotations to the input matrix based on the given angles.
     * TODO: Be cautious about gimbal lock when using Euler angles.
     *   It's recommended to use quaternions for robustness.
     *
     * @tparam T The data type of the matrix and vector elements (e.g., float, double).
     * @param matrix The input 4x4 matrix that needs to be rotated.
     * @param dgrs A 3D vector containing the rotation angles (in radians) around X, Y, and Z axes
     * respectively.
     * @return A 4x4 matrix which is the result of the input matrix after the rotations.
     */
    template<typename T>
    void rotate3D(const T (&matrix)[4][4], T (&dgrs)[3], const T (&resMatrix)[4][4]) {
        T result[4][4](matrix);
        T cx = cos(dgrs[0]); // X component
        T sx = sin(dgrs[0]); // X component
        T cy = cos(dgrs[1]); // Y component
        T sy = sin(dgrs[1]); // Y component
        T cz = cos(dgrs[2]); // Z component
        T sz = sin(dgrs[2]); // Z component
        
        
        // Combine the three rotation matrices into a single matrix
        T rot[4][4] = {{cy * cz,                 -cy * sz,                sy,       T(0)},
                       {sx * sy * cz + cx * sz,  -sx * sy * sz + cx * cz, -sx * cy, T(0)},
                       {-cx * sy * cz + sx * sz, cx * sy * sz + sx * cz,  cx * cy,  T(0)},
                       {T(0),                    T(0),                    T(0),     T(1)}};
        
        matrixMul(rot, result, resMatrix);
    }
    
    template<typename T>
    void lookAt2D(const T (&matrix)[3][3], const T (&target)[2], const T (&resMatrix)[3][3]) {
        T eye[2] = {matrix[0][2], matrix[1][2]};
        T direction[2] = {target - eye};
        if (eye == target) {
            return matrix;
        }
        T angle = -atan2(direction[1], direction[0]);
        return rotate2D(matrix, angle, resMatrix);
    }
    
    template<typename T>
    void lookAt3D(const T(&matrix)[4][4], const T (&target)[3], const T (&up)[3], const T (&resMatrix)[4][4]) {
        T eye[3] = {matrix[0][3], matrix[1][3], matrix[2][3]};
        T zAxis[3] = {(eye - target).normalize()};
        T xAxis[3] = {up.cross(zAxis).normalize()};
        T yAxis[3] = {zAxis.cross(xAxis).normalize()};
        
        // Rotation matrix using the new basis vectors (inverted change of basis matrix)
        T lookRotation[4][4] = {{xAxis[0], yAxis[0], zAxis[0], 0},
                                {xAxis[1], yAxis[1], zAxis[1], 0},
                                {xAxis[2], yAxis[2], zAxis[2], 0},
                                {0,        0,        0,        1}};
        
        // Translation matrix to move the camera to the origin
        T translation[4][4] = {{1, 0, 0, -eye[0]},
                               {0, 1, 0, -eye[1]},
                               {0, 0, 1, -eye[2]},
                               {0, 0, 0, 1}};
        
        // First translate to the origin, then apply the rotation
        matrixMul(lookRotation, translation, resMatrix);
        matrixMul(resMatrix, matrix, resMatrix);
        
    }
    
    
}; // class MatrixAlgorithm