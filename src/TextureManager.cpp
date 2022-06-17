#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texturePath, SDL_Renderer* ren){
    /**
     * @brief SDL_Surface is a set of pixels which are loaded inside the RAM.
     * Used for CPU rendering, useful for procedural generated textures (not our case).
     * 
     */
    SDL_Surface* tempSurface;
    /**
     * @brief SDL_Texture is also a set of pixels that are loaded inside the VRAM (GPU). More efficient.
     * It's more efficient because it's hardware rendering. It's using internally OpenGL or DirectX (OpenGL in our case). 
     * It's orders of magnitude faster.
     * 
     */
    SDL_Texture* tex;

    
    tempSurface = IMG_Load(texturePath);        //Load image from texture path

    if (tempSurface == nullptr){                //Check if the texture is null
        std::cout << texturePath << std::endl;
        std::cout << "Image null" << std::endl;
        printf(SDL_GetError());
    }
    tex = SDL_CreateTextureFromSurface(ren, tempSurface); //Create a surfice from the texture we loaded

    SDL_FreeSurface(tempSurface);               //Free the surface (flush, delete), as it's only being used to create the texture.

    return tex;
}