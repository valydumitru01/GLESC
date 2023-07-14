#pragma once

#include <memory>
#include <fstream>

#include "SDL2/SDL_image.h"
#include "GL/glew.h"

#include "engine/foundation/data-structures/BidirectionalMap.h"
#include "engine/core/debug-profile/Console.h"
#include "RenderDebugger.h"
#include "engine/exceptions/EngineException.h"

class TextureManager {
public:
    /**
     * @brief Takes the path of an image and the renderer and loads the texture.
     * This function will load the texture and flip it because OpenGL expects the image to be flipped.
     * @param fileName
     * @return SDL_Texture*
     */
    GLuint loadTexture(const std::string &filePath, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR,
                       GLint wrapS = GL_REPEAT, GLint wrapT = GL_REPEAT);
    
    void deleteTexture(GLuint textureID);
    
    void bindTexture(GLuint texture);

private:
    /**
     * @brief Flips the surface
     *  This is used to flip the surface because OpenGL expects the image to be flipped.
     * @param surface
     * @return
     */
    std::unique_ptr <SDL_Surface, decltype(&SDL_FreeSurface)> flipSurface(SDL_Surface &surface);
    
    /**
     * @brief Creates the texture and returns the texture ID.
     * @details This function will create the texture and return the texture ID. This is used to create the texture
     * and then cache it. For the format of the texture, it will use the number of channels in the image.
     * If the image has 4 channels, it will use GL_RGBA, if it has 3 channels, it will use GL_RGB.
     * This means that the image must be either a PNG or a JPG.
     * @param filePath The path of the image.
     * @param minFilter The minification filter.
     * @param magFilter The magnification filter.
     * @param wrapS The wrap mode for the S axis.
     * @param wrapT The wrap mode for the T axis.
     * @return The texture ID.
     */
    GLuint
    createTexture(const std::string &filePath, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT);
    
    /**
     * @brief Bidirectional map cache of the textures that have been loaded.
     * @details This is used to cache the textures so they don't have to be loaded every time.
     * This is useful for performance.
     */
    BidirectionalMap <std::string, GLuint> textureCache;
};