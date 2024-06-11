/******************************************************************************
 * @file   Math.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <type_traits>
#include <random>
#include <cstring>
#include <cmath>
#include "engine/core/asserts/Asserts.h"


namespace GLESC::Math {
    // TODO: Implement min and max and limit functions
    constexpr float FLOAT_COMPARISON_EPSILON = 1e-6f;
    constexpr double DOUBLE_COMPARISON_EPSILON = 1e-10;

    constexpr double PI = 3.14159265358979323846264338327950288419716939937510;

    template <typename Type>
    constexpr Type pi() noexcept {
        if constexpr (std::is_floating_point<Type>::value) {
            return static_cast<Type>(PI);
        }
        else {
            return Type(3);
        }
    }

    template <typename Type>
    constexpr auto epsilon() noexcept {
        using DecayedType = std::remove_const_t<std::remove_reference_t<Type>>;
        if constexpr (std::is_same_v<DecayedType, float>) {
            return FLOAT_COMPARISON_EPSILON;
        }
        else if constexpr (std::is_same_v<DecayedType, double>) {
            return DOUBLE_COMPARISON_EPSILON;
        }
        else if constexpr (std::is_integral_v<DecayedType>) {
            return 0;
        }
        else {
            // Handle other floating point types
            return DecayedType(1e-7);
        }
    }

    template <typename Type>
    constexpr Type epsilon(Type valueParam) {
        auto value = abs(valueParam);

        if (value < 1) return epsilon<Type>();

        return epsilon<Type>() * value;
    }

    template <typename Type, typename TypeFactor>
    constexpr Type lerp(const Type& start, const Type& end, const TypeFactor& factor) {
        return start + (end - start) * factor;
    }

    template <typename Type>
    Type radians(const Type& degrees) noexcept {
        return degrees * Type(PI) / Type(180);
    }

    template <typename Type>
    Type degrees(const Type& radians) noexcept {
        S_ASSERT_TRUE(std::is_floating_point_v<Type>, "Type must be floating point");
        return radians * Type(180) / Type(PI);
    }

    template <typename Type>
    Type mod(const Type& value, const Type& divisor) {
        static_assert(std::is_arithmetic_v<Type>, "Type must be arithmetic");

        if constexpr (std::is_integral_v<Type>) {
            // For integer types, use the modulo operator %
            return value % divisor;
        }
        else {
            // For floating-point types, use std::fmod
            return std::fmod(value, divisor);
        }
    }

    template <typename Type>
    constexpr Type abs(const Type& value) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        if constexpr (std::is_floating_point_v<Type>) {
            return std::fabs(value);
        }
        else if constexpr (std::is_unsigned_v<Type>) {
            return value;
        }
        else if constexpr (std::is_arithmetic_v<Type> && std::is_signed_v<Type>) {
            return std::abs(value);
        }
        else {
            // For user-defined types, you might want to call a member function
            // or free function that computes the absolute value for that type.
            // For demonstration, let's assume T has a member function abs() that
            // computes the absolute value:
            return value.abs();
        }
    }

    /**
     * @brief Clamps a value between a minimum and maximum value
     * @details Clamp is a function that limits a value to a specific range. If the value is less than the minimum,
     * it returns the minimum. If the value is greater than the maximum, it returns the maximum. Otherwise, it returns
     * the value.
     * @tparam Type1 The type of the value to clamp
     * @tparam Type2 The type of the minimum value
     * @tparam Type3 The type of the maximum value
     * @param value The value to clamp
     * @param min The minimum value
     * @param max The maximum value
     * @return The clamped value
     */
    template <typename Type1, typename Type2, typename Type3>
    constexpr Type1 clamp(const Type1& value, const Type2& min, const Type3& max) {
        if (value < min) {
            return min;
        }
        if (value > max) {
            return max;
        }
        return value;
    }


    constexpr double EPSILON_MULTIPLIER_FOR_EQUALITY = 100;

    template <typename T1, typename T2>
    struct SelectSmallerFloatingType {
        using type = std::conditional_t<
            std::is_floating_point_v<T1> && std::is_floating_point_v<T2>,
            std::conditional_t<(sizeof(T1) < sizeof(T2)), T1, T2>,
            std::conditional_t<std::is_floating_point_v<T1>, T1, T2>
        >;
    };


    template <typename LValueT, typename RValueT>
    constexpr bool eq(const LValueT& left, const RValueT& right, const double epsilon) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>,
                      "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Fixed epsilon comparison
            return std::abs(left - right) < epsilon;
        }
        else {
            // Exact comparison for non-floating-point types
            return left == right;
        }
    }
    template <typename LValueT, typename RValueT>
    constexpr bool lt(const LValueT& left, const RValueT& right, const double epsilon) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Use epsilon for floating-point comparison
            return (left < right) && !eq(left, right, epsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left < right;
        }
    }
    template <typename LValueT, typename RValueT>
    constexpr bool lte(const LValueT& left, const RValueT& right, const double epsilon) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Use epsilon for floating-point comparison
            return (left < right) || eq(left, right, epsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left <= right;
        }
    }

    template <typename LValueT, typename RValueT>
    constexpr bool gt(const LValueT& left, const RValueT& right, const double epsilon) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Use epsilon for floating-point comparison
            return (left > right) && !eq(left, right, epsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left > right;
        }
    }
    template <typename LValueT, typename RValueT>
    constexpr bool mte(const LValueT& left, const RValueT& right, const double epsilon) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Use epsilon for floating-point comparison
            return (left > right) || eq(left, right, epsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left >= right;
        }
    }



    template <typename LValueT, typename RValueT>
    constexpr bool eq(const LValueT& left, const RValueT& right) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>,
                      "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Determine the type with the lower precision
            using LowerPrecisionFloatingType = typename SelectSmallerFloatingType<LValueT, RValueT>::type;

            // Define a fixed epsilon value
            constexpr LowerPrecisionFloatingType fixedEpsilon = Math::epsilon<LowerPrecisionFloatingType>(
                EPSILON_MULTIPLIER_FOR_EQUALITY);

            // Fixed epsilon comparison
            return std::abs(left - right) < fixedEpsilon;
        }
        else {
            // Exact comparison for non-floating-point types
            return left == right;
        }
    }

    template <typename LValueT, typename RValueT>
    constexpr bool lt(const LValueT& left, const RValueT& right) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Determine the type with the lower precision
            using LowerPrecisionFloatingType = typename SelectSmallerFloatingType<LValueT, RValueT>::type;

            // Define a fixed epsilon value
            constexpr LowerPrecisionFloatingType fixedEpsilon = Math::epsilon<LowerPrecisionFloatingType>(
                EPSILON_MULTIPLIER_FOR_EQUALITY);

            // Use epsilon for floating-point comparison
            return (left < right) && !eq(left, right, fixedEpsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left < right;
        }
    }


    template <typename LValueT, typename RValueT>
    constexpr bool lte(const LValueT& left, const RValueT& right) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Determine the type with the lower precision
            using LowerPrecisionFloatingType = typename SelectSmallerFloatingType<LValueT, RValueT>::type;

            // Define a fixed epsilon value
            constexpr LowerPrecisionFloatingType fixedEpsilon = Math::epsilon<LowerPrecisionFloatingType>(
                EPSILON_MULTIPLIER_FOR_EQUALITY);

            // Use epsilon for floating-point comparison
            return (left < right) || eq(left, right, fixedEpsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left <= right;
        }
    }

    template <typename LValueT, typename RValueT>
    constexpr bool gt(const LValueT& left, const RValueT& right) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Determine the type with the lower precision
            using LowerPrecisionFloatingType = typename SelectSmallerFloatingType<LValueT, RValueT>::type;

            // Define a fixed epsilon value
            constexpr LowerPrecisionFloatingType fixedEpsilon = Math::epsilon<LowerPrecisionFloatingType>(
                EPSILON_MULTIPLIER_FOR_EQUALITY);

            // Use epsilon for floating-point comparison
            return (left > right) && !eq(left, right, fixedEpsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left > right;
        }
    }

    template <typename LValueT, typename RValueT>
    constexpr bool mte(const LValueT& left, const RValueT& right) {
        static_assert(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>, "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> || std::is_floating_point_v<RValueT>) {
            // Determine the type with the lower precision
            using LowerPrecisionFloatingType = typename SelectSmallerFloatingType<LValueT, RValueT>::type;

            // Define a fixed epsilon value
            constexpr LowerPrecisionFloatingType fixedEpsilon = Math::epsilon<LowerPrecisionFloatingType>(
                EPSILON_MULTIPLIER_FOR_EQUALITY);

            // Use epsilon for floating-point comparison
            return (left > right) || eq(left, right, fixedEpsilon);
        }
        else {
            // Exact comparison for non-floating-point types
            return left >= right;
        }
    }


    /**
     * @brief Calculates the min of two values
     * @tparam Type1 The type of the first value.
     * @tparam Type2 The type of the second value.
     * @param a The first value.
     * @param b The second value.
     * @return The min of the two values, promoted to the common type of the two input types.
     */
    template <typename Type1, typename Type2>
    constexpr auto min(const Type1 a, const Type2 b) {
        using CommonType = std::common_type_t<Type1, Type2>;
        return a < b ? static_cast<CommonType>(a) : static_cast<CommonType>(b);
    }

    /**
     * @brief Calculates the max of two values
     * @tparam Type1 The type of the first value.
     * @tparam Type2 The type of the second value.
     * @param a The first value.
     * @param b The second value.
     * @return The max of the two values, promoted to the common type of the two input types.
     */
    template <typename Type1, typename Type2>
    constexpr auto max(const Type1 a, const Type2 b) {
        using CommonType = std::common_type_t<Type1, Type2>;
        return a > b ? static_cast<CommonType>(a) : static_cast<CommonType>(b);
    }


    /**
     * @brief Remaps a value from one range to another, including support for reverse mapping.
     * @details Maps the value `x` from the range [min1, max1] to the range [min2, max2].
     *
     * @tparam Type Data type of the value (e.g., float, double).
     * @param x The value to be remapped.
     * @param min1 The lower bound of the input range.
     * @param max1 The upper bound of the input range.
     * @param min2 The lower bound of the output range.
     * @param max2 The upper bound of the output range.
     * @return Remapped value.
     */
    template <typename TypeX, typename TypeMin1, typename TypeMax1, typename TypeMin2, typename TypeMax2>
    static TypeX remap(TypeX x, TypeMin1 min1, TypeMax1 max1, TypeMin2 min2, TypeMax2 max2) {
        // Ensure the input value is clamped within the input range
        x = Math::clamp(x, min1, max1);
        // Calculate the proportion of x within the input range
        TypeX t = (x - min1) / (max1 - min1);
        // Map the proportion to the output range
        return min2 + t * (max2 - min2);
    }

    template <typename Type>
    Type sqrt(const Type& value) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        D_ASSERT_TRUE(value >= Type(0), "Value must be positive");
        Type result = Type();
        if constexpr (std::is_arithmetic_v<Type>) {
            if constexpr (std::is_integral_v<Type>) {
                return static_cast<Type>(std::round(std::sqrt(static_cast<double>(value))));
            }
            else {
                return static_cast<Type>(std::sqrt(value));
            }
        }
        else {
            // For user-defined types, you might want to call a member function
            // or free function that computes the square root for that type.
            // For demonstration, let's assume T has a member function sqrt() that
            // computes the square root:
            result = value.sqrt();
        }
        return result;
    }

    template <typename Type>
    auto cos(const Type& value) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        return std::cos(value);
    }

    template <typename Type>
    auto sin(const Type& value) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        return std::sin(value);
    }

    template <typename Type>
    auto tan(const Type& value) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        return std::tan(value);
    }

    template <typename Type>
    auto atan2(const Type& y, const Type& x) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        return std::atan2(y, x);
    }


    /**
     * @brief Generates a random number between min and max, specifically [min, max)
     * @details The random number is generated using the Mersenne Twister algorithm
     * The min and max values parameters must follow the following rules:
     * - (max - min) < std::numeric_limits<Type>::max()
     * - max >= min
     * @tparam Type The type of the random number
     * @param min The minimum value of the random number
     * @param max The maximum value of the random number
     * @return A random number of the given type in the range [min, max)
     */
    template <typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
    Type generateRandomNumber(Type min, Type max) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        D_ASSERT_TRUE(max >= min, "Max must be greater than min");
        D_ASSERT_TRUE((max + GLESC::Math::abs(min)) < std::numeric_limits<Type>::max(),
                      "(Max - min) must be less than the max value of the type");
        static std::random_device rd;
        static std::mt19937 mt(rd());

        // If the type is uint, we use the fast unsigned int type for the distribution
        if constexpr (std::is_unsigned_v<Type> && std::is_integral_v<Type>) {
            std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
            return dist(mt);
        }
        // If the type is int, we just use the int type for the int distribution
        else if constexpr (std::is_integral_v<Type>) {
            std::uniform_int_distribution<Type> dist(min, max);
            return dist(mt);
        }
        else if constexpr (std::is_floating_point_v<Type>) {
            // For other types (int, etc.), use the type directly
            std::uniform_real_distribution<Type> dist(min, max);
            return dist(mt);
        }
    }

    /**
     * @brief Generates a compile time random number between min and max, specifically [min, max)
     * @details this uses the __TIME__ macro to generate a random number
     * @tparam Type The type of the random number
     * @tparam min The minimum value of the random number
     * @tparam max The maximum value of the random number
     * @return
     */
    template <typename Type, Type min, Type max>
    constexpr Type generateCompileTimeRandomNumber() {
        static_assert(min < max, "max must be greater than min");

        // Extracting compile time in hh:mm:ss format
        constexpr auto time = __TIME__;
        constexpr auto hour = (time[0] - '0') * 10 + (time[1] - '0');
        constexpr auto minute = (time[3] - '0') * 10 + (time[4] - '0');
        constexpr auto second = (time[6] - '0') * 10 + (time[7] - '0');

        // Calculating a pseudo-random seed from the current time
        constexpr unsigned seed = hour * 3600 + minute * 60 + second;

        // Parameters for the Linear Congruential Generator
        constexpr unsigned a = 1664525; // the multiplier
        constexpr unsigned c = 1013904223; // the increment

        // Modulus is the difference between max and min. Cast to Type to ensure same type arithmetic
        constexpr Type modulus = static_cast<Type>(max - min);

        // Generating the random number using the Linear Congruential Generator formula
        // Cast each part of the operation to Type to ensure the arithmetic is done in the correct type
        constexpr Type randomNumber = static_cast<Type>((a * seed + c) % modulus) + min;

        return randomNumber;
    }


    /**
     * @brief Generates a random number with the widest range possible for the type
     * @tparam Type The type of the random number
     * @return A random number of the given type
     */
    template <typename Type>
    Type generateRandomNumber() {
        // For other types, use the standard limits
        // The maximum range for the random number is
        // [std::numeric_limits<Type>::lowest()/2, std::numeric_limits<Type>::max()/2)
        return generateRandomNumber(std::numeric_limits<Type>::lowest() / 4,
                                    std::numeric_limits<Type>::max() / 4);
    }
}
