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

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include <cmath>
#include <type_traits>
#include <limits>
#include "engine/core/debugger/Stacktrace.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/debugger/Stringer.h"

#ifndef NDEBUG
// ------------------------ Runtime asserts ---------------------------
// Runtime asserts are used to check conditions at runtime


#define ASSERT_CONTENT(failureCondition, message) \
        if (!(static_cast<bool>(failureCondition))) { \
            std::ostringstream oss; \
            oss << "\n==================== ASSERTION FAILED ====================\n" \
                << "Failed Condition: " << #failureCondition << "\n" \
                << "Message  : " << message << "\n\n" \
                << "Location : " << __FILE__ << ", Line " << __LINE__ << "\n" \
                << "Function : " << __PRETTY_FUNCTION__ << "\n\n" \
                << "Stacktrace:\n" << GLESC::generateStackTrace(); \
            GLESC::Logger::get().error(oss.str()); \
            std::terminate(); \
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

#define D_ASSERT_NULL(value, message) \
        do { \
            ASSERT_CONTENT((value) == nullptr, message) \
        } while (false)

inline void
printComparingValues(const std::string &value, const std::string &expected) {
    GLESC::Logger::get().error("Checked Value : " + value + "\nExpected Value: " + expected);
}



template<typename Type>
inline bool assertEqualsEq(const Type &value, const Type &expected) {
    if constexpr (std::is_floating_point_v<Type>) {
        // Check if the numbers are close enough (within some epsilon).
        const Type epsilon = std::numeric_limits<Type>::epsilon();
        return std::fabs(value - expected) <= epsilon * std::fabs(value + expected)
            || std::fabs(value - expected) < epsilon;
    } else {
        // For non-floating point types, directly compare the values.
        return value == expected;
    }
}

#define D_ASSERT_EQUAL(value, expected, message) \
        printComparingValues(GLESC::Stringer::toString(value), GLESC::Stringer::toString(expected)); \
        do { \
            ASSERT_CONTENT(assertEqualsEq((value), (expected)), message) \
        } while (false)

#define D_ASSERT_GREATER(value, expected, message) \
        do { \
            ASSERT_CONTENT((value) > (expected), message) \
        } while (false)

#define D_ASSERT_GREATER_OR_EQUAL(value, expected, message) \
        do { \
            ASSERT_CONTENT((value) >= (expected), message) \
        } while (false)

#define D_ASSERT_LESS(value, expected, message) \
        do { \
            ASSERT_CONTENT((value) < (expected), message) \
        } while (false)

#define D_ASSERT_LESS_OR_EQUAL(value, expected, message) \
        do { \
            ASSERT_CONTENT((value) <= (expected), message) \
        } while (false)

#define D_ASSERT_NOT_EQUAL(value, expected, message) \
        do { \
            ASSERT_CONTENT(!assertEqualsEq((value), (expected)), message) \
        } while (false)


// ------------------------ Static asserts ---------------------------
// Static asserts are used to check conditions at compile time

#define S_ASSERT_TRUE(condition, message) \
        static_assert(condition, message)
        
#define S_ASSERT_FALSE(condition, message) \
        static_assert(!(condition), message)
        
#define S_ASSERT_EQUAL(condition, expected, message) \
        static_assert(GLESC::Math::eq(condition, expected), message)

#define S_ASSERT_GREATER(condition, expected, message) \
        static_assert(condition > expected, message)

#define S_ASSERT_GREATER_OR_EQUAL(condition, expected, message) \
        static_assert(condition >= expected, message)

#define S_ASSERT_LESS(condition, expected, message) \
        static_assert(condition < expected, message)

#define S_ASSERT_LESS_OR_EQUAL(condition, expected, message) \
        static_assert(condition <= expected, message)

#define S_ASSERT_NOT_EQUAL(condition, expected, message) \
        static_assert(condition != expected, message)

#else
// ------------------------ Empty asserts ---------------------------
// Empty asserts are used to substitute asserts in release mode,
// this way the compiler will optimize them out (remove them)

#define D_ASSERT_TRUE(condition, message) do {} while (false)
#define D_ASSERT_FALSE(condition, message) do {} while (false)
#define D_ASSERT_NOT_NULL(condition, message) do {} while (false)
#define D_ASSERT_NULL(condition, message) do {} while (false)
#define D_ASSERT_EQUAL(condition, expected, message) do {} while (false)
#define D_ASSERT_GREATER(condition, expected, message) do {} while (false)
#define D_ASSERT_GREATER_OR_EQUAL(condition, expected, message) do {} while (false)
#define D_ASSERT_LESS(condition, expected, message) do {} while (false)
#define D_ASSERT_LESS_OR_EQUAL(condition, expected, message) do {} while (false)
#define D_ASSERT_NOT_EQUAL(condition, expected, message) do {} while (false)

#define S_ASSERT_TRUE(condition, message) static_assert(true, message)
#define S_ASSERT_FALSE(condition, message) static_assert(true, message)
#define S_ASSERT_EQUAL(condition, expected, message) static_assert(true, message)
#define S_ASSERT_GREATER(condition, expected, message) static_assert(true, message)
#define S_ASSERT_GREATER_OR_EQUAL(condition, expected, message) static_assert(true, message)
#define S_ASSERT_LESS(condition, expected, message) static_assert(true, message)
#define S_ASSERT_LESS_OR_EQUAL(condition, expected, message) static_assert(true, message)
#define S_ASSERT_NOT_EQUAL(condition, expected, message) static_assert(true, message)


#endif
