/******************************************************************************
 * @file   Asserts.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief Set of macros for runtime and compile time assertions.
 * @details This file contains a set of macros that can be used to check conditions at runtime and compile time.
 * It's separated into two categories: runtime asserts and static asserts. If the NDEBUG macro is defined, the
 * asserts will be empty, otherwise, they will throw an AssertFailedException if the condition is not met.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


// ------------------------ Empty asserts ---------------------------
// Empty asserts are used to substitute asserts in release mode,
// this way the compiler will optimize them out (remove them)

#define D_ASSERT_TRUE(condition, message) do {} while (false)
#define D_ASSERT_FALSE(condition, message) do {} while (false)
#define D_ASSERT_NOT_NULLPTR(condition, message) do {} while (false)
#define D_ASSERT_NULLPTR(condition, message) do {} while (false)
#define D_ASSERT_EQUAL(condition, expected, message) do {} while (false)
#define D_ASSERT_GREATER(condition, expected, message) do {} while (false)
#define D_ASSERT_GREATER_OR_EQUAL(condition, expected, message) do {} while (false)
#define D_ASSERT_LESS(condition, expected, message) do {} while (false)
#define D_ASSERT_LESS_OR_EQUAL(condition, expected, message) do {} while (false)
#define D_ASSERT_NOT_EQUAL(condition, expected, message) do {} while (false)

#define S_ASSERT_TRUE(condition, message)
#define S_ASSERT_FALSE(condition, message) do {} while (false)
#define S_ASSERT_EQUAL(condition, expected, message) do {} while (false)
#define S_ASSERT_GREATER(condition, expected, message) do {} while (false)
#define S_ASSERT_GREATER_OR_EQUAL(condition, expected, message) do {} while (false)
#define S_ASSERT_LESS(condition, expected, message) do {} while (false)
#define S_ASSERT_LESS_OR_EQUAL(condition, expected, message) do {} while (false)
#define S_ASSERT_NOT_EQUAL(condition, expected, message) do {} while (false)




#ifndef NDEBUG
#include <cmath>
#include <limits>
#include <string>
#include <type_traits>
#include <sstream>
#include "engine/core/exceptions/core/AssertFailedException.h"
#include "engine/core/debugger/Stringer.h"
#include "engine/core/logger/Logger.h"

// ------------------------ Runtime asserts ---------------------------
// Runtime asserts are used to check conditions at runtime

/**
 * @brief Converts two values to a string for comparison
 * @details This function is useful to print the values that are being compared in the asserts.
 *
 * @param value The first value
 * @param expected The second value
 * @return std::string The string representation of the values
 */
inline std::string comparingValuesToString(const std::string& value, const std::string& expected) {
    return "Left Value : " + value + " Right Value: " + expected + "\n";
}

/**
 * @brief Compares two values for equality
 * @details This function is used to compare two values for equality. It is only used for the runtime asserts.
 * It already exists a similar implementation of equality comparison in Math.h, but given that we need asserts
 * to be independent to avoid circular dependencies, we have to implement it here.
 *
 * @tparam Type1 The type of the first value
 * @tparam Type2 The type of the second value
 * @param value The first value
 * @param expected The second value
 * @return true If the values are equal
 * @return false If the values are not equal
 */
template <typename Type1, typename Type2>
bool assertEqualsEq(const Type1& value, const Type2& expected) {
    // Floating point comparison
    if constexpr (std::is_floating_point_v<Type1> || std::is_floating_point_v<Type2>) {
        using CommonType = std::common_type_t<Type1, Type2>;
        const CommonType epsilon = std::numeric_limits<CommonType>::epsilon();
        const CommonType diff = std::fabs(static_cast<CommonType>(value) - static_cast<CommonType>(expected));
        return diff <= epsilon * std::max(std::fabs(static_cast<CommonType>(value)),
                                          std::fabs(static_cast<CommonType>(expected)))
            || diff < epsilon;
    }
    // Pointer value comparison
    else if constexpr (std::is_pointer_v<Type1> && std::is_pointer_v<Type2>) {
        return reinterpret_cast<const void*>(value) == reinterpret_cast<const void*>(expected);
    }
    // General comparison
    else {
        return value == expected;
    }
}


