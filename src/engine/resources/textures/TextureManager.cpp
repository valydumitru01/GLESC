#include "engine/core/renderer/TextureManager.h"

GLuint
TextureManager::loadTexture(const std::string &filePath, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) {
    // Check if the texture is already in the cache
    if (textureCache.containsKey(filePath)) {
        return textureCache.getValue(filePath);
    }
    
    GLuint textureID = createTexture(filePath, minFilter, magFilter, wrapS, wrapT);
    textureCache.insert(filePath, textureID);
    return textureID;
}

GLuint
TextureManager::createTexture(const std::string &filePath, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) {
    // Load the image
    std::unique_ptr <SDL_Surface, decltype(&SDL_FreeSurface)> tempSurface(IMG_Load(filePath.c_str()), &SDL_FreeSurface);
    // Check if the image was loaded
    if (tempSurface == nullptr)
        throw EngineException("Image couldn't be loaded. "
                              "Image path: " + std::string(filePath) + "SDL error:" + std::string(SDL_GetError()));
    
    // Flip the surface because OpenGL expects the image to be flipped
    auto flippedSurface = flipSurface(*tempSurface);
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    bindTexture(textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    
    
    GLenum format = (flippedSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, flippedSurface->w, flippedSurface->h, 0, format, GL_UNSIGNED_BYTE,
                 flippedSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    bindTexture(0);
    
    return textureID;
}

std::unique_ptr <SDL_Surface, decltype(&SDL_FreeSurface)> TextureManager::flipSurface(SDL_Surface &surface) {
    SDL_Surface *flippedSurface =
            SDL_CreateRGBSurface(0, surface.w, surface.h, surface.format->BitsPerPixel, surface.format->Rmask,
                                 surface.format->Gmask, surface.format->Bmask, surface.format->Amask);
    
    // Lock the surface so we can access the pixels
    int locked1 = SDL_LockSurface(&surface);
    int locked2 = SDL_LockSurface(flippedSurface);
    
    // If the surface couldn't be locked
    if (locked1 == -1 || locked2 == -1)
        throw EngineException("SDL_Surface couldn't be locked" + std::string(SDL_GetError()));
    
    
    // Copy the pixels from the surface to the flipped surface
    int pitch = surface.pitch;
    for (int currentLine = 0; currentLine < surface.h; currentLine++) {
        memcpy(&((unsigned char *) flippedSurface->pixels)[currentLine * pitch],
               &((unsigned char *) surface.pixels)[(surface.h - 1 - currentLine) * pitch], pitch);
    }
    // Unlock the surface so we can access the pixels again
    SDL_UnlockSurface(flippedSurface);
    SDL_UnlockSurface(&surface);
    
    return {flippedSurface, SDL_FreeSurface};
}

void TextureManager::deleteTexture(GLuint textureID) {
    glDeleteTextures(1, &textureID);
    textureCache.eraseByValue(textureID);
}

void TextureManager::bindTexture(GLuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
}