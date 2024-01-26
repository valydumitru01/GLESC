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

#include <cmath>
#include <type_traits>
#include <random>
#include <cstring>
#include "engine/core/asserts/Asserts.h"


namespace GLESC::Math {
    // TODO: Implement min and max and limit functions
    constexpr float FLOAT_COMPARISON_EPSILON = 1e-6f;
    constexpr double DOUBLE_COMPARISON_EPSILON = 1e-10;
    
    constexpr float PI = 3.1415926;            // 7 digits of precision
    constexpr double PI_DOUBLE = 3.1415926535897932;   // 16 digits of precision
    
    template<typename Type>
    constexpr Type pi() noexcept {
        if constexpr (std::is_same_v<Type, float>)
            return PI;
        else if constexpr (std::is_same_v<Type, double>)
            return PI_DOUBLE;
        else
            static_assert(std::is_floating_point_v<Type>,
                          "PI is only defined for floating point types");
    }
    
    template<typename Type>
    constexpr inline auto epsilon() noexcept {
        using DecayedType = std::remove_const_t<std::remove_reference_t<Type>>;
        if constexpr (std::is_same_v<DecayedType, float>) {
            return FLOAT_COMPARISON_EPSILON;
        } else if constexpr (std::is_same_v<DecayedType, double>) {
            return DOUBLE_COMPARISON_EPSILON;
        } else {
            // Handle other floating point types
            return DecayedType(1e-7);
        }
    }
    
    template<typename Type>
    constexpr inline Type epsilon(Type value) {
        return epsilon<Type>() * flexibleAbs(value);
    }
    
    template<typename Type>
    Type radians(const Type &degrees) noexcept {
        return degrees * PI / Type(180);
    }
    
    template<typename Type>
    Type degrees(const Type &radians) noexcept {
        S_ASSERT_TRUE(std::is_floating_point_v<Type>, "Type must be floating point");
        return radians * Type(180) / PI;
    }
    
    
    template<typename LValueT, typename RValueT>
    constexpr inline bool eq(LValueT a, RValueT b) {
        S_ASSERT_TRUE(std::is_arithmetic_v<LValueT> && std::is_arithmetic_v<RValueT>,
                      "Types must be arithmetic");
        if constexpr (std::is_floating_point_v<LValueT> && std::is_floating_point_v<RValueT>) {
            // Determine the type with the lower precision
            using LowerPrecisionType = std::conditional_t<
                    (sizeof(LValueT) < sizeof(RValueT)), LValueT, RValueT>;
            
            // Use the epsilon of the type with the lower precision
            constexpr auto epsilon = GLESC::Math::epsilon<LowerPrecisionType>();
            return std::fabs(a - b) < epsilon;
        } else {
            return a == b;
        }
    }
    
    template<typename Type>
    constexpr inline Type abs(Type value) {
        S_ASSERT_TRUE(std::is_arithmetic_v<Type>, "Type must be arithmetic");
        if constexpr (std::is_floating_point_v<Type>) {
            return std::fabs(value);
        } else if constexpr (std::is_unsigned_v<Type>) {
            return value;
        } else if constexpr (std::is_arithmetic_v<Type> && std::is_signed_v<Type>) {
            return std::abs(value);
        } else {
            // For user-defined types, you might want to call a member function
            // or free function that computes the absolute value for that type.
            // For demonstration, let's assume T has a member function abs() that
            // computes the absolute value:
            return value.absol();
        }
    }
    
    template<typename T>
    T sqrt(const T &value) {
        S_ASSERT_TRUE(std::is_arithmetic_v<T>, "Type must be arithmetic");
        D_ASSERT_TRUE(value >= T(0), "Value must be positive");
        T result = T();
        if constexpr (std::is_arithmetic_v<T>) {
            if constexpr (std::is_integral_v<T>) {
                return static_cast<T>(std::round(std::sqrt(static_cast<double>(value))));
            } else {
                return static_cast<T>(std::sqrt(value));
            }
        } else {
            // For user-defined types, you might want to call a member function
            // or free function that computes the square root for that type.
            // For demonstration, let's assume T has a member function sqrt() that
            // computes the square root:
            result = value.sqrt();
        }
        return result;
    }
    
    
    template<typename Type>
    constexpr const int getMantissaBytes(){
        S_ASSERT_TRUE(std::is_floating_point_v<Type>, "Type must be floating point");
        return std::numeric_limits<Type>::digits;
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
    template<typename Type>
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
        else if constexpr (std::is_floating_point_v<Type>){
            // For other types (int, etc.), use the type directly
            std::uniform_real_distribution<Type> dist(min, max);
            return dist(mt);
        }
        // If the type is not integral or floating point, we don't know how to generate a random number
        else {
            S_ASSERT_TRUE(false, "Unsupported type for generateRandomNumber");
        }
    }

    /**
     * @brief Generates a random number with the widest range possible for the type
     * @tparam Type The type of the random number
     * @return A random number of the given type
     */
    template<typename Type>
    Type generateRandomNumber() {
        // For other types, use the standard limits
        // The maximum range for the random number is
        // [std::numeric_limits<Type>::lowest()/2, std::numeric_limits<Type>::max()/2)
        return generateRandomNumber(std::numeric_limits<Type>::lowest() / 4,
                                    std::numeric_limits<Type>::max() / 4);
        
    }
    
    
}

