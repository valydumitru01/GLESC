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
            data[i] = Vec<Type, M>();
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
    Matrix(const std::initializer_list<std::initializer_list<Type>> &list) {
        do {
            if (list.size() != N) {
                std::ostringstream oss;
                oss << "Assertion failed: " << "list.size()" << "\n" << "Message: "
                    << "List size is incorrect, expected size" "N" << "\n" << "File: " << "_file_name_"
                    << "\n" << "Line: " << 67 << "\n" << "Function: " << "_function_name_" << "\n"
                    << "Stacktrace: \n" << GLESC::generateStackTrace();
                GLESC::Logger::get().error(oss.str());
                std::terminate();
            }
        } while (false);
        for (const auto &row : list) {
            do {
                if (row.size() != M) {
                    std::ostringstream oss;
                    oss << "Assertion failed: " << "row.size()" << "\n" << "Message: "
                        << "List size is incorrect, expected size" "M" << "\n" << "File: " << "_file_name_"
                        << "\n" << "Line: " << 67 << "\n" << "Function: " << "_function_name_" << "\n"
                        << "Stacktrace: \n" << GLESC::generateStackTrace();
                    GLESC::Logger::get().error(oss.str());
                    std::terminate();
                }
            } while (false);
        }
        
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
                for (size_t k = 0; k < N; ++k) {
                    data[i][k] *= rhs.data[k][j];
                }
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
        *this = *this * rhs.inverse();
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
    
    [[nodiscard]] Matrix<Type, N, M> operator-(const Matrix<Type, N, M> &rhs) const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] - rhs.data[i][k];
            }
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> operator-() const {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = -data[i][k];
            }
        }
        return result;
    }
    
    [[nodiscard]] Vec<Type, M> operator*(const Vec<Type, M> &rhs) const {
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
    [[nodiscard]] Matrix<Type, N, X> operator*(const Matrix<Type, M, X> &other) const {
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
    
    // ==============Access Operators===================
    [[nodiscard]] Vec<Type, M> &operator[](size_t index) {
        return data[index];
    }
    
    // ==============Comparison Operators===================
    [[nodiscard]] bool operator==(const Matrix<Type, N, M> &rhs) const {
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                if (data[i][k] != rhs.data[i][k]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    [[nodiscard]] bool operator!=(const Matrix<Type, N, M> &rhs) const {
        return !(*this == rhs);
    }
    
    [[nodiscard]] bool operator<(const Matrix<Type, N, M> &rhs) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] >= rhs.data[i]) {
                return false;
            }
        }
        return true;
    }
    
    [[nodiscard]] bool operator>(const Matrix<Type, N, M> &rhs) const {
        for (size_t i = 0; i < N; ++i) {
            if (data[i] <= rhs.data[i]) {
                return false;
            }
        }
        return true;
    }
    
    [[nodiscard]] bool operator<=(const Matrix<Type, N, M> &rhs) const {
        return !(*this > rhs);
    }
    
    [[nodiscard]] bool operator>=(const Matrix<Type, N, M> &rhs) const {
        return !(*this < rhs);
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
    
    [[nodiscard]] Matrix<Type, N, M> translate(const Vec<Type, M - 1> &translation) {
        Matrix<Type, N, M> result(*this);
        for (size_t i = 0; i < N - 1; ++i) {
            result.data[i][M - 1] += translation[i];
        }
        return result;
    }
    
    [[nodiscard]] Matrix<Type, N, M> scale(const Vec<Type, M - 1> &scale) {
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
    
    [[nodiscard]] Matrix<Type, N, M> rotate(const Vec<Type, 3> &degrees) const {
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
            D_ASSERT(false, "Matrix size must be 2x2, 3x3 or 4x4");
        }
    }
    
    [[nodiscard]] Matrix<Type, N, M> inverse() const {
        Type det = determinant();
        if (eq(det, 0))
            throw MathException("Singular matrix");
        Matrix<Type, N, M> inv;
        
        if constexpr (N == 2 && M == 2) {
            
            inv[0][0] = data[1][1] / det;
            inv[0][1] = -data[0][1] / det;
            inv[1][0] = -data[1][0] / det;
            inv[1][1] = data[0][0] / det;
            
        } else if constexpr (N == 3 && M == 3) {
            
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; j++) {
                    // Calculate the sub-determinant
                    int x1 = (i + 1) % 3, x2 = (i + 2) % 3;
                    int y1 = (j + 1) % 3, y2 = (j + 2) % 3;
                    
                    Type subDet = data[x1][y1] * data[x2][y2] - data[x1][y2] * data[x2][y1];
                    
                    // Multiply by pow(-1, i+j)
                    inv[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * subDet;
                }
            }
            
            return inv / det;
        } else if constexpr (N == 4 && M == 4) {
            
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    Type m = minor(i, j);
                    inv[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * m;
                }
            }
            
            
            return inv;
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
        // Assuming you have a 3x3 determinant function
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