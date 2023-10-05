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
    
    Matrix<Type, N, M>& operator= (const Matrix<Type, N, M> &other) {
        if (this == &other) {
            return *this;
        }
        for (size_t i = 0; i < N; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }
    
    Vector<Type, M>
    operator*(const Vector<Type, M> &rhs) const {
        Vector<Type, M> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = 0;
            for (size_t j = 0; j < M; ++j) {
                result[i] += data[i][j] * rhs[j];
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
    
    Matrix<Type, N, M> operator/(Type scalar) const {
        if (GLESC::Math::decimalEquals(scalar, 0))
            throw MathException("Division by zero");
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                result.data[i][k] = data[i][k] / scalar;
            }
        }
        return result;
    }
    
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
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; ++k) {
                if (data[i][k] == rhs.data[i][k]) {
                    return false;
                }
            }
        }
        return true;
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
        if (GLESC::Math::decimalEquals(scalar, 0))
            throw MathException("Division by zero");
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < N; ++i) {
            for (size_t k = 0; k < M; k++) {
                result.data[i][k] = data[i][k] / scalar;
            }
        }
        std::swap(data, result.data);
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
    
    Matrix<Type, N, M> transpose() {
        Matrix<Type, N, M> result;
        for (size_t i = 0; i < M; ++i) {
            for (size_t k = 0; k < N; ++k) {
                result.data[i][k] = data[k][i];
            }
        }
        return result;
    }
    
    Vector<Type, M> &operator[](size_t index) {
        return data[index];
    }
    
    
    Matrix<Type, N, M> translate(const Vector<Type, M - 1> &translation) {
        Matrix<Type, N, M> result(*this);
        for (size_t i = 0; i < N - 1; ++i) {
            result.data[i][M - 1] += translation[i];
        }
        return result;
    }
    
    Matrix<Type, N, M> scale(const Vector<Type, M - 1> &scale) {
        Matrix<Type, N, M> result(*this);
        for (size_t i = 0; i < N - 1; ++i) {
            result.data[i][i] *= scale[i];
        }
        return result;
    }
    
    Matrix<Type, N, M> rotate(Type degree) requires (M == 2 && N == 2) {
        Matrix<Type, N, M> result(*this);
        Type c = cos(degree), s = sin(degree);
        Matrix<Type, 2, 2> rotation = {{c, -s},
                                       {s, c}};
        return result * rotation;
    }
    
    Matrix<Type, N, M> rotate(Vector<Type, 3> &degrees) requires (M == 3 && N == 3) {
        Matrix<Type, N, M> result(*this);
        Matrix<Type, 3, 3> rotationX =
                {{1, 0,                   0},
                 {0, cos(degrees.getX()), -sin(degrees.getX())},
                 {0, sin(degrees.getX()), cos(degrees.getX())}};
        
        Matrix<Type, 3, 3> rotationY =
                {{cos(degrees.getY()),  0, sin(degrees.getY())},
                 {0,                    1, 0},
                 {-sin(degrees.getY()), 0, cos(degrees.getY())}};
        Matrix<Type, 3, 3> rotationZ =
                {{cos(degrees.getZ()), -sin(degrees.getZ()), 0},
                 {sin(degrees.getZ()), cos(degrees.getZ()),  0},
                 {0,                   0,                    1}};
        result = rotationX * rotationY * rotationZ;
        return result;
    }


private:
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
