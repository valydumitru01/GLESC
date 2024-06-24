/**************************************************************************************************
 * @file   TextureLoader.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once

#include <memory>
#include <SDL2/SDL_image.h>
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"


namespace GLESC {
    /**
     * @brief A smart pointer for SDL_Surface
     */
    using SDL_SurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
    /**
     * @brief A class that loads textures from the file system
     */
    class TextureLoader {
    public:
        /**
         * @brief Loads a texture from the file system
         * @param path The path to the texture
         * @param flipTexture If the texture should be flipped
         * @return A smart pointer to the texture
         */
        static SDL_SurfacePtr loadTexture(const std::string& path, bool flipTexture);

    private:
        /**
         * @brief Flips a surface
         * @details It is needed because some graphic APIs require textures to be flipped
         * @param surface The surface to flip
         * @return The flipped surface
         */
        static SDL_SurfacePtr flipSurface(SDL_Surface& surface);
        /**
         * @brief Creates a surface from a file, it is called by loadTexture
         * @param filePath The path to the file
         * @return The surface
         */
        static SDL_SurfacePtr createSurface(const std::string& filePath);
    };
}