#define ASSERT_CONTENT(failureCondition, message) \
        if (!(static_cast<bool>(failureCondition))) { \
            std::ostringstream oss; \
            oss << "\n==================== ASSERTION FAILED ====================\n" \
                << "Failed Condition: " << #failureCondition << "\n" \
                << "Message  : " << (message) << "\n\n" \
                << "Location : " << __FILE__ << ", Line " << __LINE__ << "\n" \
                << "Function : " << __PRETTY_FUNCTION__ << "\n\n"; \
            throw AssertFailedException(oss.str()); \
        }

#define D_ASSERT_TRUE(value, message) \
        do {                              \
            ASSERT_CONTENT(value, message) \
        } while (false)

#define D_ASSERT_FALSE(value, message) \
        do { \
            ASSERT_CONTENT(!(value), message) \
        } while (false)

#define D_ASSERT_NOT_NULLPTR(value, message) \
        do { \
            ASSERT_CONTENT((value) != nullptr, message) \
        } while (false)

#define D_ASSERT_NULLPTR(value, message) \
        do { \
            ASSERT_CONTENT((value) == nullptr, message) \
        } while (false)

#define D_ASSERT_EQUAL(value, expected, message) \
        do { \
        std::string valuesString = comparingValuesToString(GLESC::Stringer::toString(value), \
                   GLESC::Stringer::toString(expected)); \
            ASSERT_CONTENT(assertEqualsEq((value), (expected)), (valuesString + (message))) \
        } while (false)

#define D_ASSERT_GREATER(value, expected, message) \
        do { \
        std::string valuesString = comparingValuesToString(GLESC::Stringer::toString(value), \
                   GLESC::Stringer::toString(expected)); \
            ASSERT_CONTENT((value) > (expected), (valuesString + (message))) \
        } while (false)

#define D_ASSERT_GREATER_OR_EQUAL(value, expected, message) \
        do { \
        std::string valuesString = comparingValuesToString(GLESC::Stringer::toString(value), \
                   GLESC::Stringer::toString(expected)); \
            ASSERT_CONTENT((value) >= (expected), (valuesString + (message))) \
        } while (false)

#define D_ASSERT_LESS(value, expected, message) \
        do { \
        std::string valuesString = comparingValuesToString(GLESC::Stringer::toString(value), \
                   GLESC::Stringer::toString(expected)); \
            ASSERT_CONTENT((value) < (expected), (valuesString + (message))) \
        } while (false)

#define D_ASSERT_LESS_OR_EQUAL(value, expected, message) \
        do { \
        std::string valuesString = comparingValuesToString(GLESC::Stringer::toString(value), \
                   GLESC::Stringer::toString(expected)); \
            ASSERT_CONTENT((value) <= (expected), (valuesString + (message))) \
        } while (false)

#define D_ASSERT_NOT_EQUAL(value, expected, message) \
        do { \
        std::string valuesString = comparingValuesToString(GLESC::Stringer::toString(value), \
                   GLESC::Stringer::toString(expected)); \
            ASSERT_CONTENT(!assertEqualsEq((value), (expected)), (valuesString + (message))) \
        } while (false)


// ------------------------ Static asserts ---------------------------
// Static asserts are used to check conditions at compile time

#define S_ASSERT_TRUE(condition, message) \
        static_assert(condition, message)

#define S_ASSERT_FALSE(condition, message) \
        static_assert(!(condition), message)

#define S_ASSERT_EQUAL(condition, expected, message) \
        static_assert((condition) == (expected), message)

#define S_ASSERT_GREATER(condition, expected, message) \
        static_assert((condition) > (expected), message)

#define S_ASSERT_GREATER_OR_EQUAL(condition, expected, message) \
        static_assert((condition) >= (expected), message)

#define S_ASSERT_LESS(condition, expected, message) \
        static_assert((condition) < expected, message)

#define S_ASSERT_LESS_OR_EQUAL(condition, expected, message) \
        static_assert((condition) <= (expected), message)

#define S_ASSERT_NOT_EQUAL(condition, expected, message) \
        static_assert((condition) != (expected), message)

#endif
