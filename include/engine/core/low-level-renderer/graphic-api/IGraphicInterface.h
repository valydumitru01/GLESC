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
    
    virtual void clear(const std::initializer_list<GAPI::ClearBits> &values) = 0;
    
    virtual void clearColor(GAPI::Float r, GAPI::Float g, GAPI::Float b, GAPI::Float a) = 0;
    
    virtual void setViewport(GAPI::Int width, GAPI::Int height) = 0;
    
    virtual void setViewport(GAPI::Int x, GAPI::Int y, GAPI::Int width, GAPI::Int height) = 0;
    
    virtual std::tuple<GAPI::Int, GAPI::Int, GAPI::Int, GAPI::Int> getViewport() = 0;
    
    virtual void swapBuffers(SDL_Window &window) = 0;
    
    virtual void createContext(SDL_Window &window) = 0;
    
    virtual void deleteContext() = 0;
    
    virtual void drawTriangles(GAPI::UInt start, GAPI::UInt count) = 0;
    
    virtual void drawTrianglesIndexed(GAPI::UInt count) = 0;
    
    virtual RGBColor readPixelColor(int x, int y) = 0;
    
    virtual RGBColorNormalized readPixelColorNormalized(int x, int y) = 0;
    
    
    
    // ------------------------------------------------------------------------------
    // -------------------------------- Buffers -------------------------------------
    
    virtual void genBuffers(GAPI::UInt amount, GAPI::UInt &bufferID) = 0;
    
    virtual void bindBuffer(GAPI::BufferTypes bufferType, GAPI::UInt buffer) = 0;
    
    virtual void unbindBuffer(GAPI::BufferTypes bufferType) = 0;
    
    virtual std::vector<float> getBufferDataF(GLuint bufferId) = 0;
    
    virtual std::vector<unsigned int> getBufferDataUI(GLuint bufferId) = 0;
    
    virtual std::vector<int> getBufferDataI(GLuint bufferId) = 0;
    
    virtual void deleteBuffer(GAPI::UInt buffer) = 0;
    
    virtual void setBufferData(const GAPI::Float *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const GAPI::UInt *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const GAPI::Int *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const Vec2F *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const Vec3F *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const Vec4F *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const Mat2F *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const Mat3F *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    virtual void setBufferData(const Mat4F *data,
                               GAPI::Size count,
                               GAPI::BufferTypes bufferType,
                               GAPI::BufferUsages bufferUsage) = 0;
    
    
    virtual void genVertexArray(GAPI::UInt &vertexArrayID) = 0;
    
    virtual void bindVertexArray(GAPI::UInt vertexArrayID) = 0;
    
    virtual void unbindVertexArray() = 0;
    
    virtual void deleteVertexArray(GAPI::UInt vertexArrayID) = 0;
    
    virtual void enableVertexData(GAPI::UInt index) = 0;
    
    virtual void createVertexData(GAPI::UInt vertexArray,
                                  GAPI::UInt count,
                                  GAPI::Types type,
                                  GAPI::Bool isNormalized,
                                  GAPI::UInt stride,
                                  GAPI::UInt offset) = 0;
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
    virtual GAPI::UInt createTexture(SDL_Surface &surface,
                                     GAPI::TextureFilters::MinFilter minFilter,
                                     GAPI::TextureFilters::MagFilter magFilter,
                                     GAPI::TextureFilters::WrapMode wrapS,
                                     GAPI::TextureFilters::WrapMode wrapT) = 0;
    
    /**
     * @brief Create texture with default parameters
     * @details The default parameters are:
     * minFilter = LINEAR
     * magFilter = LINEAR
     * wrapS = REPEAT
     * wrapT = REPEAT
     * @param textureID
     */
    virtual GAPI::UInt createTexture(SDL_Surface &surface) = 0;
    
    virtual void bindTexture(GAPI::UInt textureID) = 0;
    
    virtual void deleteTexture(GAPI::UInt textureID) = 0;
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    virtual void useShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual bool isShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual GAPI::UInt
    loadAndCompileShader(GAPI::ShaderTypes shaderType, const std::string &shaderSource) = 0;
    
    virtual bool compilationOK(GAPI::UInt shaderID, GAPI::Char *message) = 0;
    
    virtual GAPI::UInt createShaderProgram(GAPI::UInt vertexShaderID, GAPI::UInt fragmentShaderID) = 0;
    
    virtual void destroyShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual bool linkOK(GAPI::UInt programID, GAPI::Char *message) = 0;
    
    virtual void deleteShader(GAPI::UInt shaderID) = 0;
    
    
    // Uniforms
    virtual std::unique_ptr<UniformSetter>
    setUniform(GAPI::UInt program, const std::string &name) = 0;
    
};

