#pragma once

#include <boost/bimap.hpp>
#include <SDL2/SDL_image.h>
#include "engine/core/graphics-device-interface/GraphicsInterface.h"



class TextureManager {
public:
    /**
     * @brief Takes the path of an image and the renderer and loads the texture.
     * This function will load the texture and flip it because OpenGL expects the image to be flipped.
     * @param fileName
     * @return SDL_Texture*
     */
    GDIuint
    loadTexture(const std::string &filePath, TextureFilter::MinFilter minFilter = TextureFilter::MinFilter::Linear,
                TextureFilter::MagFilter magFilter = TextureFilter::MagFilter::Linear,
                TextureFilter::WrapMode wrapS = TextureFilter::WrapMode::Repeat,
                TextureFilter::WrapMode wrapT = TextureFilter::WrapMode::Repeat);
    /**
     * @brief
     * @param textureID
     */
    void deleteTexture(GDIuint textureID);
    /**
     * @brief
     * @param texture
     */
    void bindTexture(GDIuint texture);

private:
    /**
     * @brief Flips the surface
     *  This is used to flip the surface because OpenGL expects the image to be flipped.
     * @param surface
     * @return
     */
    SDL_Surface& flipSurface(SDL_Surface &surface);
    
    
    SDL_Surface& createSurface(const std::string &filePath);
    
    /**
     * @brief Pointer to the graphics interface.
     * The graphic interface creates the texture depending on the graphics API.
     */
    std::shared_ptr <GraphicsInterface> graphicsInterface;
    
    /**
     * @brief Bidirectional map cache of the textures that have been loaded.
     * @details This is used to cache the textures so they don't have to be loaded every time.
     */
    boost::bimap <size_t, GDIuint> textureCache;
    
    /**
     * @brief Hasher used to hash the file path.
     * @details This is used to hash the file path so it can be used as a key in the cache.
     */
    std::hash <std::string> hasher;
};