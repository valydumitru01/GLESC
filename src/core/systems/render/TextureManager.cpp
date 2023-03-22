#include "core/renderer/TextureManager.h"

SDL_Surface *TextureManager::LoadTexture(const char *texturePath) {
	/**
	 * @brief SDL_Surface is a set of pixels which are loaded inside the RAM.
	 * Used for CPU rendering, useful for procedural generated textures.
	 * This will be used for generating the OpenGL textures.
	 *
	 */
	SDL_Surface *tempSurface;

	tempSurface = IMG_Load(texturePath);        //Load image from texture path

	if (tempSurface == nullptr) {                //Check if the texture is null
		std::cout << texturePath << std::endl;
		std::cout << "Image null" << std::endl;
		printf(SDL_GetError());
	}

	return flipSurface(tempSurface);
}

SDL_Surface *TextureManager::flipSurface(SDL_Surface *surface) {
	int current_line, pitch;
	SDL_Surface *flipped_surface = SDL_CreateRGBSurface(0,
	                                                    surface->w, surface->h,
	                                                    surface->format->BitsPerPixel,
	                                                    surface->format->Rmask,
	                                                    surface->format->Gmask,
	                                                    surface->format->Bmask,
	                                                    surface->format->Amask);


	int locked1, locked2;
	locked1 = SDL_LockSurface(surface);

	locked2 = SDL_LockSurface(flipped_surface);

	if (locked1 == -1 || locked2 == -1) {
		std::cout << "SDL_Surface couldn't be locked" << std::endl;
		printf(SDL_GetError());
	}

	pitch = surface->pitch;
	for (current_line = 0; current_line < surface->h; current_line++) {
		memcpy(&((unsigned char *) flipped_surface->pixels)[current_line * pitch],
		       &((unsigned char *) surface->pixels)[(surface->h - 1 - current_line) * pitch],
		       pitch);
	}

	SDL_UnlockSurface(flipped_surface);
	SDL_UnlockSurface(surface);
	return flipped_surface;
}
