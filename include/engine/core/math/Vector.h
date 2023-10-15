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
#include "engine/core/math/asserts/VectorAsserts.h"


namespace GLESC::Math {
    
    template<typename Type, size_t N>
    class Vector {
        template<typename OtherType>
        using EnableIfNarrowerNumber = std::enable_if_t<
                std::is_arithmetic_v<OtherType> &&
                std::is_arithmetic_v<Type> &&
                !std::is_same_v<Type, OtherType> &&
                (sizeof(OtherType) < sizeof(Type))
        >;
        
        template<size_t Size>
        using EnableIfVectorIsSizeOrMore = std::enable_if_t<N == Size, std::void_t<>>;
        
        static_assert(N > 1, "Size must be greater than 1");
    
    public:
        // ================================================
        // ==================Constructors==================
        // ================================================
        Vector() {
            for (size_t i = 0; i < N; ++i) {
                data[i] = Type();
            }
        }
        
        
        template<typename... Args,
                 typename = std::enable_if_t<(sizeof...(Args) == N) &&
                                             (std::conjunction_v<std::is_convertible<Args, Type>...>)>
        >
        explicit Vector(Args&&... args) : data{static_cast<Type>(args)...} {
        }
        
        
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
        
        template<typename Size >
        Vector(std::initializer_list<Type> list) {
            ASSERT_INIT_LIST_IS_OF_SIZE(list, N);
            for (size_t i = 0; i < N; ++i) {
                data[i] = *(list.begin() + i);
            }
        }
        
        // #################Numeric Types###################
        /**
         * @brief
         * @details
 * https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
         * @tparam Args
         * @param args
         */
        template<typename... Args,
                 typename = std::enable_if_t<(sizeof...(Args) == N) &&
                         std::conjunction_v<std::is_same<Type, Args>...>>,
                 typename = EnableIfNarrowerNumber<std::common_type_t<Args...>>>
        explicit Vector(Args&&... args)
        : data{static_cast<Type>(std::forward<Args>(args))...} {
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        explicit Vector(OtherType value) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(value);
            }
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        explicit Vector(const Vector<OtherType, N> &other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(other[i]);
            }
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        explicit Vector(Vector<OtherType, N> &&other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(std::move(other[i]));
            }
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        explicit Vector(std::initializer_list<OtherType> list) {
            ASSERT_INIT_LIST_IS_OF_SIZE(list.size(), N);
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(*(list.begin() + i));
            }
        }
        
        
        // ================================================
        // ===============Getters and Setters==============
        // ================================================
        
        // Specialization for 1 dimensional vectors
        [[nodiscard]] Type &x() {
            return data[0];
        }
        
        void x(Type value) {
            data[0] = value;
        }
        
        [[nodiscard]] Type getX() const {
            return data[0];
        }
        
        // Specialization for 2 dimensional vectors
        [[nodiscard]] Type &y() {
            
            return data[1];
        }
        
        void y(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 2);
            data[1] = value;
        }
        
        [[nodiscard]] Type getY() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 2);
            return data[1];
        }
        
        
        // Specialization for 3 dimensional vectors
        [[nodiscard]] Type &z() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            return data[2];
        }
        
        void z(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            data[2] = value;
        }
        
        [[nodiscard]] Type getZ() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            return data[2];
        }
        
        // Specialization for 4 dimensional vectors
        [[nodiscard]] Type &w() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            return data[3];
        }
        
        void w(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            data[3] = value;
        }
        
        [[nodiscard]] Type getW() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            return data[3];
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
        
        // ############All Numeric Types###############
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        Vector<Type, N> &operator=(const Vector<OtherType, N> &other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(other[i]);
            }
            return *this;
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        Vector<Type, N> operator+=(const Vector<OtherType, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += static_cast<Type>(rhs[i]);
            }
            return *this;
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        Vector<Type, N> operator-=(const Vector<OtherType, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= static_cast<Type>(rhs[i]);
            }
            return *this;
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        Vector<Type, N> operator*=(OtherType scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= static_cast<Type>(scalar);
            }
            return *this;
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        Vector<Type, N> operator/=(OtherType scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= static_cast<Type>(scalar);
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
        
        // ############All Numeric Types###############
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        Vector<Type, N> operator+(const Vector<OtherType, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + static_cast<Type>(rhs.data[i]);
            }
            return result;
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        Vector<Type, N> operator-(const Vector<OtherType, N> &rhs) const {
            Vector<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - static_cast<Type>(rhs.data[i]);
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
        
        // ############All Numeric Types###############
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        bool operator==(const Vector<OtherType, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] != static_cast<Type>(rhs.data[i])) {
                    return false;
                }
            }
        }
        
        template<typename OtherType,
                 typename = EnableIfNarrowerNumber<OtherType>>
        bool operator!=(const Vector<OtherType, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] == static_cast<Type>(rhs.data[i])) {
                    return false;
                }
            }
            return true;
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
        
        
        /**
         * @brief Calculates the cross product of two vectors
         * @details The cross product is a vector that is perpendicular to the
         * plane formed by the two vectors.
         * Only works for 3 dimensional vectors.
         * @param other
         * @return
         */
        [[nodiscard]] Vector<Type, 3> cross(Vector<Type, 3> &other) const {
            S_ASSERT_VEC_IS_OF_SIZE(N, 3);
            return Vector<Type, 3>(
                    data[1] * other[2] - data[2] * other[1],
                    data[2] * other[0] - data[0] * other[2],
                    data[0] * other[1] - data[1] * other[0]);
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
