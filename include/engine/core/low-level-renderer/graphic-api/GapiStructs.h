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
    struct RGBColor {
        GAPI::UByte r;
        GAPI::UByte g;
        GAPI::UByte b;
        GAPI::UByte a;
        
        RGBColor() : r(0), g(0), b(0), a(0) {}
        
        [[maybe_unused]] RGBColor(GAPI::UByte r, GAPI::UByte g, GAPI::UByte b, GAPI::UByte a)
                : r(r), g(g), b(b), a(a) {}
    }; // struct RGBColor
    
    
    struct RGBColorNormalized {
        GAPI::Float r;
        GAPI::Float g;
        GAPI::Float b;
        GAPI::Float a;
        
        RGBColorNormalized() : r(0), g(0), b(0), a(0) {}
        
        [[maybe_unused]] RGBColorNormalized(GAPI::Float r,
                                            GAPI::Float g,
                                            GAPI::Float b,
                                            GAPI::Float a)
                : r(r), g(g), b(b), a(a) {}
    }; // struct RGBColorNormalized
    
    
    struct Viewport {
        GAPI::Int x;
        GAPI::Int y;
        GAPI::Int width;
        GAPI::Int height;
        
        Viewport() : x(0), y(0), width(0), height(0) {}
        
        [[maybe_unused]] Viewport(GAPI::Int x, GAPI::Int y, GAPI::Int width, GAPI::Int height)
                : x(x), y(y), width(width), height(height) {}
    }; // struct Viewport
    
} // namespace GAPI