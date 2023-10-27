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
#include <algorithm>
#include "Vec.h"
#include "engine/core/exceptions/core/math/MathException.h"
#include "engine/core/math/asserts/MatrixAsserts.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/debugger/Stacktrace.h"


template<typename Type, size_t N, size_t M>
class Matrix {
public:
    // ================================================
    // ==================Constructors==================
    // ================================================
    
    Matrix() {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                data[i][k] = Type();
            }
        }
    }
    
    explicit Matrix(Type diagonal) {
        for (size_t i = 0; i < N; ++i) {
            data[i][i] = diagonal;
        }
    }
    
    explicit Matrix(Type (&data)[N][M]) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; j++) {
                this->data[i][j] = data[i][j];
            }
        }
    }
    
    /**
     * @brief Copy constructor
     * @param other
     */
    Matrix(const Matrix<Type, N, M> &other) {
        std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
    }
    
    /**
     * @brief Move constructor
     * @param list
     */
    Matrix(Matrix<Type, N, M> &&other) noexcept {
        std::move(std::begin(other.data), std::end(other.data), std::begin(data));
    }
    
    /**
     * @brief Initializer list constructor
     * @param list
     */
    inline Matrix(const std::initializer_list<std::initializer_list<Type>> &list) {
        ASSERT_MAT_INIT_LIST_IS_OF_SIZE(N, M, list);
        size_t i = 0;
        for (const auto &row : list) {
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
    /**
     * @brief Copy assignment operator
     * @param other
     * @return Matrix<Type, N, M>& - reference to this
     */
    Matrix<Type, N, M> &operator=(const Matrix<Type, N, M> &other) noexcept {
        if (this == &other) {
            return *this;
        }
        std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
        return *this;
    }
    
    /**
     * @brief Move assignment operator
     * @param rhs
     * @return Matrix<Type, N, M>& - reference to this
     */
    Matrix<Type, N, M> &operator=(Matrix<Type, N, M> &&rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        std::move(std::begin(rhs.data), std::end(rhs.data), std::begin(data));
        return *this;
    }
    
    /**
     * @brief Initializer list assignment operator
     * @param rhs
     * @return Matrix<Type, N, M>& - reference to this
     */
    Matrix<Type, N, M> &operator=(const std::initializer_list<std::initializer_list<Type>> &rhs) {
        ASSERT_MAT_INIT_LIST_IS_OF_SIZE(N, M, rhs);
        size_t i = 0;
        for (const auto &row : rhs) {
            size_t j = 0;
            for (const auto &element : row) {
                data[i][j] = element;
                ++j;
            }
            ++i;
        }
        return *this;
    }
    
    
    Matrix<Type, N, M> &operator*=(const Matrix<Type, N, M> &rhs) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                data[i][j] *= rhs.data[i][j];
            }
        }
        return *this;
    }
    
    Matrix<Type, N, M> &operator*=(Type scalar) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                data[i][k] *= scalar;
            }
        }
        
        return *this;
    }
    
    Matrix<Type, N, M> &operator+=(Type rhs) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                data[i][k] += rhs;
            }
        }
        return *this;
    }
    
    Matrix<Type, N, M> &operator+=(const Matrix<Type, N, M> &rhs) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                data[i][k] += rhs.data[i][k];
            }
        }
        return *this;
    }
    
    Matrix<Type, N, M> &operator-=(const Matrix<Type, N, M> &rhs) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                data[i][k] -= rhs.data[i][k];
            }
        }
        return *this;
    }
    
    Matrix<Type, N, M> &operator-=(Type rhs) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                data[i][k] -= rhs;
            }
        }
        return *this;
    }
    
    
    Matrix<Type, N, M> &operator/=(Type scalar) {
        if (eq(scalar, 0))
            throw MathException("Division by zero");
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                data[i][k] /= scalar;
            }
        }
        return *this;
    }
    
    Matrix<Type, N, M> &operator/=(const Matrix<Type, N, M> &rhs) {
        if (eq(rhs.determinant(), 0))
            throw MathException("Division by zero");
        *this *= rhs.inverse();
        return *this;
    }
    
    // ==============Arithmetic Operators===================
    
    [[nodiscard]] Matrix<Type, N, M> operator+(const Matrix<Type, N, M> &rhs) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] + rhs.data[i][k];
            }
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> operator+(Type scalar) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                result.data[i][k] = data[i][k] + scalar;
            }
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> operator-(const Matrix<Type, N, M> &rhs) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] - rhs.data[i][k];
            }
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> operator-(Type scalar) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                result.data[i][k] = data[i][k] - scalar;
            }
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> operator-() const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                result.data[i][k] = -data[i][k];
            }
        }
        return result;
    }
    
    /**
     * @brief Multiplying Matrix by Matrix
     * @details A matrix NxM multiplied by a matrix MxX results in a matrix N x X
     * For example:
     * | 1 2 3 |   | 7  8  |   | 58  64  |
     * | 4 5 6 | * | 9  10 | = | 139 154 |
     *             | 11 12 |
     * 2x3      *  3x2       = 2x2
     * @tparam X
     * @param other
     * @return
     */
    template<size_t X>
    [[nodiscard]] Matrix<Type, N, X> operator*(const Matrix<Type, M, X> &other) const {
        Matrix<Type, N, X> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < X; ++j) {
                for (size_t k = 0; k < M; ++k) {
                    result[i][j] += (*this).get(i,k) * other.get(k,j);
                }
            }
        }
        return result;
    }
    
    
    [[nodiscard]] Matrix<Type, N, M> operator*(Type scalar) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] * scalar;
            }
        }
        return result;
    }
    
    
    [[nodiscard]] Matrix<Type, N, M> operator/(Type scalar) const {
        if (eq(scalar, Type()))
            throw MathException("Division by zero");
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] / scalar;
            }
        }
        return result;
    }
    /**
     * @brief Matrix division by matrix
     * @details The matrix division by matrix is defined as the multiplication of the first matrix
     * by the inverse of the second matrix
     * @param rhs
     * @return
     */
    [[nodiscard]] Matrix<Type, N, M> operator/(const Matrix<Type, N, M> &rhs) const {
        Matrix<Type, N, M> result;
        if (eq(rhs.determinant(), Type()))
            throw MathException("Division by zero");
        result = *this * rhs.inverse();
        return result;
    }
    
    // ==============Access Operators===================
    [[nodiscard]] Vector<Type, M> &operator[](size_t index) {
        return data[index];
    }
    
    [[nodiscard]] const Type &get(size_t i, size_t j) const {
        return data[i].get(j);
    }
    
    [[nodiscard]] size_t rows() const {
        return N;
    }
    
    [[nodiscard]] size_t cols() const {
        return M;
    }
    
    // ==============Comparison Operators===================
    [[nodiscard]] bool operator==(const Matrix<Type, N, M> &rhs) const {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                if (!eq(data[i][k], rhs.data[i][k])) {
                    return false;
                }
            }
        }
        return true;
    }
    
    [[nodiscard]] bool operator!=(const Matrix<Type, N, M> &rhs) const {
        return !(*this == rhs);
    }
    
    
    // =================Matrix Functions=================
    
    [[nodiscard]] Matrix<Type, N, M> transpose() {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < M; ++i) {
            for (size_t k = 0; k < N; ++k) {
                result.data[i][k] = data[k][i];
            }
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> translate(const Vector<Type, M - 1> &translation) {
        Matrix<Type, N, M> result(*this);
        for (size_t i = 0; i < N - 1; ++i) {
            result.data[i][M - 1] += translation[i];
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> scale(const Vector<Type, M - 1> &scale) {
        Matrix<Type, N, M> result(*this);
        for (size_t i = 0; i < N - 1; ++i) {
            result.data[i][i] *= scale[i];
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> rotate(const Type &degree) {
        S_ASSERT_MAT_IS_OF_SIZE(N, M, 3, 3);
        Matrix<Type, N, M> result(*this);
        Type c = cos(degree), s = sin(degree);
        Matrix<Type, 3, 3> rotation = {{c, -s, 0},
                                       {s, c,  0},
                                       {0, 0,  1}};
        return result * rotation;
    }
    
    [[nodiscard]] Matrix<Type, N, M> rotate(const Vector<Type, 3> &degrees) const {
        S_ASSERT_MAT_IS_OF_SIZE(N, M, 4, 4);
        Matrix<Type, 4, 4> result(*this);
        Matrix<Type, 4, 4> rotationX = {{1, 0,                   0,                    0},
                                        {0, cos(degrees.getX()), -sin(degrees.getX()), 0},
                                        {0, sin(degrees.getX()), cos(degrees.getX()),  0},
                                        {0, 0,                   0,                    1}};
        
        Matrix<Type, 4, 4> rotationY = {{cos(degrees.getY()),  0, sin(degrees.getY()), 0},
                                        {0,                    1, 0,                   0},
                                        {-sin(degrees.getY()), 0, cos(degrees.getY()), 0},
                                        {0,                    0, 0,                   1}};
        
        Matrix<Type, 4, 4> rotationZ = {{cos(degrees.getZ()), -sin(degrees.getZ()), 0, 0},
                                        {sin(degrees.getZ()), cos(degrees.getZ()),  0, 0},
                                        {0,                   0,                    1, 0},
                                        {0,                   0,                    0, 1}};
        
        return rotationX * rotationY * rotationZ * result;
    }
    
    
    [[nodiscard]]Type determinant() const {
        S_ASSERT_MAT_IS_SQUARE(N, M);
        if constexpr (N == 2 && M == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        } else if constexpr (N == 3 && M == 3) {
            return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
                   data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
                   data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        } else if constexpr (N == 4 && M == 4) {
            Type det;
            det = data[0][0] * (data[1][1] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
                                data[1][2] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) +
                                data[1][3] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]));
            
            det -= data[0][1] * (data[1][0] * (data[2][2] * data[3][3] - data[2][3] * data[3][2]) -
                                 data[1][2] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
                                 data[1][3] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]));
            
            det += data[0][2] * (data[1][0] * (data[2][1] * data[3][3] - data[2][3] * data[3][1]) -
                                 data[1][1] * (data[2][0] * data[3][3] - data[2][3] * data[3][0]) +
                                 data[1][3] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
            
            det -= data[0][3] * (data[1][0] * (data[2][1] * data[3][2] - data[2][2] * data[3][1]) -
                                 data[1][1] * (data[2][0] * data[3][2] - data[2][2] * data[3][0]) +
                                 data[1][2] * (data[2][0] * data[3][1] - data[2][1] * data[3][0]));
            
            return det;
        } else {
            int n = N;
            Matrix<Type, N, M> localData(*this);
            Type det = Type(1);
            
            for (int i = 0; i < n; ++i) {
                int maxRow = i;
                
                for (int k = i + 1; k < n; ++k) {
                    if (absol(localData[k][i]) > absol(localData[maxRow][i])) {
                        maxRow = k;
                    }
                }
                
                if (localData[maxRow][i] == 0) {
                    return 0;
                }
                
                localData[maxRow].swap(localData[i]);
                det *= localData[i][i];
                
                for (int k = i + 1; k < n; ++k) {
                    Type factor = localData[k][i] / localData[i][i];
                    for (int j = i; j < n; ++j) {
                        localData[k][j] -= factor * localData[i][j];
                    }
                }
            }
            
            return det;
        }
        
    }
    
    Matrix<Type, N, M> adjoint() const {
        Matrix<Type, N, M> adj;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                adj.data[r][c] = (data[(c + 1) % 3][(r + 1) % 3] * data[(c + 2) % 3][(r + 2) % 3]) -
                                 (data[(c + 1) % 3][(r + 2) % 3] * data[(c + 2) % 3][(r + 1) % 3]);
            }
        }
        return adj;
    }
    
    [[nodiscard]] Matrix<Type, N, M> inverse() const {
        Type det = determinant();
        if (eq(det, 0))
            throw MathException("Division by zero");
        if constexpr (N == 2 && M == 2) {
            Matrix<Type, N, M> inv;
            inv.data[0][0] = data[1][1] / det;
            inv.data[0][1] = -data[0][1] / det;
            inv.data[1][0] = -data[1][0] / det;
            inv.data[1][1] = data[0][0] / det;
            return inv;
        } else if constexpr (N == 3 && M == 3) {
            Matrix<Type, N, M> inv = adjoint();
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    inv.data[r][c] /= det;
                }
            }
            return inv;
        } else if constexpr (N == 4 && M == 4) {
            
            Type A2323 = data[2][2] * data[3][3] - data[2][3] * data[3][2];
            Type A1323 = data[2][1] * data[3][3] - data[2][3] * data[3][1];
            Type A1223 = data[2][1] * data[3][2] - data[2][2] * data[3][1];
            Type A0323 = data[2][0] * data[3][3] - data[2][3] * data[3][0];
            Type A0223 = data[2][0] * data[3][2] - data[2][2] * data[3][0];
            Type A0123 = data[2][0] * data[3][1] - data[2][1] * data[3][0];
            Type A2313 = data[1][2] * data[3][3] - data[1][3] * data[3][2];
            Type A1313 = data[1][1] * data[3][3] - data[1][3] * data[3][1];
            Type A1213 = data[1][1] * data[3][2] - data[1][2] * data[3][1];
            Type A2312 = data[1][2] * data[2][3] - data[1][3] * data[2][2];
            Type A1312 = data[1][1] * data[2][3] - data[1][3] * data[2][1];
            Type A1212 = data[1][1] * data[2][2] - data[1][2] * data[2][1];
            Type A0313 = data[1][0] * data[3][3] - data[1][3] * data[3][0];
            Type A0213 = data[1][0] * data[3][2] - data[1][2] * data[3][0];
            Type A0312 = data[1][0] * data[2][3] - data[1][3] * data[2][0];
            Type A0212 = data[1][0] * data[2][2] - data[1][2] * data[2][0];
            Type A0113 = data[1][0] * data[3][1] - data[1][1] * data[3][0];
            Type A0112 = data[1][0] * data[2][1] - data[1][1] * data[2][0];
            
            
            det = data[0][0] * (data[1][1] * A2323 - data[1][2] * A1323 + data[1][3] * A1223) -
                  data[0][1] * (data[1][0] * A2323 - data[1][2] * A0323 + data[1][3] * A0223) +
                  data[0][2] * (data[1][0] * A1323 - data[1][1] * A0323 + data[1][3] * A0123) -
                  data[0][3] * (data[1][0] * A1223 - data[1][1] * A0223 + data[1][2] * A0123);
            det = 1 / det;
            
            Matrix<Type, N, M> im;
            
            im[0][0] = det * (data[1][1] * A2323 - data[1][2] * A1323 + data[1][3] * A1223);
            im[0][1] = det * -(data[0][1] * A2323 - data[0][2] * A1323 + data[0][3] * A1223);
            im[0][2] = det * (data[0][1] * A2313 - data[0][2] * A1313 + data[0][3] * A1213);
            im[0][3] = det * -(data[0][1] * A2312 - data[0][2] * A1312 + data[0][3] * A1212);
            im[1][0] = det * -(data[1][0] * A2323 - data[1][2] * A0323 + data[1][3] * A0223);
            im[1][1] = det * (data[0][0] * A2323 - data[0][2] * A0323 + data[0][3] * A0223);
            im[1][2] = det * -(data[0][0] * A2313 - data[0][2] * A0313 + data[0][3] * A0213);
            im[1][3] = det * (data[0][0] * A2312 - data[0][2] * A0312 + data[0][3] * A0212);
            im[2][0] = det * (data[1][0] * A1323 - data[1][1] * A0323 + data[1][3] * A0123);
            im[2][1] = det * -(data[0][0] * A1323 - data[0][1] * A0323 + data[0][3] * A0123);
            im[2][2] = det * (data[0][0] * A1313 - data[0][1] * A0313 + data[0][3] * A0113);
            im[2][3] = det * -(data[0][0] * A1312 - data[0][1] * A0312 + data[0][3] * A0112);
            im[3][0] = det * -(data[1][0] * A1223 - data[1][1] * A0223 + data[1][2] * A0123);
            im[3][1] = det * (data[0][0] * A1223 - data[0][1] * A0223 + data[0][2] * A0123);
            im[3][2] = det * -(data[0][0] * A1213 - data[0][1] * A0213 + data[0][2] * A0113);
            im[3][3] = det * (data[0][0] * A1212 - data[0][1] * A0212 + data[0][2] * A0112);
            
            return im;
        }
        
    }
    
    [[nodiscard]] Type minor(size_t i, size_t j) const {
        S_ASSERT_MAT_IS_OF_SIZE(N, M, 4, 4);
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
        return subMatrix.determinant();
    }
    
    [[nodiscard]] std::string toString() const {
        std::string result;
        for (size_t i = 0; i < N; ++i) {
            result += "[";
            for (size_t j = 0; j < M; ++j) {
                result += std::to_string(data[i][j]);
                if (j != M - 1) {
                    result += ", ";
                }
            }
            result += "]\n";
        }
        return result;
    }

protected:
    Vector<Type, N> data[M];
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


namespace GLESC::Math {
    inline Matrix4D
    perspective(double fovRadians, double aspectRatio, double nearPlane, double farPlane) {
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