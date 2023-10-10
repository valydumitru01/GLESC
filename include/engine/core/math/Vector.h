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
        // ================================================
        // ==================Constructors==================
        // ================================================
        Vector() {
            for (size_t i = 0; i < N; ++i) {
                data[i] = Type();
            }
        }
        
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
                data[i] = other[i];
            }
        }
        
        Vector(Vector<Type, N> &&other) noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] = std::move(other[i]);
            }
        }
        
        Vector(std::initializer_list<Type> list) {
            ASSERT(list.size() == N,
                   "Initializer list size must be equal to N");
            for (size_t i = 0; i < N; ++i) {
                data[i] = *(list.begin() + i);
            }
        }
        
        // ================================================
        // ==================Operators=====================
        // ================================================
        
        // ==============Assignment operators==============
        
        Vector<Type, N> &operator=(const Vector<Type, N> &other) {
            if (this == &other)
                return *this;
            
            for (size_t i = 0; i < N; ++i) {
                data[i] = other[i];
            }
            return *this;
        }
        
        Vector<Type, N> operator+=(const Vector<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += rhs.data[i];
            }
            return *this;
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
        
        
        // ==============Arithmetic Operators===================
        Vector<Type, N> operator+(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + rhs.data[i];
            }
            return result;
        }
        
        Vector<Type, N> operator-(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - rhs.data[i];
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
        
        Vector<Type, N> operator*(Type scalar) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }
        
        // ==============Access Operators===================
        Type &operator[](size_t index) {
            return data[index];
        }
        
        const Type &operator[](size_t index) const {
            return data[index];
        }
        
        // ==============Comparison Operators===================
        constexpr bool operator==(const Vector &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] != rhs.data[i])
                    return false;
            }
            return true;
        }
        
        constexpr bool operator!=(const Vector &rhs) const {
            return !(*this == rhs);
        }
        
        constexpr bool operator<(const Vector &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] >= rhs.data[i])
                    return false;
            }
            return true;
        }
        
        constexpr bool operator>(const Vector &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] <= rhs.data[i])
                    return false;
            }
            return true;
        }
        
        constexpr bool operator<=(const Vector &rhs) const {
            return !(*this > rhs);
        }
        
        constexpr bool operator>=(const Vector &rhs) const {
            return !(*this < rhs);
        }
        
        
        // =================Vector Functions=================
        
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
        
        
        [[nodiscard]] std::string toString() const {
            std::string result;
            result += "[";
            for (size_t i = 0; i < N; ++i) {
                result += std::to_string(data[i]);
            }
            result += "]";
            return result;
        }
        
        
        // -----------------------------------------------
        // Specialization for vectors of different dimensions
        // -----------------------------------------------
        
        // Specialization for 1 dimensional vectors
        [[nodiscard]] Type& x() requires (N >= 1) {
            return data[0];
        }
        void x(Type value) requires (N >= 1) {
            data[0] = value;
        }
        [[nodiscard]] Type getX() const requires (N >= 1) {
            return data[0];
        }
        
        // Specialization for 2 dimensional vectors
        [[nodiscard]] Type& y() requires (N >= 2) {
            return data[1];
        }
        void y(Type value) requires (N >= 2) {
            data[1] = value;
        }
        [[nodiscard]] Type getY() const requires (N >= 2) {
            return data[1];
        }
        
        
        // Specialization for 3 dimensional vectors
        [[nodiscard]] Type& z() requires (N >= 3) {
            return data[2];
        }
        void z(Type value) requires (N >= 3) {
            data[2] = value;
        }
        [[nodiscard]] Type getZ() const requires (N >= 3) {
            return data[2];
        }
        
        /**
         * @brief Calculates the cross product of two vectors
         * @details The cross product is a vector that is perpendicular to the
         * plane formed by the two vectors.
         * Only works for 3 dimensional vectors.
         * @param other
         * @return
         */
        Vector<Type, 3> cross(Vector<Type, 3> &other) const requires (N == 3) {
            return Vector<Type, 3>(
                    data[1] * other[2] - data[2] * other[1],
                    data[2] * other[0] - data[0] * other[2],
                    data[0] * other[1] - data[1] * other[0]);
        }
        
        
        // Specialization for 4 dimensional vectors
        [[nodiscard]] Type& w() requires (N >= 4) {
            return data[3];
        }
        void w(Type value) requires (N >= 4) {
            data[3] = value;
        }
        
        // ###############################################
        // Specialization for vectors of different types
        // ###############################################
        
        // ############All Arithmetic Types###############
        
        // ==============Assignment operators==============
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
                 && (!std::is_same_v<Type, OtherType>)
        Vector<Type, N> &operator=(const Vector<OtherType, N> &other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(other[i]);
            }
            return *this;
        }
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
                 && (!std::is_same_v<Type, OtherType>)
        Vector<Type, N> operator+=(const Vector<OtherType, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += static_cast<Type>(rhs[i]);
            }
            return *this;
        }
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
                 && (!std::is_same_v<Type, OtherType>)
        Vector<Type, N> operator-=(const Vector<OtherType, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= static_cast<Type>(rhs[i]);
            }
            return *this;
        }
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
                 && (!std::is_same_v<Type, OtherType>)
        Vector<Type, N> operator*=(OtherType scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= static_cast<Type>(scalar);
            }
            return *this;
        }
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
                 && (!std::is_same_v<Type, OtherType>)
        Vector<Type, N> operator/=(OtherType scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= static_cast<Type>(scalar);
            }
            return *this;
        }
        
        // ==============Arithmetic Operators===================
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
        Vector<Type, N> operator+(const Vector<OtherType, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + static_cast<Type>(rhs.data[i]);
            }
            return result;
        }
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
        Vector<Type, N> operator-(const Vector<OtherType, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - static_cast<Type>(rhs.data[i]);
            }
            return result;
        }
        
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
        bool operator==(const Vector<OtherType, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] != static_cast<Type>(rhs.data[i])) {
                    return false;
                }
            }
        }
        
        template<typename OtherType>
        requires std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type>
        bool operator!=(const Vector<OtherType, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] == static_cast<Type>(rhs.data[i])) {
                    return false;
                }
            }
            return true;
        }
        
        
        // ############All Floating Point Types###############
        
        bool operator==(const Vector<Type,
                N> &other) const requires(std::is_floating_point_v<Type>) {
            for (size_t i = 0; i < N; ++i) {
                if (!GLESC::Math::eq(data[i], other[i])) {
                    return false;
                }
            }
            return true;
        }
    
    
    private:
        Type data[N];
    };
    
    
}


