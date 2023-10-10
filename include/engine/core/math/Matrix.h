/******************************************************************************
 * @file   Matrix.h
 * @author Valentin Dumitru
 * @date   2023-10-03
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <cmath>
#include <memory>
#include "Vector.h"
#include "engine/core/exceptions/core/math/MathException.h"


template<typename Type, size_t N, size_t M>
class Matrix {
public:
    // ================================================
    // ==================Constructors==================
    // ================================================
    
    Matrix() {
        for (size_t i = 0; i < N; ++i) {
            data[i] = Vec<Type, M>();
        }
    }
    
    explicit Matrix(Type diagonal) {
        for (size_t i = 0; i < N; ++i) {
            data[i][i] = diagonal;
        }
    }
    
    explicit Matrix(Type data[N][M]) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; j++) {
                this->data[i][j] = data[i][j];
            }
        }
    }
    
    Matrix(const std::initializer_list<std::initializer_list<Type>> &list) {
        if (list.size() != N) {
            throw MathException("Invalid matrix size");
        }
        
        size_t i = 0;
        for (const auto &row : list) {
            if (row.size() != M) {
                throw MathException("Invalid matrix size");
            }
            
            size_t j = 0;
            for (const auto &element : row) {
                data[i][j] = element;
                ++j;
            }
            ++i;
        }
    }
    // ================================================
    // ==================Operators=====================
    // ================================================
    
    
    // ==============Assignment operators==============
    
    Matrix<Type, N, M> &operator=(Matrix<double, 3ULL, 3ULL> other) {
        if (this == &other) {
            return *this;
        }
        for (size_t i = 0; i < N; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }
    
    
    Matrix<Type, N, M> &operator*=(const Matrix<Type, N, M> &rhs) {
        Matrix<Type, N, M> temp;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                temp.data[i][j] = 0;
                for (size_t k = 0; k < N; ++k) {
                    temp.data[i][j] += data[i][k] * rhs.data[k][j];
                }
            }
        }
        std::swap(data, temp.data);
        return *this;
    }
    
    Matrix<Type, N, M> &operator*=(Type scalar) {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] * scalar;
            }
        }
        std::swap(data, result.data);
    }
    
    Matrix<Type, N, M> &operator+=(const Matrix<Type, N, M> &rhs) {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                result.data[i][k] = data[i][k] + rhs.data[i][k];
            }
        }
        std::swap(data, result.data);
    }
    
    Matrix<Type, N, M> &operator-=(const Matrix<Type, N, M> &rhs) {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                result.data[i][k] = data[i][k] - rhs.data[i][k];
            }
        }
        std::swap(data, result.data);
    }
    
    Matrix<Type, N, M> &operator/=(Type scalar) {
        if (GLESC::Math::eq(scalar, 0))
            throw MathException("Division by zero");
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                result.data[i][k] = data[i][k] / scalar;
            }
        }
        std::swap(data, result.data);
    }
    
    // ==============Arithmetic Operators===================
    
    Matrix<Type, N, M> operator+(const Matrix<Type, N, M> &rhs) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] + rhs.data[i][k];
            }
        }
        return result;
    }
    
    Matrix<Type, N, M> operator-(const Matrix<Type, N, M> &rhs) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] - rhs.data[i][k];
            }
        }
        return result;
    }
    
    Matrix<Type, N, M> operator-() const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = -data[i][k];
            }
        }
        return result;
    }
    
    Vec<Type, M>
    operator*(const Vec<Type, M> &rhs) const {
        Vec<Type, M> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = 0;
            for (size_t j = 0; j < M; ++j) {
                result[i] += data[i][j] * rhs[j];
            }
        }
        return result;
    }
    
    template<size_t X>
    Matrix<Type, N, X>
    operator*(const Matrix<Type, M, X> &other) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = 0;
                for (size_t j = 0; j < N; ++j) {
                    result.data[i][k] += data[i][j] * other.data[j][k];
                }
            }
        }
        return result;
    }
    
    Matrix<Type, N, M> operator*(Type scalar) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] * scalar;
            }
        }
        return result;
    }
    
    
    Matrix<Type, N, M> operator/(Type scalar) const {
        if (GLESC::Math::eq(scalar, Type()))
            throw MathException("Division by zero");
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] / scalar;
            }
        }
        return result;
    }
    
    // ==============Access Operators===================
    Vec<Type, M> &operator[](size_t index) {
        return data[index];
    }
    
    // ==============Comparison Operators===================
    bool operator==(const Matrix<Type, N, M> &rhs) const {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                if (data[i][k] != rhs.data[i][k]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool operator!=(const Matrix<Type, N, M> &rhs) const {
        return !(*this == rhs);
    }
    
    bool operator<(const Matrix<Type, N, M> &rhs) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] >= rhs.data[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool operator>(const Matrix<Type, N, M> &rhs) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] <= rhs.data[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool operator<=(const Matrix<Type, N, M> &rhs) const {
        return !(*this > rhs);
    }
    
    bool operator>=(const Matrix<Type, N, M> &rhs) const {
        return !(*this < rhs);
    }
    
    
    // =================Matrix Functions=================
    
    Matrix<Type, N, M> transpose() {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < M; ++i) {
            for (size_t k = 0; k < N; ++k) {
                result.data[i][k] = data[k][i];
            }
        }
        return result;
    }
    
    Matrix<Type, N, M> translate(const Vec<Type, M - 1> &translation) {
        Matrix<Type, N, M> result(*this);
        for (size_t i = 0; i < N - 1; ++i) {
            result.data[i][M - 1] += translation[i];
        }
        return result;
    }
    
    Matrix<Type, N, M> scale(const Vec<Type, M - 1> &scale) {
        Matrix<Type, N, M> result(*this);
        for (size_t i = 0; i < N - 1; ++i) {
            result.data[i][i] *= scale[i];
        }
        return result;
    }
    
    Matrix<Type, N, M> rotate(const Type &degree) requires (M == 3 && N == 3) {
        Matrix<Type, N, M> result(*this);
        Type c = cos(degree), s = sin(degree);
        Matrix<Type, 3, 3> rotation = {{c, -s, 0},
                                       {s, c,  0},
                                       {0, 0,  1}};
        return result * rotation;
    }
    
    [[nodiscard]] Matrix<Type, N, M>
    rotate(const Vec<Type, 3> &degrees) const requires (M == 4 && N == 4) {
        Matrix<Type, 4, 4> result(*this);
        Matrix<Type, 4, 4> rotationX =
                {{1, 0,                   0,                    0},
                 {0, cos(degrees.getX()), -sin(degrees.getX()), 0},
                 {0, sin(degrees.getX()), cos(degrees.getX()),  0},
                 {0, 0,                   0,                    1}};
        
        Matrix<Type, 4, 4> rotationY =
                {{cos(degrees.getY()),  0, sin(degrees.getY()), 0},
                 {0,                    1, 0,                   0},
                 {-sin(degrees.getY()), 0, cos(degrees.getY()), 0},
                 {0,                    0, 0,                   1}};
        
        Matrix<Type, 4, 4> rotationZ =
                {{cos(degrees.getZ()), -sin(degrees.getZ()), 0, 0},
                 {sin(degrees.getZ()), cos(degrees.getZ()),  0, 0},
                 {0,                   0,                    1, 0},
                 {0,                   0,                    0, 1}};
        
        return rotationX * rotationY * rotationZ * result;
    }
    
    Type determinant() requires (N == 2 && M == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    
    Type determinant() requires (N == 3 && M == 3) {
        return data[0][0] *
               (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
               data[0][1] *
               (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
               data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    }
    
    Type determinant() requires (N == 4 && M == 4) {
        Type det;
        // calculate the 4x4 determinant
        // using cofactors for a 3x3 matrix
        det = data[0][0] * (
                data[1][1] *
                (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
                data[1][2] *
                (data[2][1] * data[3][3] - data[2][3] * data[3][1]) +
                data[1][3] *
                (data[2][1] * data[3][2] - data[2][2] * data[3][1]));
        
        det -= data[0][1] * (
                data[1][0] *
                (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
                data[1][2] *
                (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
                data[1][3] *
                (data[2][0] * data[3][2] - data[2][2] * data[3][0]));
        
        det += data[0][2] * (
                data[1][0] *
                (data[2][1] * data[3][3] - data[2][3] * data[3][1]) -
                data[1][1] *
                (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
                data[1][3] *
                (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
        
        det -= data[0][3] * (
                data[1][0] *
                (data[2][1] * data[3][2] - data[2][2] * data[3][1]) -
                data[1][1] *
                (data[2][0] * data[3][2] - data[2][2] * data[3][0]) +
                data[1][2] *
                (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
        
        return det;
    }
    
    Matrix<Type, N, M> inverse() requires (N == 2 && M == 2) {
        Type det = determinant();
        if (GLESC::Math::eq(det, 0))
            throw std::runtime_error("Singular matrix");
        Matrix<Type, N, M> inv;
        inv(0, 0) = data[1][1] / det;
        inv(0, 1) = -data[0][1] / det;
        inv(1, 0) = -data[1][0] / det;
        inv(1, 1) = data[0][0] / det;
        return inv;
    }
    
    Matrix<Type, N, M> inverse() requires (N == 3 && M == 3) {
        Type det = determinant();
        if (GLESC::Math::eq(det, 0)) {
            throw std::runtime_error("Singular matrix");
        }
        
        Matrix<Type, N, M> inv;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                // Calculate the sub-determinant
                int x1 = (i + 1) % 3, x2 = (i + 2) % 3;
                int y1 = (j + 1) % 3, y2 = (j + 2) % 3;
                
                Type subDet = data[x1][y1] * data[x2][y2]
                              - data[x1][y2] * data[x2][y1];
                
                // Multiply by pow(-1, i+j)
                inv[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * subDet;
            }
        }
        
        return inv / det;
    }
    
    Type minor(size_t i, size_t j) const {
        Matrix<Type, 3, 3> subMatrix;
        
        for (size_t row = 0, curRow = 0; row < 4; ++row) {
            if (row == i)
                continue;
            for (size_t col = 0, curCol = 0; col < 4; ++col) {
                if (col == j)
                    continue;
                subMatrix[curRow][curCol] = data[row][col];
                ++curCol;
            }
            ++curRow;
        }
        // Assuming you have a 3x3 determinant function
        return subMatrix.determinant();
    }
    
    Matrix<Type, N, M> inverse() requires (N == 4 && M == 4) {
        Type det = determinant();
        if (GLESC::Math::eq(det, Type()))
            throw std::runtime_error("Singular matrix");
        
        Matrix<Type, N, M> inv;
        
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                Type m = minor(i, j);
                inv[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * m;
            }
        }
        
        return inv / det;
    }
private:
    Vec<Type, N> data[M];
}; // class Matrix

using Matrix2 = Matrix<float, 2, 2>;
using Matrix3 = Matrix<float, 3, 3>;
using Matrix4 = Matrix<float, 4, 4>;

using Matrix2D = Matrix<double, 2, 2>;
using Matrix3D = Matrix<double, 3, 3>;
using Matrix4D = Matrix<double, 4, 4>;

using Matrix2I = Matrix<int, 2, 2>;
using Matrix3I = Matrix<int, 3, 3>;
using Matrix4I = Matrix<int, 4, 4>;

using Matrix2U = Matrix<unsigned int, 2, 2>;
using Matrix3U = Matrix<unsigned int, 3, 3>;
using Matrix4U = Matrix<unsigned int, 4, 4>;

using Matrix2L = Matrix<long, 2, 2>;
using Matrix3L = Matrix<long, 3, 3>;
using Matrix4L = Matrix<long, 4, 4>;

using Matrix2F = Matrix<float, 2, 2>;
using Matrix3F = Matrix<float, 3, 3>;
using Matrix4F = Matrix<float, 4, 4>;


namespace GLESC::Math{
    inline Matrix4D perspective(double fovRadians,
                         double aspectRatio,
                         double nearPlane,
                         double farPlane){
        Matrix4D result;
        
        double f = 1.0 / tan(fovRadians / 2.0);
        
        result[0][0] = f / aspectRatio;
        result[1][1] = f;
        result[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
        result[2][3] = (2.0 * farPlane * nearPlane) / (nearPlane - farPlane);
        result[3][2] = -1.0;
        result[3][3] = 0.0;
        
        return result;
    }
}