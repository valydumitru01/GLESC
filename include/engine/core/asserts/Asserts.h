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
#include "engine/core/debugger/Stacktrace.h"
#include "engine/core/logger/Logger.h"

#ifndef NDEBUG
// ------------------------ Runtime asserts ---------------------------
// Runtime asserts are used to check conditions at runtime


#define ASSERT_CONTENT(condition, message) \
        std::string stacktrace = GLESC::generateStackTrace(); \
        Logger::get().error( \
            "Assertion `" #condition "` failed in " + std::string(__FILE__) + \
            " line " + std::to_string(__LINE__) + ": \n\t" + \
            std::string(message) + "\nStacktrace:\n" + stacktrace); \
        std::terminate();

#define ASSERT(condition, message) \
        do { \
            if (! (condition)) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define ASSERT_FALSE(condition, message) \
        do { \
            if (condition) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define ASSERT_NOT_NULL(condition, message) \
        do { \
            if (condition == nullptr) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define ASSERT_NULL(condition, message) \
        do { \
            if (condition != nullptr) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define ASSERT_EQUAL(condition, expected, message) \
        do { \
            if (condition != expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define ASSERT_GREATER(condition, expected, message) \
        do { \
            if (condition <= expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define ASSERT_GREATER_OR_EQUAL(condition, expected, message) \
        do { \
            if (condition < expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)

#define ASSERT_LESS(condition, expected, message) \


#define ASSERT_NOT_EQUAL(condition, expected, message) \
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

#define ASSERT(condition, message) do { } while (false)
#define ASSERT_FALSE(condition, message) do { } while (false)
#define ASSERT_NOT_NULL(condition, message) do { } while (false)
#define ASSERT_NULL(condition, message) do { } while (false)
#define ASSERT_EQUAL(condition, expected, message) do { } while (false)
#define ASSERT_GREATER(condition, expected, message) do { } while (false)
#define ASSERT_GREATER_OR_EQUAL(condition, expected, message) do { } while (false)
#define ASSERT_LESS(condition, expected, message) do { } while (false)
#define ASSERT_LESS_OR_EQUAL(condition, expected, message) do { } while (false)
#define ASSERT_NOT_EQUAL(condition, expected, message) do { } while (false)

#define S_ASSERT_EQUAL(condition, expected, message) do { } while (false)
#define S_ASSERT_GREATER(condition, expected, message) do { } while (false)
#define S_ASSERT_GREATER_OR_EQUAL(condition, expected, message) do { } while (false)
#define S_ASSERT_LESS(condition, expected, message) do { } while (false)
#define S_ASSERT_LESS_OR_EQUAL(condition, expected, message) do { } while (false)
#define S_ASSERT_NOT_EQUAL(condition, expected, message) do { } while (false)


#endif
