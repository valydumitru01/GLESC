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
    class Vec {
        template<typename OtherType> using EnableIfNarrowerNumber = std::enable_if_t<
                std::is_arithmetic_v<OtherType> && std::is_arithmetic_v<Type> &&
                !std::is_same_v<Type, OtherType> && (sizeof(OtherType) < sizeof(Type))>;
    
    public:
        // ================================================
        // ==================Constructors==================
        // ================================================
        Vec() {
            for (size_t i = 0; i < N; ++i) {
                data[i] = Type();
            }
        }
        //TODO: Add list vector constructor
        
        template<typename... Args, typename = std::enable_if_t<
                (sizeof...(Args) == N) && (std::conjunction_v<std::is_convertible<Args, Type>...>)>>
        /*NOLINT*/Vec(Args &&... args) noexcept : data{static_cast<Type>(args)...} {
        }
        
        
        explicit Vec(Type values) noexcept {
            std::fill(std::begin(data), std::end(data), values);
        }
        
        /**
         * @brief Copy constructor
         * @details Copies the data from the other vector to this one
         * @param other The vector to copy from
         */
        Vec(const Vec<Type, N> &other) noexcept {
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
        }
        
        /**
         * @brief Move constructor
         * @details Moves the data from the other vector to this one
         * @param other The vector to move from
         */
        Vec(Vec<Type, N> &&other) noexcept {
            std::move(std::begin(other.data), std::end(other.data), std::begin(data));
        }
        Vec(std::initializer_list<Type> list) noexcept {
            D_ASSERT_INIT_LIST_IS_OF_SIZE(list.size(), N);
            std::copy(list.begin(), list.end(), std::begin(data));
        }
        
        // #################Numeric Types###################
        /**
         * @brief
         * @details
         * https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
         * @tparam Args
         * @param args
         */
        template<typename... Args, typename =std::enable_if_t<
                (sizeof...(Args) == N) && std::conjunction_v<std::is_same<Type, Args>...>>,
                 typename = EnableIfNarrowerNumber<std::common_type_t<Args...>>>
        explicit Vec(Args &&... args)
                : data{static_cast<Type>(std::forward<Args>(args))...} {
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        explicit Vec(OtherType value) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(value);
            }
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        explicit Vec(const Vec<OtherType, N> &other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(other[i]);
            }
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        explicit Vec(Vec<OtherType, N> &&other) {
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(std::move(other[i]));
            }
        }
        
        // ================================================
        
        
        template<typename OtherType>
        Vec(std::initializer_list<OtherType> list) noexcept {
            D_ASSERT_INIT_LIST_IS_OF_SIZE(list.size(), N);
            for (size_t i = 0; i < N; ++i) {
                data[i] = static_cast<Type>(*(list.begin() + i));
            }
        }
        // ===============Getters and Setters==============
        // ================================================
        
        [[nodiscard]] Type &x() {
            return data[0];
        }
        
        void x(Type value) {
            data[0] = value;
        }
        
        [[nodiscard]] Type getX() const {
            return data[0];
        }
        
        void setX(Type value) {
            data[0] = value;
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
        
        void setY(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 2);
            data[1] = value;
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
        
        void setZ(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            data[2] = value;
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
        
        void setW(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            data[3] = value;
        }
        
        // ================================================
        // ==================Operators=====================
        // ================================================
        
        // ==============Assignment operators==============
        
        Vec<Type, N> &operator=(const Vec<Type, N> &other) noexcept{
            if (this == &other)
                return *this;
            
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
            return *this;
        }
        
        Vec<Type, N> &operator=(Vec<Type, N> &&other) noexcept {
            if (this == &other)
                return *this;
            
            std::move(std::begin(other.data), std::end(other.data), std::begin(data));
            return *this;
        }
        
        Vec<Type, N> operator+=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += rhs.data[i];
            }
            return *this;
        }
        
        Vec<Type, N> operator+=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += scalar;
            }
            return *this;
        }
        
        Vec<Type, N> operator-=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= rhs.data[i];
            }
            return *this;
        }
        
        Vec<Type, N> operator-=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= scalar;
            }
            return *this;
        }
        
        Vec<Type, N> operator*=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= scalar;
            }
            return *this;
        }
        
        Vec<Type, N> operator*=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= rhs.data[i];
            }
            return *this;
        }
        
        Vec<Type, N> operator/=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= scalar;
            }
            return *this;
        }
        
        Vec<Type, N> operator/=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= rhs.data[i];
            }
            return *this;
        }
        
        
        // ==============Arithmetic Operators===================
        
        Vec<Type, N> operator+(const Type &scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + scalar;
            }
            return result;
        }
        
        Vec<Type, N> operator+(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + rhs.data[i];
            }
            return result;
        }
        
        Vec<Type, N> operator-(const Type &scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - scalar;
            }
            return result;
        }
        
        Vec<Type, N> operator-(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - rhs.data[i];
            }
            return result;
        }
        
        
        Vec<Type, N> operator/(Type scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / scalar;
            }
            return result;
        }
        
        Vec<Type, N> operator/(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / rhs.data[i];
            }
            return result;
        }
        
        Vec<Type, N> operator*(Type scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }
        
        Vec<Type, N> operator*(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * rhs.data[i];
            }
            return result;
        }
        
        // ############All Numeric Types###############
        // TODO: Change these with constexpr ifs, its shorter and more readable
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        Vec<Type, N> operator+(const Vec<OtherType, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + static_cast<Type>(rhs.data[i]);
            }
            return result;
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        Vec<Type, N> operator-(const OtherType &scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - static_cast<Type>(scalar);
            }
            return result;
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        Vec<Type, N> operator-(const Vec<OtherType, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - static_cast<Type>(rhs.data[i]);
            }
            return result;
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        Vec<Type, N> operator*(OtherType scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = static_cast<Type>(data[i] * static_cast<Type>(scalar));
            }
            return result;
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        Vec<Type, N> operator/(OtherType scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = static_cast<Type>(data[i] / scalar);
            }
            return result;
        }
        
        template<typename OtherType, typename = EnableIfNarrowerNumber<OtherType>>
        Vec<Type, N> operator/(const Vec<OtherType, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = static_cast<Type>(data[i] / static_cast<Type>(rhs.data[i]));
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
        
        const Type& get(size_t index) const {
            return data[index];
        }
        
        // ==============Comparison Operators===================
        template<typename OtherType>
        constexpr bool operator==(const Vec<OtherType, N> &rhs) const {
            if constexpr (std::is_floating_point_v<OtherType>) {
                for (size_t i = 0; i < N; ++i) {
                    if (!eq(data[i], rhs.data[i]))
                        return false;
                }
                return true;
            } else if (std::is_convertible_v<OtherType, Type>) {
                for (size_t i = 0; i < N; ++i) {
                    if (data[i] != static_cast<Type>(rhs.data[i])) {
                        return false;
                    }
                }
                return true;
                
            } else {
                for (size_t i = 0; i < N; ++i) {
                    if (data[i] != rhs.data[i]) {
                        return false;
                    }
                }
                return true;
            }
        }
        
        constexpr bool operator!=(const Vec<Type, N> &rhs) const {
            if constexpr (std::is_floating_point_v<Type>) {
                for (size_t i = 0; i < N; ++i) {
                    if (eq(data[i], rhs.data[i]))
                        return false;
                }
                return true;
            } else {
                for (size_t i = 0; i < N; ++i) {
                    if (data[i] == rhs.data[i]) {
                        return false;
                    }
                }
                return true;
            }
        }
        
        bool operator<(const Vec<Type, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] < rhs.data[i]) return true;
                if (data[i] > rhs.data[i]) return false;
            }
            return false;
        }
        
        constexpr bool operator>(const Vec<Type, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] > rhs.data[i]) return true;
                if (data[i] < rhs.data[i]) return false;
            }
            return false;
        }
        
        constexpr bool operator<=(const Vec<Type, N> &rhs) const {
            return !(*this > rhs);
        }
        
        constexpr bool operator>=(const Vec<Type, N> &rhs) const {
            return !(*this < rhs);
        }
        
        

        // =================Vector Functions=================
        
        void swap(Vec<Type, N> &other) {
            std::swap(data, other.data);
        }
        
        [[nodiscard]] Type dot(const Vec<Type, N> &rhs) const {
            Type result = Type();
            for (size_t i = 0; i < N; ++i) {
                result += data[i] * rhs.data[i];
            }
            return result;
        }
        
        [[nodiscard]] Type length() const {
            return sqRoot(lengthSquared());
        }
        
        [[nodiscard]]Type lengthSquared() const {
            Type result = Type();
            for (size_t i = 0; i < N; ++i) {
                result += data[i] * data[i];
            }
            return result;
        }
        
        [[nodiscard]] Type isHomogeneous() const {
            return data[N - 1] == Type(1);
        }
        
        [[nodiscard]] Vec<Type, N> normalize() const {
            Type length = this->length();
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / length;
            }
            return result;
        }
        
        [[nodiscard]] int size() const {
            return N;
        }
        
        
        [[nodiscard]] std::string toString() const {
            std::string result;
            result += "[";
            if constexpr (std::is_arithmetic_v<Type>) {
                for (size_t i = 0; i < N; ++i) {
                    result += std::to_string(data[i]) + ", ";
                }
            } else {
                for (size_t i = 0; i < N; ++i) {
                    result += data[i].toString() + ", ";
                }
            }
            result.pop_back();
            result.pop_back();
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
        [[nodiscard]] Vec<Type, 3> cross(Vec<Type, 3> &other) const {
            S_ASSERT_VEC_IS_OF_SIZE(N, 3);
            return Vec<Type, 3>(data[1] * other[2] - data[2] * other[1],
                                   data[2] * other[0] - data[0] * other[2],
                                   data[0] * other[1] - data[1] * other[0]);
        }
    
    private:
        Type data[N];
    };
    
    
}


