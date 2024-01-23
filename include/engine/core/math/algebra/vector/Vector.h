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
#include "engine/core/math/algebra/vector/VectorBasicAlgorithms.h"
#include "engine/core/math/algebra/vector/VectorAlgorithms.h"


namespace GLESC::Math {
    
    template<typename Type, size_t N>
    class Vector {
    
    public:
        // =========================================================================================
        // ====================================== Constructors =====================================
        // =========================================================================================
        
        /**
         * @brief Default constructor
         * @details Initializes the vector with 0s
         */
        constexpr Vector() noexcept {
            for (size_t i = 0; i < N; ++i) {
                data[i] = Type();
            }
        }
        
        /**
         * @brief Array constructor
         * @details Initializes the vector with the values from the array
         * @param values
         */
        constexpr explicit Vector(const Type(&list)[N]) noexcept {
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
        constexpr Vector(Args &&... args) noexcept : data{args...} {
        }
        
        
        /**
         * @brief Fill constructor
         * @details Initializes all the values of the vector with the given value
         * @param values
         */
        constexpr explicit Vector(Type values) noexcept {
            std::fill(std::begin(data), std::end(data), values);
        }
        
        /**
         * @brief Copy constructor
         * @details Copies the data from the other vector to this one
         * @param other The vector to copy from
         */
        constexpr Vector(const Vector<Type, N> &other) noexcept {
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
        }
        
        /**
         * @brief Move constructor
         * @details Moves the data from the other vector to this one
         * @param other The vector to move from
         */
        constexpr Vector(Vector<Type, N> &&other) noexcept {
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
         * @brief Sets the data of the vector given an index
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
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(1);
            return data[0];
        }
        
        /**
         * @brief Sets the x (first) value of the vector
         * @details This works as a setter but for the x (first) value of the vector.
         * @param value The value to set
         */
        void x(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(1);
            data[0] = value;
        }
        
        /**
         * @brief Returns the x (first) value of the vector
         * @details This is a getter for the x (first) value of the vector.
         * @return The x (first) value of the vector
         */
        [[nodiscard]] const Type &getX() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(1);
            return data[0];
        }
        
        /**
         * @brief Sets the x (first) value of the vector
         * @details This works as a setter but for the x (first) value of the vector.
         * @param value The value to set
         */
        void setX(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(1);
            data[0] = value;
        }
        
        /**
         * @brief Returns the y (second) value of the vector.
         * @details This is the same as operator[] but only for the y (second) value.
         * The returned value is a reference so it can be modified.
         * @return The y (second) value of the vector
         */
        [[nodiscard]] Type &y() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(2);
            return data[1];
        }
        
        /**
         * @brief Sets the y (second) value of the vector.
         * @details This works as a setter but for the y (second) value of the vector.
         * @param value The value to set
         */
        void y(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(2);
            data[1] = value;
        }
        
