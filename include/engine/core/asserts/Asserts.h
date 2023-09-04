/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "engine/core/logger/Logger.h"

#ifndef NDEBUG
#define ASSERT_CONTENT(condition, message) \
        Logger::get().error("Assertion `" #condition "` failed in " + std::string(__FILE__) + " line " + \
        std::to_string(__LINE__) + ": \n\t" + std::string(message)); \
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

#define ASSERT_NOT_EQUAL(condition, expected, message) \
        do { \
            if (condition == expected) { \
                ASSERT_CONTENT(condition, message) \
            } \
        } while (false)
#else

#define ASSERT(condition, message) do { } while (false)

#endif