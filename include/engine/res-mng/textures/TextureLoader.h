/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <SDL2/SDL_image.h>
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"


using SDL_SurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;

class TextureLoader {
public:
    static SDL_SurfacePtr loadTexture(const std::string &path);

private:
    
    static SDL_SurfacePtr flipSurface(SDL_Surface &surface);
    
    
    static SDL_SurfacePtr createSurface(const std::string &filePath);
    
    /**
     * @brief Hasher used to hash the file path.
     * @details This is used to hash the file path so it can be used as a key in the cache.
     */
    static std::hash<std::string> hasher;
};
