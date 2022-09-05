#pragma once
#include "Game.h"
class TextureManager {
    public:
        /**
         * @brief Takes the path of an image and the renderer and loads the texture.
         * 
         * @param fileName 
         * @param ren 
         * @return SDL_Texture* 
         */
        static SDL_Surface* LoadTexture(const char* fileName);
        
    private:
        static SDL_Surface* flipSurface(SDL_Surface * surface);

};