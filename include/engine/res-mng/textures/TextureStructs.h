/**************************************************************************************************
 * @file   TextureStructs.h
 * @author Valentin Dumitru
 * @date   30/11/2023
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <iomanip>
#include <sstream>

#include "TextureEnums.h"

using namespace GLESC::GAPI;

/**
 * @brief A pixel abstraction class that holds the RGBA values of a pixel
 */
[[nodiscard]] struct Pixel {
    UByte r{}, g{}, b{}, a{};
    
    Pixel() = default;
    
    Pixel(UByte rParam, UByte gParam, UByte bParam, UByte aParam)
            : r(rParam), g(gParam), b(bParam), a(aParam) {}
    
    RGBAColorNormalized getColorNormalized() const {
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
    
    RGBAColor getColor() const { return {r, g, b, a}; }
};


/**
 * @brief A struct that holds the format of a texture
 */
[[nodiscard]] struct Format {
    GLESC::ResMng::Texture::ColorFormat colorFormat;
    GLESC::ResMng::Texture::BitDepth bitDepth;
    Uint32 rMask, gMask, bMask, aMask;
    Uint8 rLoss, gLoss, bLoss, aLoss;
    Uint8 rShift, gShift, bShift, aShift;
    
    std::string toString() const {
        
        std::string bitDepthString = GLESC::ResMng::Texture::toString(bitDepth);
        std::string  colorFormatString = GLESC::ResMng::Texture::toString(colorFormat);
        std::stringstream ss;
        auto maskLength = static_cast<unsigned int>(bitDepth) / 4;
        ss << std::hex << std::setfill('0');
        ss << "\tBit depth: " << bitDepthString << "\n";
        ss << "\tColor format: " << colorFormatString << "\n";
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