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
#include "engine/core/asserts/Asserts.h"


namespace GLESC::Math {
    constexpr float FLOAT_COMPARISON_EPSILON = 1e-6f;
    constexpr double DOUBLE_COMPARISON_EPSILON = 1e-10;
    constexpr float PI =
            3.1415926535897932384626433832795028841971693993751058209749445923f;
    
    template<typename T>
    constexpr inline bool eq(T a, T b) {
        return a == b;
    }
    
    template<>
    constexpr inline bool eq<float>(float a, float b) {
        return std::fabs(a - b) < FLOAT_COMPARISON_EPSILON;
    }
    
    template<>
    constexpr inline bool eq<double>(double a, double b) {
        return std::fabs(a - b) < DOUBLE_COMPARISON_EPSILON;
    }
    
    
    
    
    template<typename T>
    T clamp(T value, T min, T max) {
        if (value < min) {
            return min;
        } else if (value > max) {
            return max;
        } else {
            return value;
        }
    }
    
    template<typename T>
    T lerp(T a, T b, float t) {
        return a + (b - a) * t;
    }
    
    template<typename T>
    T lerp(T a, T b, T c, float t) {
        return lerp(lerp(a, b, t), lerp(b, c, t), t);
    }
    
    template<typename T>
    T lerp(T a, T b, T c, T d, float t) {
        return lerp(lerp(a, b, t), lerp(b, c, t), lerp(c, d, t), t);
    }
    
    template<typename T>
    T lerp(T a, T b, T c, T d, T e, float t) {
        return lerp(lerp(a, b, t), lerp(b, c, t), lerp(c, d, t),
                    lerp(d, e, t), t);
    }
    
    template<typename T>
    T lerp(T a, T b, T c, T d, T e, T f, float t) {
        return lerp(lerp(a, b, t), lerp(b, c, t), lerp(c, d, t),
                    lerp(d, e, t), lerp(e, f, t), t);
    }
    
    template<typename T>
    T lerp(T a, T b, T c, T d, T e, T f, T g, float t) {
        return lerp(lerp(a, b, t), lerp(b, c, t), lerp(c, d, t),
                    lerp(d, e, t), lerp(e, f, t), lerp(f, g, t), t);
    }
    
    template<typename T>
    T lerp(T a, T b, T c, T d, T e, T f, T g, T h, float t) {
        return lerp(lerp(a, b, t), lerp(b, c, t),
                    lerp(c, d, t), lerp(d, e, t),
                    lerp(e, f, t), lerp(f, g, t),
                    lerp(g, h, t), t);
    }
    
    template<typename T>
    T lerp(T a, T b, T c, T d, T e, T f, T g, T h, T i, float t) {
        return lerp(lerp(a, b, t), lerp(b, c, t),
                    lerp(c, d, t), lerp(d, e, t),
                    lerp(e, f, t), lerp(f, g, t),
                    lerp(g, h, t), lerp(h, i, t), t);
    }
    
}
