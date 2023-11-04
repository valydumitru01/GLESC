/******************************************************************************
 * @file   MatrixAlgorithm.h
 * @author Valentin Dumitru
 * @date   2023-10-31
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cstddef>
#include <iostream>
#include <engine/core/exceptions/core/math/MathException.h>

template<typename Type, size_t N, size_t M>
class Matrix;

namespace MatrixAlgorithms {
    template<typename Type, size_t N>
    inline Matrix<Type, N, N> gaussianInverse(const Matrix<Type, N, N> &inputMatrix) {
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
                    throw MathException("Matrix is singular (non-invertible)");
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
                if (i == j)
                    continue;
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
    
    // Forward declaration of cofactor for recursive call
    template<typename Type, size_t N, size_t M>
    Type cofactor(const Matrix<Type, N, M> &matrix, size_t row, size_t col);
    
    template<class Type, size_t N, size_t M>
    Type laplaceExpansionDeterminant(const Matrix<Type, N, M> &matrix) {
        if constexpr (N == 1) {
            return matrix[0][0];
        } else if constexpr (N == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else if constexpr (N == 3 && M == 3) {
            return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                   matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                   matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        } else if constexpr (N == 4 && M == 4) {
            Type det;
            det = matrix[0][0] *
                  (matrix[1][1] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) -
                   matrix[1][2] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) +
                   matrix[1][3] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]));
            
            det -= matrix[0][1] *
                   (matrix[1][0] * (matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2]) -
                    matrix[1][2] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) +
                    matrix[1][3] * (matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0]));
            
            det += matrix[0][2] *
                   (matrix[1][0] * (matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1]) -
                    matrix[1][1] * (matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0]) +
                    matrix[1][3] * (matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0]));
            
            det -= matrix[0][3] *
                   (matrix[1][0] * (matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1]) -
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
    
    template<class Type, size_t N, size_t M>
    Type cofactor(const Matrix<Type, N, M> &matrix, size_t row, size_t col) {
        Matrix<Type, N - 1, N - 1> subMatrix;
        
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
    Matrix<T, 3, 3> rotate2D(const Matrix<T, 3, 3> &matrix, T dgrs) {
        Matrix<T, 3, 3> result(matrix);
        T c = cos(dgrs);
        T s = sin(dgrs);
        
        Matrix<T, 3, 3> rotation = {{T(c), T(-s), T(0)},
                                    {T(s), T(c),  T(0)},
                                    {T(0), T(0),  T(1)}};
        return result * rotation;
    }
    
    template<typename T>
    Matrix<T, 4, 4> rotate3D(const Matrix<T, 4, 4> &matrix, Vector<T, 3> dgrs) {
        Matrix<T, 4, 4> result(matrix);
        T cx = cos(dgrs.getX());
        T sx = sin(dgrs.getX());
        T cy = cos(dgrs.getY());
        T sy = sin(dgrs.getY());
        T cz = cos(dgrs.getZ());
        T sz = sin(dgrs.getZ());
        
        
        Matrix<T, 4, 4> rotationX = {{T(1), T(0),  T(0),   T(0)},
                                     {T(0), T(cx), T(-sx), T(0)},
                                     {T(0), T(sx), T(cx),  T(0)},
                                     {T(0), T(0),  T(0),   T(1)}};
        
        Matrix<T, 4, 4> rotationY = {{T(cy),  T(0), T(sy), T(0)},
                                     {T(0),   T(1), T(0),  T(0)},
                                     {T(-sy), T(0), T(cy), T(0)},
                                     {T(0),   T(0), T(0),  T(1)}};
        
        Matrix<T, 4, 4> rotationZ = {{T(cz), T(-sz), T(0), T(0)},
                                     {T(sz), T(cz),  T(0), T(0)},
                                     {T(0),  T(0),   T(1), T(0)},
                                     {T(0),  T(0),   T(0), T(1)}};
        return rotationX * rotationY * rotationZ * result;
    }
    
    template<typename T>
    Matrix<T, 3, 3> lookAt2D(const Matrix<T, 3, 3> &matrix, const Vector<T, 2> &target) {
        Vector<T, 2> eye(matrix[0][2], matrix[1][2]);
        Vector<T, 2> direction = target - eye;
        T angle = atan2(direction[1], direction[0]);
        return rotate2D(matrix, angle);
    }
    
    template<typename T>
    Matrix<T, 4, 4> lookAt3D(const Matrix<T, 4, 4> &matrix,
                             const Vector<T, 3> &target,
                             const Vector<T, 3> &up) {
        Vector<T, 3> eye(matrix[0][3], matrix[1][3], matrix[2][3]);
        Vector<T, 3> zAxis = (eye - target).normalize();
        Vector<T, 3> xAxis = up.cross(zAxis).normalize();
        Vector<T, 3> yAxis = zAxis.cross(xAxis).normalize();
        
        Matrix<T, 4, 4> result(matrix);
        
        Matrix<T, 4, 4> lookRotation = {{xAxis[0], xAxis[1], xAxis[2], T(0)},
                                        {yAxis[0], yAxis[1], yAxis[2], T(0)},
                                        {zAxis[0], zAxis[1], zAxis[2], T(0)},
                                        {T(0),     T(0),     T(0),     T(1)}};
        
        return lookRotation * result;
    }
    
    
}; // class MatrixAlgorithm