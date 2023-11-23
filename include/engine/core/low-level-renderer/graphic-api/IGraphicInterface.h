/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <SDL2/SDL.h>

#include "GapiEnums.h"
#include "GapiStructs.h"
#include "IUniformSetter.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

#ifdef GLESC_OPENGL
using UniformSetter = GLUniformSetter;
#endif

class IGraphicInterface {
public:
    IGraphicInterface() = default;
    
    virtual ~IGraphicInterface() = default;
    
    virtual void preWindowConfig() = 0;
    
    virtual void postWindowCreationInit() = 0;
    
    virtual void clear(const std::initializer_list<GAPIValues> &values) = 0;
    
    virtual void clearColor(GAPIfloat r, GAPIfloat g, GAPIfloat b, GAPIfloat a) = 0;
    
    virtual void setViewport(GAPIint width, GAPIint height) = 0;
    
    virtual void setViewport(GAPIint x, GAPIint y, GAPIint width, GAPIint height) = 0;
    
    virtual std::tuple<GAPIint, GAPIint, GAPIint, GAPIint> getViewport() = 0;
    
    virtual void swapBuffers(SDL_Window &window) = 0;
    
    virtual void createContext(SDL_Window &window) = 0;
    
    virtual void deleteContext() = 0;
    
    virtual void drawTriangles(GAPIuint start, GAPIuint count) = 0;
    
    virtual void drawTrianglesIndexed(GAPIuint count) = 0;
    
    virtual RGBColor readPixelColor(int x, int y) = 0;
    
    virtual RGBColorNormalized readPixelColorNormalized(int x, int y) = 0;
    
    
    
    // ------------------------------------------------------------------------------
    // -------------------------------- Buffers -------------------------------------
    
    virtual void genBuffers(GAPIuint amount, GAPIuint &bufferID) = 0;
    
    virtual void bindBuffer(GAPIValues bufferType, GAPIuint buffer) = 0;
    
    virtual void unbindBuffer(GAPIValues bufferType) = 0;
    
    virtual std::vector<float> getBufferDataF(GLuint bufferId) =0;
    
    virtual std::vector<unsigned int> getBufferDataUi(GLuint bufferId)=0;
    
    virtual std::vector<int> getBufferDataI(GLuint bufferId)=0;
    
    virtual void deleteBuffer(GAPIuint buffer) = 0;
    
    virtual void setBufferData(const void *data,
                               GAPIsize size,
                               GAPIValues bufferType,
                               GAPIValues bufferUsage) = 0;
    
    virtual void genVertexArray(GAPIuint &vertexArrayID) = 0;
    
    virtual void bindVertexArray(GAPIuint vertexArrayID) = 0;
    
    virtual void unbindVertexArray() = 0;
    
    virtual void deleteVertexArray(GAPIuint vertexArrayID) = 0;
    
    virtual void enableVertexData(GAPIuint index) = 0;
    
    virtual void createVertexData(GAPIuint vertexArray,
                                  GAPIuint count,
                                  GAPIType type,
                                  GAPIbool isNormalized,
                                  GAPIuint stride,
                                  GAPIuint offset) = 0;
    // ------------------------------------------------------------------------------
    // -------------------------------- Texture -------------------------------------
    
    /**
     * @brief Create a texture from an SDL_Surface
     * @details This function creates a texture from an SDL_Surface.
     * It also sets the texture parameters.
     * @param surface
     * @param minFilter
     * @param magFilter
     * @param wrapS
     * @param wrapT
     * @return
     */
    virtual GAPIuint createTexture(SDL_Surface &surface,
                                   GAPIValues minFilter,
                                   GAPIValues magFilter,
                                   GAPIValues wrapS,
                                   GAPIValues wrapT) = 0;
    
    /**
     * @brief Create texture with default parameters
     * @details The default parameters are:
     * minFilter = LINEAR
     * magFilter = LINEAR
     * wrapS = REPEAT
     * wrapT = REPEAT
     * @param textureID
     */
    virtual GAPIuint createTexture(SDL_Surface &surface) = 0;
    
    virtual void bindTexture(GAPIuint textureID) = 0;
    
    virtual void deleteTexture(GAPIuint textureID) = 0;
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    virtual void useShaderProgram(GAPIuint shaderProgram) = 0;
    
    virtual bool isShaderProgram(GAPIuint shaderProgram) = 0;
    
    virtual GAPIuint
    loadAndCompileShader(GAPIValues shaderType, const std::string &shaderSource) = 0;
    
    virtual bool compilationOK(GAPIuint shaderID, GAPIchar *message) = 0;
    
    virtual GAPIuint createShaderProgram(GAPIuint vertexShaderID, GAPIuint fragmentShaderID) = 0;
    
    virtual void destroyShaderProgram(GAPIuint shaderProgram) = 0;
    
    virtual bool linkOK(GAPIuint programID, GAPIchar *message) = 0;
    
    virtual void deleteShader(GAPIuint shaderID) = 0;
    
    
    // Uniforms
    virtual std::unique_ptr<UniformSetter>
    setUniform(GAPIuint program, const std::string &name) = 0;
    
};

