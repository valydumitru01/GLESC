#pragma once
#include <iostream>
#include <stdexcept>

#ifndef NDEBUG
    #define ASSERT_CONTENT(condition, message) "Assertion `" #condition "` failed in " << __FILE__ \
                          << " line " << __LINE__ << ": " << message << std::endl \
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