        /**
         * @brief Returns the y (second) value of the vector.
         * @details This is a getter for the y (second) value of the vector.
         * @return The y (second) value of the vector
         */
        [[nodiscard]] Type getY() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(2);
            return data[1];
        }
        
        /**
         * @brief Sets the y (second) value of the vector.
         * @details This works as a setter for the y (second) value of the vector.
         * @param value The value to set
         */
        void setY(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(2);
            data[1] = value;
        }
        
        /**
         * @brief Returns the z (third) value of the vector.
         * @details This is the same as operator[] but only for the z (third) value.
         * The returned value is a reference so it can be modified.
         * @return The z (third) value of the vector
         */
        [[nodiscard]] Type &z() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(3);
            return data[2];
        }
        
        /**
         * @brief Sets the z (third) value of the vector
         * @details This works as a setter but for the z (third) value of the vector.
         * @param value The value to set
         */
        void z(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(3);
            data[2] = value;
        }
        
        /**
         * @brief Returns the z (third) value of the vector
         * @details This is a getter for the z (third) value of the vector.
         * @return The z (third) value of the vector
         */
        [[nodiscard]] Type getZ() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(3);
            return data[2];
        }
        
        /**
         * @brief Sets the z (third) value of the vector
         * @details This works as a setter for the z (third) value of the vector.
         * @param value The value to set
         */
        void setZ(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(3);
            data[2] = value;
        }
        
        /**
         * @brief Returns the w (fourth) value of the vector.
         * @details This is the same as operator[] but only for the w (fourth) value.
         * The returned value is a reference so it can be modified.
         * @return The w (fourth) value of the vector
         */
        [[nodiscard]] Type &w() {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(4);
            return data[3];
        }
        
        /**
         * @brief Sets the w (fourth) value of the vector
         * @details This works as a setter but for the w (fourth) value of the vector.
         * @param value The value to set
         */
        void w(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(4);
            data[3] = value;
        }
        
        /**
         * @brief Returns the w (fourth) value of the vector
         * @details This is a getter for the w (fourth) value of the vector.
         * @return The w (fourth) value of the vector
         */
        [[nodiscard]] Type getW() const {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(4);
            return data[3];
        }
        
        /**
         * @brief Sets the w (fourth) value of the vector
         * @details This works as a setter for the w (fourth) value of the vector.
         * @param value The value to set
         */
        void setW(Type value) {
            S_ASSERT_VEC_IS_OF_SIZE_OR_BIGGER(4);
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
        constexpr Vector<Type, N> &operator=(const Vector<Type, N> &other) noexcept {
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
        constexpr Vector<Type, N> &operator=(Vector<Type, N> &&other) noexcept {
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
        constexpr Vector<Type, N> &operator=(const Type(&list)[N]) noexcept {
            std::copy(std::begin(list), std::end(list), std::begin(data));
            return *this;
        }
        
        /**
         * @brief In-place addition with another vector
         * @details Adds the elements of the given vector to this vector element-wise.
         * @param rhs The vector to add
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator+=(const Vector<Type, N> &rhs) {
            VectorBasicAlgorithms::vectorAdd(this->data, rhs.data, this->data);
            return *this;
        }
        
        /**
         * @brief In-place addition with a scalar
         * @details Adds the scalar value to each element of this vector.
         * @param scalar The scalar value to add
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator+=(Type scalar) {
            VectorBasicAlgorithms::vectorScalarAdd(this->data, scalar, this->data);
            return *this;
        }
        
        /**
         * @brief In-place subtraction with another vector
         * @details Subtracts the elements of the given vector from this vector element-wise.
         * @param rhs The vector to subtract
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator-=(const Vector<Type, N> &rhs) {
            VectorBasicAlgorithms::vectorSub(this->data, rhs, this->data);
            return *this;
        }
        
        /**
         * @brief In-place subtraction with a scalar
         * @details Subtracts the scalar value from each element of this vector.
         * @param scalar The scalar value to subtract
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator-=(const Type scalar) {
            for (size_t i = 0; i < N; ++i) {
                data[i] -= scalar;
            }
            VectorBasicAlgorithms::vectorScalarSub(this->data, scalar, this->data);
            return *this;
        }
        
        /**
         * @brief In-place multiplication with a scalar
         * @details Multiplies each element of this vector by the scalar value.
         * @param scalar The scalar value to multiply with
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator*=(const Type scalar) {
            VectorBasicAlgorithms::vectorScalarMul(this->data, scalar, this->data);
            return *this;
        }
        
        /**
         * @brief In-place multiplication with another vector
         * @details Multiplies the elements of this vector with the elements of the given vector
         * element-wise.
         * @param rhs The vector to multiply with
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator*=(const Vector<Type, N> &rhs) {
            VectorBasicAlgorithms::vectorMul(this->data, rhs, this->data);
            return *this;
        }
        
        /**
         * @brief In-place division with a scalar
         * @details Divides each element of this vector by the scalar value.
         * @param scalar The scalar value to divide by
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator/=(const Type scalar) {
            VectorBasicAlgorithms::vectorScalarDiv(this->data, scalar, this->data);
            return *this;
        }
        
        /**
         * @brief In-place division with another vector
         * @details Divides the elements of this vector by the elements of the given vector
         * element-wise.
         * @param rhs The vector to divide by
         * @return A reference to this vector after the operation
         */
        constexpr Vector<Type, N> operator/=(const Vector<Type, N> &rhs) {
            VectorBasicAlgorithms::vectorDiv(this->data, rhs.data, this->data);
            return *this;
        }
        
        
        // ================================== Arithmetic Operators =================================
        
        /**
         * @brief Overloads the '+' operator for scalar addition
         * @details Adds a scalar to each component of the vector
         * @param scalar The scalar value to add
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator+(const Type &scalar) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorScalarAdd(this->data, scalar, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the '+' operator for vector addition
         * @details Adds the corresponding data of two vectors
         * @param rhs The right-hand-side vector to add
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator+(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorAdd(this->data, rhs.data, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the unary '-' operator for negation
         * @details Negates each component of the vector
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator-() const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorNegate(this->data, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the '-' operator for scalar subtraction
         * @details Subtracts a scalar from each component of the vector
         * @param scalar The scalar value to subtract
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator-(const Type &scalar) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorScalarSub(this->data, scalar, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the '-' operator for vector subtraction
         * @details Subtracts the corresponding data of two vectors
         * @param rhs The right-hand-side vector to subtract
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator-(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorSub(this->data, rhs.data, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the '/' operator for scalar division
         * @details Divides each component of the vector by a scalar
         * @param scalar The scalar value to divide by
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator/(Type scalar) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorScalarDiv(this->data, scalar, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the '/' operator for vector division
         * @details Divides the corresponding data of two vectors
         * @param rhs The right-hand-side vector to divide by
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator/(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorDiv(this->data, rhs.data, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the '*' operator for scalar multiplication
         * @details Multiplies each component of the vector by a scalar
         * @param scalar The scalar value to multiply by
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator*(Type scalar) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorScalarMul(this->data, scalar, result.data);
            return result;
        }
        
        /**
         * @brief Overloads the '*' operator for vector multiplication
         * @details Multiplies the corresponding data of two vectors
         * @param rhs The right-hand-side vector to multiply by
         * @return A new vector containing the result
         */
        constexpr Vector<Type, N> operator*(const Vector<Type, N> &rhs) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::vectorMul(this->data, rhs.data, result.data);
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
        constexpr bool operator==(const Vector<OtherType, N> &rhs) const {
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
        constexpr bool operator!=(const Vector<Type, N> &rhs) const {
            return !(*this == rhs);
        }
        
        /**
         * @brief Less than operator for vectors
         * @details Compares elements in sequence; returns as soon as a determining element is found
         * @param rhs Vector to compare against
         * @return True if this vector is less than rhs, false otherwise
         */
        constexpr bool operator<(const Vector<Type, N> &rhs) const {
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
        constexpr bool operator>(const Vector<Type, N> &rhs) const {
            return !(*this <= rhs);
        }
        
        /**
         * @brief Less than or equal to operator for vectors
         * @details Derived from the greater-than operator
         * @param rhs Vector to compare against
         * @return True if this vector is less than or equal to rhs, false otherwise
         */
        constexpr bool operator<=(const Vector<Type, N> &rhs) const {
            return *this < rhs || *this == rhs;
        }
        
        /**
         * @brief Greater than or equal to operator for vectors
         * @details Derived from the less-than operator
         * @param rhs Vector to compare against
         * @return True if this vector is greater than or equal to rhs, false otherwise
         */
        constexpr bool operator>=(const Vector<Type, N> &rhs) const {
            return !(*this < rhs);
        }
        
        
        // =========================================================================================
        // ==================================== Vector Methods =====================================
        // =========================================================================================
        
        void swap(Vector<Type, N> &other) {
            std::swap(data, other.data);
        }
        
        [[nodiscard]] Type dot(const Vector<Type, N> &rhs) const {
            return VectorBasicAlgorithms::dotProduct(this->data, rhs.data);
        }
        
        [[nodiscard]] Type length() const {
            return VectorBasicAlgorithms::length(this->data);
        }
        
        [[nodiscard]]Type lengthSquared() const {
            return VectorBasicAlgorithms::lengthSquared(this->data);
        }
        
        [[nodiscard]] Type isHomogeneous() const {
            return data[N - 1] == Type(1);
        }
        
        
        [[nodiscard]] Vector<Type, N + 1> homogenize() const {
            Vector<Type, N + 1> result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = data[i];
            }
            result[N] = Type(1);
            return result;
        }
        
        [[nodiscard]] Vector<Type, N> project(const Vector<Type, N> &other) const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::project(this->data, other.data, result.data);
            return result;
        }
        
        [[nodiscard]] Vector<Type, N - 1> dehomogenize() const {
            if (data[N - 1] == Type(0))
                throw MathException("Cannot dehomogenize a vector with a zero w-component.");
            
            Vector<Type, N - 1> result;
            Type wInv = Type(1) / data[N - 1];
            
            for (size_t i = 0; i < N - 1; ++i) {
                result[i] = data[i] * wInv;
            }
            
            return result;
        }
        
        
        [[nodiscard]] Vector<Type, N> normalize() const {
            Vector<Type, N> result;
            VectorBasicAlgorithms::normalize(this->data, result.data);
            return result;
        }
        
        [[nodiscard]] int size() const {
            return N;
        }
        
        /**
         * @brief Checks if the vector is parallel to another vector
         * @details This method only makes sense when the vector acts as a direction vector.
         * @param other The vector to check against
         * @return True if the vectors are parallel, false otherwise
         */
        bool isParallel(const Vector<Type, N> &other) const {
            Vector<Type, N> crossProd = this->cross(other);
            return GLESC::Math::eq(crossProd.length(), 0);
        }
        
        /**
         * @brief Checks if the vector is orthogonal to another vector
         * @details This method only makes sense when the vector acts as a direction vector.
         * @param other The vector to check against
         * @return True if the vectors are orthogonal, false otherwise
         */
        bool isOrthogonal(const Vector<Type, N> &other) const {
            return GLESC::Math::eq(this->dot(other), 0);
        }
        
        /**
         * @brief Get an orthogonal (or perpendicular) vector.
         * @return A new vector that is orthogonal to this one. If the vector has more than 2
         * dimensions, the axis of orthogonality is chosen arbitrarily.
         */
        Vector<Type, N> getOrthogonal() const {
            static_assert(N == 2 || N == 3 || N == 4, "getOrthogonal is only implemented for 2D, 3D, and 4D vectors");
            
            if constexpr (N == 2) {
                // In 2D, the orthogonal vector can be obtained by swapping the data
                // and negating one of them.
                return Vector<Type, 2>(-data[1], data[0]);
            } else if constexpr (N == 3) {
                // In 3D, we use the cross product to find an orthogonal vector.
                // First, we need a non-parallel vector to cross with.
                // We choose either (0, 1, 0) or (1, 0, 0) depending on which one is less parallel
                // to the original vector, to avoid degenerate cross products.
                Vector<Type, 3> nonParallel =
                        (GLESC::Math::abs(data[0]) > GLESC::Math::abs(data[1])) ? Vector<Type, 3>(0, 1, 0) : Vector<
                                Type, 3>(1, 0, 0);
                
                // The cross product of this vector with 'nonParallel' yields an orthogonal vector.
                return this->cross(nonParallel);
            } else if constexpr (N == 4) {
                // Finding an orthogonal vector in 4D involves more choices due to extra degrees of
                // freedom. Here, we zero out two data and solve the other two to maintain
                // orthogonality. The choice of which data to zero out depends on the
                // non-zero data of the original vector.
                if (data[0] != 0 || data[1] != 0) {
                    // If the first or second component is non-zero, we set the last two data
                    // to zero and negate one of the first two data to create orthogonality.
                    return Vector<Type, 4>(-data[1], data[0], 0, 0);
                } else {
                    // If the first two data are zero, we work with the last two data.
                    // We negate one and copy the other to create orthogonality.
                    return Vector<Type, 4>(0, -data[3], data[2], 0);
                }
            }
        }
        
        
        /**
         * @brief Checks if the current vector is a scalar multiple of another vector.
         *
         * @param other The vector to compare against.
         * @return true If the current vector is a scalar multiple of the other vector.
         * @return false Otherwise.
         */
        bool isMultipleOf(const Vector<Type, N> &other) const {
            Type ratio;
            bool ratioInitialized = false;
            
            for (size_t i = 0; i < N; ++i) {
                if (!eq(GLESC::Math::abs(other.data[i]), 0)) {
                    if (!ratioInitialized) {
                        ratio = data[i] / other.data[i];
                        ratioInitialized = true;
                    } else if (GLESC::Math::abs(data[i] / other.data[i] - ratio) > epsilon<Type>()) {
                        return false;
                    }
                } else if (!eq(GLESC::Math::abs(data[i]), 0)) {
                    return false;
                }
            }
            return true;
        }
        
        
        bool isCollinear(const std::vector<Vector> &points) const {
            // Create a vector of pointers to the data of each point
            std::vector<const VectorData<Type, N> *> pointData;
            
            for (const auto &point : points) {
                // Cast away const-ness with const_cast. Be very careful with this!
                pointData.push_back(&point.data);
            }
            
            // Call the areCollinear function with the reference point's data and the vector of data pointers
            return VectorAlgorithms::areCollinear(this->data, pointData);
        }
        
        
        /**
         * @brief Calculates the cross product of two vectors
         * @details The cross product is a vector that is perpendicular to the
         * plane formed by the two vectors.
         * Only works for 3 dimensional vectors.
         * @param other
         * @return
         */
        [[nodiscard]] Vector<Type, 3> cross(const Vector<Type, 3> &other) const {
            Vector<Type, 3> result;
            VectorBasicAlgorithms::crossProduct(this->data, other.data, result.data);
            return result;
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
        
        VectorData<Type, N> data;
    };
    
    
}


template<typename Type, size_t N> using VectorT = GLESC::Math::Vector<Type, N>;

using Vec2 = VectorT<float, 2>;
using Vec3 = VectorT<float, 3>;
using Vec4 = VectorT<float, 4>;

using Vec2B = VectorT<bool, 2>;
using Vec3B = VectorT<bool, 3>;
using Vec4B = VectorT<bool, 4>;

using Vec2UI = VectorT<unsigned int, 2>;
using Vec3Ui = VectorT<unsigned int, 3>;
using Vec4Ui = VectorT<unsigned int, 4>;

using Vec2I = VectorT<int, 2>;
using Vec3I = VectorT<int, 3>;
using Vec4I = VectorT<int, 4>;

using Vec2Ul = VectorT<unsigned long, 2>;
using Vec3Ul = VectorT<unsigned long, 3>;
using Vec4Ul = VectorT<unsigned long, 4>;

using Vec2L = VectorT<long, 2>;
using Vec3L = VectorT<long, 3>;
using Vec4L = VectorT<long, 4>;

using Vec2F = VectorT<float, 2>;
using Vec3F = VectorT<float, 3>;
using Vec4F = VectorT<float, 4>;

using Vec2D = VectorT<double, 2>;
using Vec3D = VectorT<double, 3>;
using Vec4D = VectorT<double, 4>;


namespace std {
    template<typename T, size_t U>
    struct hash<VectorT < T, U>> {
    std::size_t operator()(const VectorT <T, U> &vec) const {
        std::hash<T> hasher;
        std::size_t seed = 0;
        for (size_t i = 0; i < U; ++i) {
            seed ^= hasher(vec[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
}
