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
#include "engine/core/asserts/Asserts.h"


namespace GLESC::Math {
    constexpr float FLOAT_COMPARISON_EPSILON = 1e-6f;
    constexpr double DOUBLE_COMPARISON_EPSILON = 1e-10;
    /**
     * @brief This epsilon is special for math related operations.
     * @details Is less precise and its used for any type of data. This is necessary
     * because many operations like determinants or matrix inverse are not precise.
     */
    constexpr float ENGINE_EPSILON = 1e-6f;
    constexpr float PI =
            3.1415926535897932384626433832795028841971693993751058209749445923f;
    
    template<typename LValueT, typename RValueT>
    constexpr inline bool flexibleEquals(LValueT a, RValueT b) {
        if constexpr (std::is_floating_point_v<LValueT> &&
                      std::is_floating_point_v<RValueT>) {
            return std::fabs(a - b) < FLOAT_COMPARISON_EPSILON;
        } else {
            return a == b;
        }
    }
    
    template<typename Type>
    constexpr inline Type flexibleAbs(Type value) {
        if constexpr (std::is_floating_point_v<Type>) {
            return std::fabs(value);
        } else if constexpr (std::is_unsigned_v<Type>){
            return value;
        } else if constexpr (std::is_arithmetic_v<Type> && std::is_signed_v<Type>) {
            return std::abs(value);
        } else {
            // For user-defined types, you might want to call a member function
            // or free function that computes the absolute value for that type.
            // For demonstration, let's assume T has a member function abs() that
            // computes the absolute value:
            return value.abs();
        }
    }
    
    template <typename T>
    T flexibleSqrt(const T& value) {
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
}

template<typename LValueT, typename RValueT>
bool eq(LValueT a, RValueT b) {
    return GLESC::Math::flexibleEquals(a, b);
}

template<typename Type>
Type sqRoot(Type value) {
    return GLESC::Math::flexibleSqrt(value);
}

template<typename Type>
Type absol(Type value) {
    return GLESC::Math::flexibleAbs(value);
}