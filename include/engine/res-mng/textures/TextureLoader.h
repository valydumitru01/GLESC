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
    static SDL_SurfacePtr loadTexture(const std::string &path, bool flipTexture);

private:
    
    static SDL_SurfacePtr flipSurface(SDL_Surface &surface);
    static SDL_SurfacePtr createSurface(const std::string &filePath);
};
