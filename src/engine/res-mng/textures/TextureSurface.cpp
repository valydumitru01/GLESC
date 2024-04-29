/**************************************************************************************************
 * @file   TextureSurface.cpp
 * @author Valentin Dumitru
 * @date   28/04/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/res-mng/textures/TextureSurface.h"

#include "engine/res-mng/textures/TextureLoader.h"
using namespace GLESC::ResMng::Texture;

TextureSurface::TextureSurface(const std::string& pathParam, bool flipTexture) {
    load(pathParam, flipTexture);
}

void TextureSurface::initializeData(SDL_Surface& sdlSurface) {
    // TODO: Is all this copying really necessary? Maybe use the SDL_Surface directly?
    //    But having our own format is useful

    format = Format();

    format.rMask = sdlSurface.format->Rmask;
    format.gMask = sdlSurface.format->Gmask;
    format.bMask = sdlSurface.format->Bmask;
    format.aMask = sdlSurface.format->Amask;
    format.rLoss = sdlSurface.format->Rloss;
    format.gLoss = sdlSurface.format->Gloss;
    format.bLoss = sdlSurface.format->Bloss;
    format.aLoss = sdlSurface.format->Aloss;
    format.rShift = sdlSurface.format->Rshift;
    format.gShift = sdlSurface.format->Gshift;
    format.bShift = sdlSurface.format->Bshift;
    format.aShift = sdlSurface.format->Ashift;


    // Assert that the bits per pixel is as expected
    D_ASSERT_TRUE(isDppCorrect(sdlSurface.format->BitsPerPixel), "Bits per pixel is not correct");

    if (format.aMask)
        format.colorFormat = ColorFormat::RGBA;
    else
        format.colorFormat = ColorFormat::RGB;

    // Set format's bit depth
    format.bitDepth = static_cast<BitDepth>(sdlSurface.format->BitsPerPixel);

    // Set texture dimensions
    width = static_cast<UInt>(sdlSurface.w);
    height = static_cast<UInt>(sdlSurface.h);

    // Calculate the total number of bytes for all pixels
    size_t totalBytes = width * height * static_cast<size_t>(sdlSurface.format->BytesPerPixel);

    // Resize the pixel vector to accommodate all bytes
    pixels.resize(totalBytes);

    // Copy the pixel data using memcpy for efficiency
    std::memcpy(pixels.data(), sdlSurface.pixels, totalBytes);
}

Pixel TextureSurface::getPixel(unsigned int x, unsigned int y) const {
    D_ASSERT_TRUE(hasLoaded, "Texture not loaded");
    D_ASSERT_LESS(x, width, "X coordinate out of bounds");
    D_ASSERT_LESS(y, height, "Y coordinate out of bounds");
    auto baseUBytePixelPtr = pixels.data();

    // Calculate the number of bytes per pixel
    // Divide by 8 because the bit depth is stored in bits and each byte has 8 bits
    auto byteDepth = static_cast<UInt>(format.bitDepth) / 8;

    // Move the pointer to the pixel we want to read
    // Multiply by byteDepth because the pixel data is stored as bytes
    baseUBytePixelPtr += (y * width + x) * byteDepth;
    Uint32 pixelValue = 0;

    for (UInt i = 0; i < byteDepth; ++i) {
        pixelValue |= static_cast<Uint32>(baseUBytePixelPtr[i]) << (8 * i);
    }

    // Extract the individual color components
    auto r = static_cast<Uint8>((pixelValue & format.rMask) >> format.rShift);
    auto g = static_cast<Uint8>((pixelValue & format.gMask) >> format.gShift);
    auto b = static_cast<Uint8>((pixelValue & format.bMask) >> format.bShift);
    Uint8 a = (format.aMask != 0)
                  ? static_cast<Uint8>((pixelValue & format.aMask) >> format.aShift)
                  : 255;

    // Normalize if needed (i.e. if the bit depth is less than 8)
    r = (format.rLoss != 0) ? r * 255 / ((1 << format.rLoss) - 1) : r;
    g = (format.gLoss != 0) ? g * 255 / ((1 << format.gLoss) - 1) : g;
    b = (format.bLoss != 0) ? b * 255 / ((1 << format.bLoss) - 1) : b;
    // Alpha normalization is typically not needed if alpha is either 0 or 255

    return Pixel{r, g, b, a};
}


void TextureSurface::load(const std::string& pathParam, bool flipTexture) {
    D_ASSERT_FALSE(pathParam.empty(), "File path is empty.");
    SDL_SurfacePtr sdlSurface = TextureLoader::loadTexture(
        ASSETS_PATH + std::string("/") + pathParam, flipTexture);
    initializeData(*sdlSurface);
    // Texture is now loaded, must be set to true right after the texture is loaded
    // the above functions will throw an error if the texture is not loaded
    hasLoaded = true;
}


std::string TextureSurface::toString() const {
    D_ASSERT_TRUE(hasLoaded, "Texture not loaded");
    std::stringstream ss;
    ss << "Texture:\n";
    ss << "\tWidth: " << width << "\n";
    ss << "\tHeight: " << height << "\n";
    ss << "\tTotal of pixels: " << getTotalOfPixels() << "\n";
    ss << "\tFormat:\n" << format.toString() << "\n";

    unsigned int pixelCount = 20;
    pixelCount = Math::sqrt(pixelCount);
    unsigned int widthStep = std::max(1u, getWidth() / pixelCount);
    unsigned int heightStep = std::max(1u, getHeight() / pixelCount);
    Logger::get().info("\tPixels:");
    for (UInt y = 0; y < getHeight() - 1; y += heightStep) {
        for (UInt x = 0; x < getWidth() - 1; x += widthStep) {
            auto pixel = getPixel(x, y);

            Logger::get().info("\t\tPixel at (" + std::to_string(x) + ", " + std::to_string(y) +
                "): " + pixel.toString());
        }
    }
    return ss.str();
}
