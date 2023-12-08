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
#include <engine/core/exceptions/core/math/MathException.h>
#include "engine/core/math/Math.h"
#include "engine/core/math/asserts/VectorAsserts.h"


namespace GLESC::Math {
    
    template<typename Type, size_t N>
    class Vec {
    
    public:
        // =========================================================================================
        // ====================================== Constructors =====================================
        // =========================================================================================
        
        /**
         * @brief Default constructor
         * @details Initializes the vector with 0s
         */
        Vec() noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] = Type();
            }
        }
        
        /**
         * @brief Array constructor
         * @details Initializes the vector with the values from the array
         * @param values
         */
        explicit Vec(const Type(&list)[N]) noexcept {
            std::copy(std::begin(list), std::end(list), std::begin(data));
        }
        
        /**
         * @brief Variadic constructor
         * @details Initializes the vector with the values from the variadic arguments.
         * This means that this constructor can be called with any number of arguments.
         * This constructor is only enabled if the number of arguments is equal to the
         * dimension of the vector.
         * @tparam Args
         * @param args
         */
        template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) == N)>>
        Vec(Args &&... args) noexcept : data{args...} {
        }
        
        
        /**
         * @brief Fill constructor
         * @details Initializes all the values of the vector with the given value
         * @param values
         */
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
        
        
        // =========================================================================================
        // ======================================== Accessors ======================================
        // =========================================================================================
        
        // ================================== General Accessors ====================================
        /**
         * @brief Returns the data of the vector given an index
         * @param index
         * @return
         */
        Type &operator[](size_t index) {
            return data[index];
        }
        
        /**
         * @brief Returns the data of the vector given an index, const version (read only)
         * @param index
         * @return
         */
        const Type &operator[](size_t index) const {
            return data[index];
        }
        
        /**
         * @brief Returns the data of the vector given an index
         * @details This is the same as operator[] but it's more explicit (it's const, read only)
         * @param index
         * @return
         */
        const Type &get(size_t index) const {
            return data[index];
        }
        
        /**
         * @brief Returns the data of the vector given an index
         * @details This is the same as operator[] but it's more explicit.
         * Because it's a normal setter.
         * @param index
         * @param value
         */
        void set(size_t index, Type value) {
            data[index] = value;
        }
        
        // ================================== Special Accessors ====================================
        
        /**
         * @brief Returns the x (reference) value of the vector.
         * @details This is the same as operator[] but only for the x (first) value.
         * The returned value is a reference so it can be modified.
         * @return The x (first) value of the vector
         */
        [[nodiscard]] Type &x() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 1);
            return data[0];
        }
        
        /**
         * @brief Sets the x (first) value of the vector
         * @details This works as a setter but for the x (first) value of the vector.
         * @param value The value to set
         */
        void x(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 1);
            data[0] = value;
        }
        
        /**
         * @brief Returns the x (first) value of the vector
         * @details This is a getter for the x (first) value of the vector.
         * @return The x (first) value of the vector
         */
        [[nodiscard]] const Type &getX() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 1);
            return data[0];
        }
        
        /**
         * @brief Sets the x (first) value of the vector
         * @details This works as a setter but for the x (first) value of the vector.
         * @param value The value to set
         */
        void setX(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 1);
            data[0] = value;
        }
        
        /**
         * @brief Returns the y (second) value of the vector.
         * @details This is the same as operator[] but only for the y (second) value.
         * The returned value is a reference so it can be modified.
         * @return The y (second) value of the vector
         */
        [[nodiscard]] Type &y() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 2);
            return data[1];
        }
        
        /**
         * @brief Sets the y (second) value of the vector.
         * @details This works as a setter but for the y (second) value of the vector.
         * @param value The value to set
         */
        void y(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 2);
            data[1] = value;
        }
        
        /**
         * @brief Returns the y (second) value of the vector.
         * @details This is a getter for the y (second) value of the vector.
         * @return The y (second) value of the vector
         */
        [[nodiscard]] Type getY() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 2);
            return data[1];
        }
        
        /**
         * @brief Sets the y (second) value of the vector.
         * @details This works as a setter for the y (second) value of the vector.
         * @param value The value to set
         */
        void setY(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 2);
            data[1] = value;
        }
        
        /**
         * @brief Returns the z (third) value of the vector.
         * @details This is the same as operator[] but only for the z (third) value.
         * The returned value is a reference so it can be modified.
         * @return The z (third) value of the vector
         */
        [[nodiscard]] Type &z() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            return data[2];
        }
        
        /**
         * @brief Sets the z (third) value of the vector
         * @details This works as a setter but for the z (third) value of the vector.
         * @param value The value to set
         */
        void z(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            data[2] = value;
        }
        
        /**
         * @brief Returns the z (third) value of the vector
         * @details This is a getter for the z (third) value of the vector.
         * @return The z (third) value of the vector
         */
        [[nodiscard]] Type getZ() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            return data[2];
        }
        
        /**
         * @brief Sets the z (third) value of the vector
         * @details This works as a setter for the z (third) value of the vector.
         * @param value The value to set
         */
        void setZ(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 3);
            data[2] = value;
        }
        
        /**
         * @brief Returns the w (fourth) value of the vector.
         * @details This is the same as operator[] but only for the w (fourth) value.
         * The returned value is a reference so it can be modified.
         * @return The w (fourth) value of the vector
         */
        [[nodiscard]] Type &w() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            return data[3];
        }
        
        /**
         * @brief Sets the w (fourth) value of the vector
         * @details This works as a setter but for the w (fourth) value of the vector.
         * @param value The value to set
         */
        void w(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            data[3] = value;
        }
        
        /**
         * @brief Returns the w (fourth) value of the vector
         * @details This is a getter for the w (fourth) value of the vector.
         * @return The w (fourth) value of the vector
         */
        [[nodiscard]] Type getW() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            return data[3];
        }
        
        /**
         * @brief Sets the w (fourth) value of the vector
         * @details This works as a setter for the w (fourth) value of the vector.
         * @param value The value to set
         */
        void setW(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(N, 4);
            data[3] = value;
        }
        
        // =========================================================================================
        // ======================================= Operators =======================================
        // =========================================================================================
        
        // ================================= Assignment Operators ==================================
        
        /**
         * @brief Copy assignment operator
         * @details Copies the data from the other vector to this one
         * @param other
         * @return A reference to this vector
         */
        Vec<Type, N> &operator=(const Vec<Type, N> &other) noexcept {
            if (this == &other)
                return *this;
            
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
            return *this;
        }
        
        /**
         * @brief Move assignment operator
         * @details Moves the data from the other vector to this one
         * @param other The vector to move from
         * @return A reference to this vector
         */
        Vec<Type, N> &operator=(Vec<Type, N> &&other) noexcept {
            if (this == &other)
                return *this;
            
            std::move(std::begin(other.data), std::end(other.data), std::begin(data));
            return *this;
        }
        
        /**
         * @brief Array assignment operator
         * @details Assigns the values from the array to this vector
         * @param values
         * @return A reference to this vector
         */
        Vec<Type, N> &operator=(const Type(&list)[N]) noexcept {
            std::copy(std::begin(list), std::end(list), std::begin(data));
            return *this;
        }
        
        /**
         * @brief In-place addition with another vector
         * @details Adds the elements of the given vector to this vector element-wise.
         * @param rhs The vector to add
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator+=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += rhs.data[i];
            }
            return *this;
        }
        
        /**
         * @brief In-place addition with a scalar
         * @details Adds the scalar value to each element of this vector.
         * @param scalar The scalar value to add
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator+=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] += scalar;
            }
            return *this;
        }
        
        /**
         * @brief In-place subtraction with another vector
         * @details Subtracts the elements of the given vector from this vector element-wise.
         * @param rhs The vector to subtract
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator-=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= rhs.data[i];
            }
            return *this;
        }
        
        /**
         * @brief In-place subtraction with a scalar
         * @details Subtracts the scalar value from each element of this vector.
         * @param scalar The scalar value to subtract
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator-=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= scalar;
            }
            return *this;
        }
        
        /**
         * @brief In-place multiplication with a scalar
         * @details Multiplies each element of this vector by the scalar value.
         * @param scalar The scalar value to multiply with
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator*=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= scalar;
            }
            return *this;
        }
        
        /**
         * @brief In-place multiplication with another vector
         * @details Multiplies the elements of this vector with the elements of the given vector
         * element-wise.
         * @param rhs The vector to multiply with
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator*=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] *= rhs.data[i];
            }
            return *this;
        }
        
        /**
         * @brief In-place division with a scalar
         * @details Divides each element of this vector by the scalar value.
         * @param scalar The scalar value to divide by
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator/=(Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= scalar;
            }
            return *this;
        }
        
        /**
         * @brief In-place division with another vector
         * @details Divides the elements of this vector by the elements of the given vector
         * element-wise.
         * @param rhs The vector to divide by
         * @return A reference to this vector after the operation
         */
        Vec<Type, N> operator/=(const Vec<Type, N> &rhs) {
            for (size_t i = 0; i < N; ++i) {
                data[i] /= rhs.data[i];
            }
            return *this;
        }
        
        
        // ================================== Arithmetic Operators =================================
        
        /**
         * @brief Overloads the '+' operator for scalar addition
         * @details Adds a scalar to each component of the vector
         * @param scalar The scalar value to add
         * @return A new vector containing the result
         */
        Vec<Type, N> operator+(const Type &scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + scalar;
            }
            return result;
        }
        
        /**
         * @brief Overloads the '+' operator for vector addition
         * @details Adds the corresponding components of two vectors
         * @param rhs The right-hand-side vector to add
         * @return A new vector containing the result
         */
        Vec<Type, N> operator+(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] + rhs.data[i];
            }
            return result;
        }
        
        /**
         * @brief Overloads the unary '-' operator for negation
         * @details Negates each component of the vector
         * @return A new vector containing the result
         */
        Vec<Type, N> operator-() const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = -data[i];
            }
            return result;
        }
        
        /**
         * @brief Overloads the '-' operator for scalar subtraction
         * @details Subtracts a scalar from each component of the vector
         * @param scalar The scalar value to subtract
         * @return A new vector containing the result
         */
        Vec<Type, N> operator-(const Type &scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - scalar;
            }
            return result;
        }
        
        /**
         * @brief Overloads the '-' operator for vector subtraction
         * @details Subtracts the corresponding components of two vectors
         * @param rhs The right-hand-side vector to subtract
         * @return A new vector containing the result
         */
        Vec<Type, N> operator-(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] - rhs.data[i];
            }
            return result;
        }
        
        /**
         * @brief Overloads the '/' operator for scalar division
         * @details Divides each component of the vector by a scalar
         * @param scalar The scalar value to divide by
         * @return A new vector containing the result
         */
        Vec<Type, N> operator/(Type scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / scalar;
            }
            return result;
        }
        
        /**
         * @brief Overloads the '/' operator for vector division
         * @details Divides the corresponding components of two vectors
         * @param rhs The right-hand-side vector to divide by
         * @return A new vector containing the result
         */
        Vec<Type, N> operator/(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] / rhs.data[i];
            }
            return result;
        }
        
        /**
         * @brief Overloads the '*' operator for scalar multiplication
         * @details Multiplies each component of the vector by a scalar
         * @param scalar The scalar value to multiply by
         * @return A new vector containing the result
         */
        Vec<Type, N> operator*(Type scalar) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }
        
        /**
         * @brief Overloads the '*' operator for vector multiplication
         * @details Multiplies the corresponding components of two vectors
         * @param rhs The right-hand-side vector to multiply by
         * @return A new vector containing the result
         */
        Vec<Type, N> operator*(const Vec<Type, N> &rhs) const {
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] * rhs.data[i];
            }
            return result;
        }
        
        
        // ==================================== Comparison Operators ================================
        
        /**
         * @brief Equality operator for vectors
         * @details Compares this vector to another, allowing for different underlying types.
         * Handles floating-point comparison via 'eq' function.
         * @param rhs Vector to compare against
         * @return True if the vectors are equal, false otherwise
         */
        template<typename OtherType>
        constexpr bool operator==(const Vec<OtherType, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (!eq(data[i], rhs.data[i]))
                    return false;
            }
            return true;
        }
        
        /**
         * @brief Inequality operator for vectors
         * @details Utilizes the equality operator for the actual comparison
         * @param rhs Vector to compare against
         * @return True if the vectors are not equal, false otherwise
         */
        constexpr bool operator!=(const Vec<Type, N> &rhs) const {
            return !(*this == rhs);
        }
        
        /**
         * @brief Less than operator for vectors
         * @details Compares elements in sequence; returns as soon as a determining element is found
         * @param rhs Vector to compare against
         * @return True if this vector is less than rhs, false otherwise
         */
        bool operator<(const Vec<Type, N> &rhs) const {
            for (size_t i = 0; i < N; ++i) {
                if (data[i] < rhs.data[i])
                    return true;
                if (data[i] > rhs.data[i])
                    return false;
            }
            return false;
        }
        
        /**
         * @brief Greater than operator for vectors
         * @details Derived from the less-than-or-equal operator
         * @param rhs Vector to compare against
         * @return True if this vector is greater than rhs, false otherwise
         */
        constexpr bool operator>(const Vec<Type, N> &rhs) const {
            return !(*this <= rhs);
        }
        
        /**
         * @brief Less than or equal to operator for vectors
         * @details Derived from the greater-than operator
         * @param rhs Vector to compare against
         * @return True if this vector is less than or equal to rhs, false otherwise
         */
        constexpr bool operator<=(const Vec<Type, N> &rhs) const {
            return *this < rhs || *this == rhs;
        }
        
        /**
         * @brief Greater than or equal to operator for vectors
         * @details Derived from the less-than operator
         * @param rhs Vector to compare against
         * @return True if this vector is greater than or equal to rhs, false otherwise
         */
        constexpr bool operator>=(const Vec<Type, N> &rhs) const {
            return !(*this < rhs);
        }
        
        
        // =========================================================================================
        // ==================================== Vector Methods =====================================
        // =========================================================================================
        
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
        
        
        [[nodiscard]] Vec<Type, N + 1> homogenize() const {
            Vec<Type, N + 1> result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = data[i];
            }
            result[N] = Type(1);
            return result;
        }
        
        [[nodiscard]] Vec<Type, N - 1> dehomogenize() const {
            if (data[N - 1] == Type(0))
                throw MathException("Cannot dehomogenize a vector with a zero w-component.");
            
            Vec<Type, N - 1> result;
            Type wInv = Type(1) / data[N - 1];
            
            for (size_t i = 0; i < N - 1; ++i) {
                result[i] = data[i] * wInv;
            }
            
            return result;
        }
        
        
        [[nodiscard]] Vec<Type, N> normalize() const {
            Type length = this->length();
            if (eq(length, Type(1)) || eq(length, Type(0))) { return *this; }
            Vec<Type, N> result;
            for (size_t i = 0; i < N; ++i)
                result.data[i] = data[i] / length;
            
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
    
    protected:
        Type data[N];
    };
    
    
}


