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

#ifndef NDEBUG
// ------------------------ Runtime asserts ---------------------------
// Runtime asserts are used to check conditions at runtime


#define ASSERT_CONTENT(condition, message) \
            std::ostringstream oss;                                              \
            oss << "Assertion failed: " << #condition << "\n"                    \
                << "Message: " << message << "\n"                                \
                << "File: " << __FILE__ << "\n"                                  \
                << "Line: " << __LINE__ << "\n"                                  \
                << "Function: " << __PRETTY_FUNCTION__ << "\n"                   \
                << "Stacktrace: \n" << GLESC::generateStackTrace();              \
            GLESC::Logger::get().error(oss.str());                               \
            std::terminate();



#define D_ASSERT(condition, message) \
        do { \
            if (! (condition)) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_FALSE(condition, message) \
        do { \
            if (condition) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_NOT_NULL(condition, message) \
        do { \
            if (condition == nullptr) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_NULL(condition, message) \
        do { \
            if (condition != nullptr) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_EQUAL(condition, expected, message) \
        do { \
            if (condition != expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_GREATER(condition, expected, message) \
        do { \
            if (condition <= expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_GREATER_OR_EQUAL(condition, expected, message) \
        do { \
            if (condition < expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_LESS(condition, expected, message) \
        do { \
            if (condition >= expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)
#define D_ASSERT_LESS_OR_EQUAL(condition, expected, message) \
        do { \
            if (condition > expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define D_ASSERT_NOT_EQUAL(condition, expected, message) \
        do { \
            if (condition == expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
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