template<typename Type, size_t N> using Vector = GLESC::Math::Vec<Type, N>;

template<typename Type> using Vec2 = Vector<Type, 2>;
template<typename Type> using Vec3 = Vector<Type, 3>;
template<typename Type> using Vec4 = Vector<Type, 4>;


using Vec2F = Vector<float, 2>;
using Vec2D = Vector<double, 2>;
using Vec2I = Vector<int, 2>;
using Vec2U = Vector<unsigned int, 2>;
using Vec2L = Vector<long, 2>;

using Vec3F = Vector<float, 3>;
using Vec3D = Vector<double, 3>;
using Vec3I = Vector<int, 3>;
using Vec3U = Vector<unsigned int, 3>;
using Vec3L = Vector<long, 3>;

using Vec4F = Vector<float, 4>;
using Vec4D = Vector<double, 4>;
using Vec4I = Vector<int, 4>;
using Vec4U = Vector<unsigned int, 4>;
using Vec4L = Vector<long, 4>;


namespace std {
    template<typename T, size_t U>
    struct hash<Vector < T, U>> {
        std::size_t operator()(const Vector<T, U> &vec) const {
            std::hash<T> hasher;
            std::size_t seed = 0;
            for (size_t i = 0; i < U; ++i) {
                seed ^= hasher(vec[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}
