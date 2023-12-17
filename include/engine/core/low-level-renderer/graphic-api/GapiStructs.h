/**************************************************************************************************
 * @file   GapiStructs.h
 * @author Valentin Dumitru
 * @date   2023-11-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once


#include "GapiTypes.h"

namespace GAPI {
    struct RGBAColor {
        GAPI::UByte r;
        GAPI::UByte g;
        GAPI::UByte b;
        GAPI::UByte a;
        
        RGBAColor() : r(0), g(0), b(0), a(0) {}
        
        [[maybe_unused]] RGBAColor(GAPI::UByte r, GAPI::UByte g, GAPI::UByte b, GAPI::UByte a) :
                r(r), g(g), b(b), a(a) {}
        
        bool operator==(const RGBAColor &other) const {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }
        
        bool operator<(const RGBAColor &other) const {
            return r < other.r && g < other.g && b < other.b && a < other.a;
        }
        
        std::string toString() const {
            return "RGBAColor(" + std::to_string(r) + ", " + std::to_string(g) + ", " +
                   std::to_string(b) + ", " + std::to_string(a) + ")";
        }
    }; // struct RGBColor
    
    
    struct RGBAColorNormalized {
        GAPI::Float r;
        GAPI::Float g;
        GAPI::Float b;
        GAPI::Float a;
        
        RGBAColorNormalized() : r(0), g(0), b(0), a(0) {}
        
        [[maybe_unused]] RGBAColorNormalized(GAPI::Float r,
                                             GAPI::Float g,
                                             GAPI::Float b,
                                             GAPI::Float a) : r(r), g(g), b(b), a(a) {}
    }; // struct RGBColorNormalized
    
    
    struct Viewport {
        GAPI::Int x;
        GAPI::Int y;
        GAPI::Int width;
        GAPI::Int height;
        
        Viewport() : x(0), y(0), width(0), height(0) {}
        
        [[maybe_unused]] Viewport(GAPI::Int x, GAPI::Int y, GAPI::Int width, GAPI::Int height) :
                x(x), y(y), width(width), height(height) {}
    }; // struct Viewport
} // namespace GAPI

using RGBA = GAPI::RGBAColor;
using RGBANorm = GAPI::RGBAColorNormalized;


namespace std {
    template<>
    struct hash<RGBA> {
        std::size_t operator()(const RGBA &color) const {
            // Implement a simple hash function for RGBA
            // This is a basic example, and you might want to use a more sophisticated approach
            return (std::hash<float>()(color.r) ^ std::hash<float>()(color.g) << 1 ^
                    std::hash<float>()(color.b) << 2 ^ std::hash<float>()(color.a) << 3);
        }
    };
}

namespace std {
    template<>
    struct hash<RGBANorm> {
        std::size_t operator()(const RGBANorm &color) const {
            // Implement a simple hash function for RGBA
            // This is a basic example, and you might want to use a more sophisticated approach
            return (std::hash<float>()(color.r) ^ std::hash<float>()(color.g) << 1 ^
                    std::hash<float>()(color.b) << 2 ^ std::hash<float>()(color.a) << 3);
        }
    };
}