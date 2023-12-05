/**************************************************************************************************
 * @file   TextureDebugger.h
 * @author Valentin Dumitru
 * @date   04/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once


#define PRINT_TEXTURE_DATA(texture) printTextureData(texture)

#ifndef NLOGGING

#include "engine/core/low-level-renderer/texture/Texture.h"

void printTextureData(GLESC::Texture &texture) {
    std::stringstream ss;
    Logger ::get().info(texture.toString());
    
    
    int pixelCount = 20;
    pixelCount = sqRoot(pixelCount);
    GAPI::UInt widthStep = std::max(1u, texture.getWidth() / pixelCount);
    GAPI::UInt heightStep = std::max(1u, texture.getHeight() / pixelCount);
    Logger ::get().info("\tPixels:");
    for (GAPI::UInt y = 0; y < texture.getHeight(); y += heightStep) {
        for (GAPI::UInt x = 0; x < texture.getWidth(); x += widthStep) {
            auto pixel = texture.getPixel(x, y);
            
            Logger ::get().info("\t\tPixel at (" + std::to_string(x) + ", " + std::to_string(y) +
                                "): " + pixel.toString());
        }
    }
}

#endif // NLOGGING