template<typename Type, size_t N> using Vector = GLESC::Math::Vec<Type, N>;

using Vec2 = Vector<float, 2>;
using Vec3 = Vector<float, 3>;
using Vec4 = Vector<float, 4>;

using Vec2B = Vector<bool, 2>;
using Vec3B = Vector<bool, 3>;
using Vec4B = Vector<bool, 4>;

using Vec2UI = Vector<unsigned int, 2>;
using Vec3Ui = Vector<unsigned int, 3>;
using Vec4Ui = Vector<unsigned int, 4>;

using Vec2I = Vector<int, 2>;
using Vec3I = Vector<int, 3>;
using Vec4I = Vector<int, 4>;

using Vec2Ul = Vector<unsigned long, 2>;
using Vec3Ul = Vector<unsigned long, 3>;
using Vec4Ul = Vector<unsigned long, 4>;

using Vec2L = Vector<long, 2>;
using Vec3L = Vector<long, 3>;
using Vec4L = Vector<long, 4>;

using Vec2F = Vector<float, 2>;
using Vec3F = Vector<float, 3>;
using Vec4F = Vector<float, 4>;

using Vec2D = Vector<double, 2>;
using Vec3D = Vector<double, 3>;
using Vec4D = Vector<double, 4>;




namespace std {
    template<typename T, size_t U>
    struct hash<Vector < T, U>> {
    std::size_t operator()(const Vector <T, U> &vec) const {
        std::hash<T> hasher;
        std::size_t seed = 0;
        for (size_t i = 0; i < U; ++i) {
            seed ^= hasher(vec[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
}
