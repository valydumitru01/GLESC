/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/res-mng/textures/TextureManager.h"
#include <memory>
#include "engine/core/logger/Logger.h"
#include "engine/core/exceptions/resources/ResourceException.h"

TextureManager::TextureManager(GraphicInterface &graphicInterfaceParam) : graphicInterface(graphicInterfaceParam) {
    Logger::get().importantInfo("Texture manager created.");
}

GDIuint TextureManager::loadTexture(const std::string &filePath, GDIValues minFilter,
                                    GDIValues magFilter, GDIValues wrapS,
                                    GDIValues wrapT) {
    // Check if the texture is already in the cache
    size_t hashedPath = hasher(filePath);
    if (textureCache.left.find(hashedPath) != textureCache.left.end()) {
        return textureCache.left.at(hasher(filePath));
    }
    
    GDIuint textureID = graphicInterface.createTexture(createSurface(filePath), minFilter, magFilter, wrapS, wrapT);
    textureCache.insert({hashedPath, textureID});
    return textureID;
}

SDL_Surface &TextureManager::createSurface(const std::string &filePath) {
    // Load the image
    std::unique_ptr <SDL_Surface, decltype(&SDL_FreeSurface)> surfacePtr(IMG_Load(filePath.c_str()), &SDL_FreeSurface);
    // Check if the image was loaded
    if (surfacePtr == nullptr)
        throw ResourceException("Image couldn't be loaded. "
                              "Image path: " + std::string(filePath) + "SDL error:" + std::string(SDL_GetError()));
    SDL_Surface &surface = *surfacePtr;
    // If its opengl, flip
    if (graphicInterface.getGraphicsAPI() == GraphicsAPI::OPENGL) {
        flipSurface(surface);
    }
}

void TextureManager::deleteTexture(GDIuint textureID) {
    graphicInterface.deleteTexture(textureID);
}

void TextureManager::bindTexture(GDIuint textureID) {
    graphicInterface.bindTexture(textureID);
}


SDL_Surface &TextureManager::flipSurface(SDL_Surface &surface) {
    SDL_Surface *flippedSurface =
            SDL_CreateRGBSurface(0, surface.w, surface.h, surface.format->BitsPerPixel, surface.format->Rmask,
                                 surface.format->Gmask, surface.format->Bmask, surface.format->Amask);
    if (flippedSurface == nullptr)
        throw ResourceException("SDL_Surface couldn't be created" + std::string(SDL_GetError()));
    
    
    // Lock the surface so we can access the pixels
    int locked1 = SDL_LockSurface(&surface);
    int locked2 = SDL_LockSurface(flippedSurface);
    
    // If the surface couldn't be locked
    if (locked1 == -1 || locked2 == -1)
        throw ResourceException("SDL_Surface couldn't be locked" + std::string(SDL_GetError()));
    
    
    // Copy the pixels from the surface to the flipped surface
    int pitch = surface.pitch;
    for (int currentLine = 0; currentLine < surface.h; currentLine++) {
        memcpy(&((unsigned char *) flippedSurface->pixels)[currentLine * pitch],
               &((unsigned char *) surface.pixels)[(surface.h - 1 - currentLine) * pitch], pitch);
    }
    // Unlock the surface so we can access the pixels again
    SDL_UnlockSurface(flippedSurface);
    SDL_UnlockSurface(&surface);
    
    return *flippedSurface;
}