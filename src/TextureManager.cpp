#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texturePath, SDL_Renderer* ren){
    SDL_Surface* tempSurface = IMG_Load(texturePath);
    if (tempSurface == nullptr){
        std::cout << texturePath << std::endl;
        std::cout << "Image null" << std::endl;
        printf(SDL_GetError());
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}