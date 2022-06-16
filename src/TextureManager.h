#pragma once
#include "Game.h"


class TextureManager {
    public:
        /**
         * @brief Takes the path of an image and the renderer and loads the texture
         * 
         * @param fileName 
         * @param ren 
         * @return SDL_Texture* 
         */
        static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);

};