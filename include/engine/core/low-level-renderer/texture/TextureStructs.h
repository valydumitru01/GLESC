/**************************************************************************************************
 * @file   TextureStructs.h
 * @author Valentin Dumitru
 * @date   30/11/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <iomanip>

#include "engine/core/low-level-renderer/graphic-api/debugger/GapiDebugger.h"
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

struct Pixel {
    GAPI::UByte r, g, b, a;
    
    Pixel() : r(0), g(0), b(0), a(0) {}
    
    Pixel(GAPI::UByte rParam, GAPI::UByte gParam, GAPI::UByte bParam, GAPI::UByte aParam)
            : r(rParam), g(gParam), b(bParam), a(aParam) {}
    
    GAPI::RGBColorNormalized getColorNormalized() const {
        return {r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f};
    }
    
    std::string toString() const {
        std::stringstream ss;
        ss << "RGB["
            << static_cast<unsigned>(r) << ", " << static_cast<unsigned>(g) << ", "
            << static_cast<unsigned>(b) << ", " << static_cast<unsigned>(a)
        << "]";
        return ss.str();
    }
    
    GAPI::RGBColor getColor() const { return {r, g, b, a}; }
};


struct Format {
    GAPI::Types dataType;
    GAPI::Texture::InternalFormat::BitDepth bitDepth;
    GAPI::Texture::InternalFormat::ColorFormat colorFormat;
    
    Uint32 rMask, gMask, bMask, aMask;
    Uint8 rLoss, gLoss, bLoss, aLoss;
    Uint8 rShift, gShift, bShift, aShift;
    
    std::string toString() const {
        std::stringstream ss;
        auto maskLength = static_cast<unsigned int>(bitDepth) / 4;
        ss << std::hex << std::setfill('0');
        ss << "\tData type: " << GAPI::toString(dataType) << "\n";
        ss << "\tBit depth: " << GAPI::toString(bitDepth) << "\n";
        ss << "\tColor format: " << GAPI::toString(colorFormat) << "\n";
        ss << "\tRed mask: 0x" << std::setw(maskLength) << rMask << "\n";
        ss << "\tGreen mask: 0x" << std::setw(maskLength) << gMask << "\n";
        ss << "\tBlue mask: 0x" << std::setw(maskLength) << bMask << "\n";
        ss << "\tAlpha mask: 0x" << std::setw(maskLength) << aMask << "\n";
        ss << "\tRed loss: " << std::hex << static_cast<unsigned>(rLoss) << "\n";
        ss << "\tGreen loss: " << std::hex << static_cast<unsigned>(gLoss) << "\n";
        ss << "\tBlue loss: " << std::hex << static_cast<unsigned>(bLoss) << "\n";
        ss << "\tAlpha loss: " << std::hex << static_cast<unsigned>(aLoss) << "\n";
        ss << "\tRed shift: " << std::hex << static_cast<unsigned>(rShift) << "\n";
        ss << "\tGreen shift: " << std::hex << static_cast<unsigned>(gShift) << "\n";
        ss << "\tBlue shift: " << std::hex << static_cast<unsigned>(bShift) << "\n";
        ss << "\tAlpha shift: " << std::hex << static_cast<unsigned>(aShift) << "\n";
        return ss.str();
    }
    
    Format() = default;
};