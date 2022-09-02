#include "TextureManager.h"

SDL_Surface* TextureManager::LoadTexture(const char* texturePath){
    /**
     * @brief SDL_Surface is a set of pixels which are loaded inside the RAM.
     * Used for CPU rendering, useful for procedural generated textures.
     * This will be used for generating the OpenGL textures.
     * 
     */
    SDL_Surface* tempSurface;

    tempSurface = IMG_Load(texturePath);        //Load image from texture path

    if (tempSurface == nullptr){                //Check if the texture is null
        std::cout << texturePath << std::endl;
        std::cout << "Image null" << std::endl;
        printf(SDL_GetError());
    }
    return tempSurface;
}