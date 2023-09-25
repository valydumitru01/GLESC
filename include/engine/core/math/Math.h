/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
namespace GLESC {
    namespace Math {
        constexpr float FLOAT_COMPARISON_EPSILON = 1e-6f;
        constexpr double DOUBLE_COMPARISON_EPSILON = 1e-10;
        constexpr float PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286f;
        
        template<typename T>
        inline bool decimalEquals(T a, T b, T epsilon) {
            return std::abs(a - b) < epsilon;
        }
        
        inline bool floatEquals(float a, float b) {
            return decimalEquals(a, b, FLOAT_COMPARISON_EPSILON);
        }
        
        inline bool doubleEquals(double a, double b) {
            return decimalEquals(a, b, DOUBLE_COMPARISON_EPSILON);
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
            return lerp(lerp(a, b, t), lerp(b, c, t), lerp(c, d, t), lerp(d, e, t), t);
        }
        
        template<typename T>
        T lerp(T a, T b, T c, T d, T e, T f, float t) {
            return lerp(lerp(a, b, t), lerp(b, c, t), lerp(c, d, t), lerp(d, e, t), lerp(e, f, t), t);
        }
        
        template<typename T>
        T lerp(T a, T b, T c, T d, T e, T f, T g, float t) {
            return lerp(lerp(a, b, t), lerp(b, c, t), lerp(c, d, t), lerp(d, e, t), lerp(e, f, t), lerp(f, g, t), t);
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
}