template<typename Type, size_t N>
using Vec = GLESC::Math::Vector<Type, N>;

template<typename Type>
using Vec2 = Vec<Type, 2>;
template<typename Type>
using Vec3 = Vec<Type, 3>;
template<typename Type>
using Vec4 = Vec<Type, 4>;


using Vec2F = Vec<float, 2>;
using Vec2D = Vec<double, 2>;
using Vec2I = Vec<int, 2>;
using Vec2U = Vec<unsigned int, 2>;
using Vec2L = Vec<long, 2>;

using Vec3F = Vec<float, 3>;
using Vec3D = Vec<double, 3>;
using Vec3I = Vec<int, 3>;
using Vec3U = Vec<unsigned int, 3>;
using Vec3L = Vec<long, 3>;

using Vec4F = Vec<float, 4>;
using Vec4D = Vec<double, 4>;
using Vec4I = Vec<int, 4>;
using Vec4U = Vec<unsigned int, 4>;
using Vec4L = Vec<long, 4>;


namespace std {
    template<typename T, size_t U>
    struct hash<Vec < T, U>> {
    std::size_t operator()(const Vec <T, U> &vec) const {
        std::hash<T> hasher;
        std::size_t seed = 0;
        for (size_t i = 0; i < U; ++i) {
            seed ^= hasher(vec[i]) + 0x9e3779b9 + (seed << 6) +
                    (seed >> 2);
        }
        return seed;
    }
};
}
