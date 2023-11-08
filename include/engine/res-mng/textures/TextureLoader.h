/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <boost/bimap.hpp>
#include <SDL2/SDL_image.h>
#include "engine/Config.h"
#include "engine/core/exceptions/resources/ResourceException.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/res-mng/textures/TextureLoader.h"

class TextureLoader {
public:
    TextureLoader();
    
    void loadTexture(const std::string &filePath);

private:
    static SDL_Surface &flipSurface(SDL_Surface &surface);
    
    
    SDL_Surface &createSurface(const std::string &filePath);
    
    /**
     * @brief Bidirectional map cache of the textures that have been loaded.
     * @details This is used to cache the textures so they don't have to be loaded every time.
     */
    boost::bimap<size_t, GAPIuint> textureCache;
    
    /**
     * @brief Hasher used to hash the file path.
     * @details This is used to hash the file path so it can be used as a key in the cache.
     */
    std::hash<std::string> hasher;
};
