/******************************************************************************
 * @file   TextureLoader.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/exceptions/resources/ResourceException.h"
#include "engine/core/logger/Logger.h"
#include "engine/res-mng/textures/TextureLoader.h"

#include "engine/core/debugger/Debugger.h"
#include "engine/core/file-system/BinPath.h"


SDL_SurfacePtr TextureLoader::createSurface(const std::string &filePath) {
    D_ASSERT_FALSE(filePath.empty(), "File path is empty.");
    std::string fullImagePath = BinPath::getExecutableDirectory() + "/" + filePath;
    Logger::get().info("Loading image: " + fullImagePath);
    // Load the image
    SDL_SurfacePtr surfacePtr(IMG_Load(fullImagePath.c_str()), &SDL_FreeSurface);
    //postSDLCall
    SDL_ClearError();
    // Check if the image was loaded
    D_ASSERT_NOT_NULLPTR(surfacePtr, "Image couldn't be loaded. Image path: " + fullImagePath +
                                     ", SDL error: " + SDL_GetError());
    Logger::get().success("Image loaded successfully: " + filePath);
    return surfacePtr;
}


/**
 * @brief Takes the path of an image and loads it into a texture.
 * @param filePath The path of the image.
 * @param flipTexture
 * @return The image data of the loaded image.
 */
SDL_SurfacePtr TextureLoader::loadTexture(const std::string &filePath, bool flipTexture) {
    D_ASSERT_FALSE(filePath.empty(), "File path is empty.");

    SDL_SurfacePtr surface = createSurface(filePath);
    if (flipTexture)
        surface = flipSurface(*surface.get());
    
    
    return surface;
}

SDL_SurfacePtr TextureLoader::flipSurface(SDL_Surface &surface) {
    SDL_SurfacePtr flippedSurface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(
            SDL_CreateRGBSurface(0, surface.w, surface.h, surface.format->BitsPerPixel,
                                 surface.format->Rmask, surface.format->Gmask,
                                 surface.format->Bmask, surface.format->Amask),
            &SDL_FreeSurface);
    
    D_ASSERT_NOT_NULLPTR(flippedSurface, "Flipped surface couldn't be created. SDL error: " +
                                         std::string(SDL_GetError()));
    
    Logger::get().info("Flipping image...");
    
    D_ASSERT_TRUE(!SDL_MUSTLOCK(&surface) || SDL_LockSurface(&surface) == 0,
                  "Original surface must be locked.");
    
    D_ASSERT_TRUE(!SDL_MUSTLOCK(flippedSurface.get()) || SDL_LockSurface(flippedSurface.get()) == 0,
                  "Flipped surface must be locked.");
    
    
    int pitch = surface.pitch;
    for (int currentLine = 0; currentLine < surface.h; ++currentLine) {
        memcpy(static_cast<unsigned char *>(flippedSurface->pixels) + currentLine * pitch,
               static_cast<unsigned char *>(surface.pixels) + (surface.h - 1 - currentLine) * pitch,
               pitch);
    }
    
    if (SDL_MUSTLOCK(&surface)) {
        SDL_UnlockSurface(&surface);
    }
    if (SDL_MUSTLOCK(flippedSurface.get())) {
        SDL_UnlockSurface(flippedSurface.get());
    }
    
    Logger::get().success("Image flipped successfully.");
    
    return flippedSurface;
}

