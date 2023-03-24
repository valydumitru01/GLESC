#pragma once

#include <SDL2/SDL_image.h>
#include "util/console.h"

class TextureManager {
public:
    /**
     * @brief Takes the path of an image and the renderer and loads the texture.
     * This function will load the texture and flip it because OpenGL expects the image to be flipped.
     * @param fileName
     * @return SDL_Texture*
     */
    static SDL_Surface *loadTexture(const char *fileName);

private:
    /**
     * @brief Flips the surface
     *  This is used to flip the surface because OpenGL expects the image to be flipped.
     * @param surface
     * @return
     */
    static SDL_Surface *flipSurface(SDL_Surface *surface);

};