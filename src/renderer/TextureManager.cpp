#include "core/systems/render/TextureManager.h"

SDL_Surface *TextureManager::loadTexture(const char *texturePath) {
    // SDL_Surface is a set of pixels which are loaded inside the RAM.
    // Used for CPU rendering, useful for procedural generated textures.
    // This will be used for generating the OpenGL textures.
    SDL_Surface *tempSurface;

    tempSurface = IMG_Load(fileName);

    if (tempSurface == nullptr) {
        Console::error("Image couldn't be loaded. "
                       "Image path: " + std::string(fileName) + "SDL error:" + std::string(SDL_GetError()));
    }

    return flipSurface(tempSurface);
}

SDL_Surface *TextureManager::flipSurface(SDL_Surface *surface) {
    // Create a new surface with the same properties as the old one
    // This will be the flipped surface
    int current_line, pitch;
    SDL_Surface *flipped_surface = SDL_CreateRGBSurface(0, surface->w, surface->h,
                                                        surface->format->BitsPerPixel,
                                                        surface->format->Rmask, surface->format->Gmask,
                                                        surface->format->Bmask, surface->format->Amask);

    // Lock the surface so we can access the pixels
    int locked1, locked2;
    locked1 = SDL_LockSurface(surface);

    locked2 = SDL_LockSurface(flipped_surface);

    // If the surface couldn't be locked
    if (locked1 == -1 || locked2 == -1) {
        Console::error("SDL_Surface couldn't be locked" + std::string(SDL_GetError()));
    }

    // Copy the pixels from the surface to the flipped surface
    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line++) {
        memcpy(&((unsigned char *) flipped_surface->pixels)[current_line * pitch],
               &((unsigned char *) surface->pixels)[(surface->h - 1 - current_line) * pitch], pitch);
    }
    // Unlock the surface so we can access the pixels again
    SDL_UnlockSurface(flipped_surface);
    SDL_UnlockSurface(surface);
    return flipped_surface;
}
