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
            ASSERT_CONTENT(value , message) \
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

#define D_ASSERT_EQUAL(value, expected, message) \
        printComparingValues(GLESC::toString(value), GLESC::toString(expected)); \
        do { \
            ASSERT_CONTENT(eq((value), (expected)), message) \
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
            ASSERT_CONTENT(!eq((value), (expected)), message) \
        } while (false)


// ------------------------ Static asserts ---------------------------
// Static asserts are used to check conditions at compile time

#define S_ASSERT(condition, message) \
        static_assert(condition, message)

#define S_ASSERT_EQUAL(condition, expected, message) \
        static_assert(condition == expected, message)

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

#define D_ASSERT(condition, message) do { } while (false)
#define D_ASSERT_FALSE(condition, message) do { } while (false)
#define D_ASSERT_NOT_NULL(condition, message) do { } while (false)
#define D_ASSERT_NULL(condition, message) do { } while (false)
#define D_ASSERT_EQUAL(condition, expected, message) do { } while (false)
#define D_ASSERT_GREATER(condition, expected, message) do { } while (false)
#define D_ASSERT_GREATER_OR_EQUAL(condition, expected, message) do { } while (false)
#define D_ASSERT_LESS(condition, expected, message) do { } while (false)
#define D_ASSERT_LESS_OR_EQUAL(condition, expected, message) do { } while (false)
#define D_ASSERT_NOT_EQUAL(condition, expected, message) do { } while (false)

#define S_ASSERT_EQUAL(condition, expected, message) do { } while (false)
#define S_ASSERT_GREATER(condition, expected, message) do { } while (false)
#define S_ASSERT_GREATER_OR_EQUAL(condition, expected, message) do { } while (false)
#define S_ASSERT_LESS(condition, expected, message) do { } while (false)
#define S_ASSERT_LESS_OR_EQUAL(condition, expected, message) do { } while (false)
#define S_ASSERT_NOT_EQUAL(condition, expected, message) do { } while (false)


#endif
