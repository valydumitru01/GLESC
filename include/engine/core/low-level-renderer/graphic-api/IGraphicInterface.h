/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <SDL2/SDL.h>

#include "engine/core/low-level-renderer/graphic-api/GapiEnums.h"
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/core/low-level-renderer/graphic-api/IUniformSetter.h"

#ifdef GLESC_OPENGL
using UniformSetter = GLUniformSetter;
#endif

class IGraphicInterface {
public:
    IGraphicInterface() = default;
    
    virtual ~IGraphicInterface() = default;
    
    virtual void preWindowCreationInit() = 0;
    
    virtual void postWindowCreationInit() = 0;
    
    virtual void clear(const std::initializer_list<GAPI::ClearBits> &values) = 0;
    
    virtual void clearColor(GAPI::Float r, GAPI::Float g, GAPI::Float b, GAPI::Float a) = 0;
    
    virtual void setViewport(GAPI::Int width, GAPI::Int height) = 0;
    
    virtual void setViewport(GAPI::Int x, GAPI::Int y, GAPI::Int width, GAPI::Int height) = 0;
    
    virtual GAPI::Viewport getViewport() = 0;
    
    virtual void swapBuffers(SDL_Window &window) = 0;
    
    virtual void createContext(SDL_Window &window) = 0;
    
    virtual void deleteContext() = 0;
    
    virtual void drawTriangles(GAPI::UInt start, GAPI::UInt count) = 0;
    
    virtual void drawTrianglesIndexed(GAPI::UInt count) = 0;
    
    virtual GAPI::RGBColor readPixelColor(int x, int y) = 0;
    
    virtual GAPI::RGBColorNormalized readPixelColorNormalized(int x, int y) = 0;
    
    
    
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
    
    
    virtual GAPI::UInt createTexture(GAPI::Texture::Filters::Min minFilter,
                                     GAPI::Texture::Filters::Mag magFilter,
                                     GAPI::Texture::Filters::WrapMode wrapS,
                                     GAPI::Texture::Filters::WrapMode wrapT) = 0;
    
    virtual GAPI::Void
    setTextureData(GAPI::Int level, GAPI::UInt width, GAPI::UInt height, GAPI::UByte *texelBuffer) = 0;
    
    virtual void bindTexture(GAPI::UInt textureID) = 0;
    
    virtual GAPI::Void bindTextureOnSlot(GAPI::UInt textureID, GAPI::UInt slot) = 0;
    
    virtual GAPI::Void unbindTexture() = 0;
    
    virtual void deleteTexture(GAPI::UInt textureID) = 0;
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    virtual void useShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual bool isShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual GAPI::UInt
    loadAndCompileShader(GAPI::ShaderTypes shaderType, const std::string &shaderSource) = 0;
    
    virtual bool compilationOK(GAPI::UInt shaderID, GAPI::Char *message) = 0;
    
    virtual GAPI::UInt
    createShaderProgram(GAPI::UInt vertexShaderID, GAPI::UInt fragmentShaderID) = 0;
    
    virtual void destroyShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual bool linkOK(GAPI::UInt programID, GAPI::Char *message) = 0;
    
    virtual void deleteShader(GAPI::UInt shaderID) = 0;
    
    
    // Uniforms
    virtual std::unique_ptr<UniformSetter>
    setUniform(GAPI::UInt program, const std::string &name) = 0;
    
};

