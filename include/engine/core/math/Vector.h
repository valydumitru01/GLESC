/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <type_traits>
#include <cmath>
#include <string>
#include "engine/core/math/Math.h"


namespace GLESC::Math {
    template<typename Type, size_t N>
    class Vector {
        static_assert(N > 0, "Size must be greater than 0");
    
    public:
        // Constructors
        Vector() : data() {}
        
        template<typename... Args>
        explicit Vector(Args &&... args) requires (sizeof ...(Args) == N)
                : data(std::forward<Args>(args) ...) {}
        
        explicit Vector(Type values) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = values;
            }
        }
        
        Vector(const Vector<Type, N> &other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = other.data[i];
            }
        }
        
        Vector(Vector<Type, N> &&other) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] = std::move(other.data[i]);
            }
        }
        
        Vector<Type, N> &operator=(const Vector<Type, N> &other) {
            if (this == &other) return *this;
            
            for (size_t i = 0; i < N; ++i) {
                data[i] = other.data[i];
            }
            return *this;
        }
        
        Vector<Type, N> operator+(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + rhs.data[i];
            }
            return result;
        }
        
        Type& operator[](size_t index) {
            return data[index];
        }
        
        const Type& operator[](size_t index) const{
            return data[index];
        }
        
        Vector<Type, N> operator-(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - rhs.data[i];
            }
            return result;
        }
        
        Vector<Type, N> operator*(Type scalar) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }
        
        Vector<Type, N> operator/(Type scalar) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / scalar;
            }
            return result;
        }
        
        [[nodiscard]] Type dot(const Vector<Type, N> &rhs) const {
            Type result = Type(0);
            for (size_t i = 0; i < N; ++i) {
                result += data[i] * rhs.data[i];
            }
            return result;
        }
        
        [[nodiscard]] Type length() const {
            Type result = Type(0);
            for (size_t i = 0; i < N; ++i) {
                result += data[i] * data[i];
            }
            return std::sqrt(result);
        }
        
        [[nodiscard]] Vector<Type, N> normalize() const {
            Type length = this->length();
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / length;
            }
            return result;
        }
        
        Vector<Type, N> operator+=(const Vector<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += rhs.data[i];
            }
            return *this;
        }
        
        bool operator<(const Vector<Type, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] >= rhs.data[i]) {
                    return false;
                }
            }
            return true;
        }
        
        Vector<Type, N> operator-=(const Vector<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= rhs.data[i];
            }
            return *this;
        }
        
        Vector<Type, N> operator*=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= scalar;
            }
            return *this;
        }
        
        Vector<Type, N> operator/=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= scalar;
            }
            return *this;
        }
        
        bool operator==(const Vector<Type, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] != rhs.data[i]) {
                    return false;
                }
            }
            return true;
        }
        
        bool operator==(const Vector<Type,
                N> &other) const requires(std::is_floating_point_v<Type>) {
            for (size_t i = 0; i < N; ++i) {
                if (!GLESC::Math::decimalEquals(data[i], other.data[i])) {
                    return false;
                }
            }
            return true;
        }
        
        bool operator!=(const Vector<Type, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] == rhs.data[i]) {
                    return false;
                }
            }
            return true;
        }
        
        [[nodiscard]] std::string toString() const {
            std::string result;
            result += "[";
            for (size_t i = 0; i < N; ++i) {
                result += std::to_string(data[i]);
            }
            result += "]";
            return result;
        }
        
        
        Vector<Type, 3> cross(Vector<Type, 3> &other) const requires (N == 3) {
            return Vector<Type, 3>(
                    data[1] * other.data[2] - data[2] * other.data[1],
                    data[2] * other.data[0] - data[0] * other.data[2],
                    data[0] * other.data[1] - data[1] * other.data[0]);
        }
        
        [[nodiscard]] Type getX() const requires (N >= 1) {
            return data[0];
        }
        
        [[nodiscard]] Type getY() const requires (N >= 2) {
            return data[1];
        }
        
        [[nodiscard]] Type getZ() const requires (N >= 3) {
            return data[2];
        }
        
        [[nodiscard]] Type getW() const requires (N >= 4) {
            return data[3];
        }
    
    
    private:
        Type data[N];
    };
    
    
}


template<typename Type, size_t N> using Vector = GLESC::Math::Vector<Type, N>;

using Vector2 = Vector<float, 2>;
using Vector3 = Vector<float, 3>;
using Vector4 = Vector<float, 4>;


using Vector2F = Vector<float, 2>;
using Vector2D = Vector<double, 2>;
using Vector2I = Vector<int, 2>;
using Vector2U = Vector<unsigned int, 2>;
using Vector2L = Vector<long, 2>;

using Vector3F = Vector<float, 3>;
using Vector3D = Vector<double, 3>;
using Vector3I = Vector<int, 3>;
using Vector3U = Vector<unsigned int, 3>;
using Vector3L = Vector<long, 3>;

using Vector4F = Vector<float, 4>;
using Vector4D = Vector<double, 4>;
using Vector4I = Vector<int, 4>;
using Vector4U = Vector<unsigned int, 4>;
using Vector4L = Vector<long, 4>;


namespace std {
    template<typename T, size_t U>
    struct hash<Vector < T, U>> {
    std::size_t operator()(const Vector <T, U> &vec) const {
        std::hash<T> hasher;
        std::size_t seed = 0;
        for (size_t i = 0; i < U; ++i) {
            seed ^= hasher(vec.data[i]) + 0x9e3779b9 + (seed << 6) +
                    (seed >> 2);
        }
        return seed;
    }
};
}
