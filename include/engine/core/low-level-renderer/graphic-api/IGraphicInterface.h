/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <unordered_map>
#include <set>
#include <SDL2/SDL.h>

#include "engine/core/low-level-renderer/graphic-api/GapiEnums.h"
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/core/low-level-renderer/graphic-api/IUniformSetter.h"


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
    
    virtual GAPI::RGBAColor readPixelColor(int x, int y) = 0;
    
    virtual GAPI::RGBAColorNormalized readPixelColorNormalized(GAPI::UInt x, GAPI::UInt y) = 0;
    
    
    
    // ------------------------------------------------------------------------------
    // -------------------------------- Buffers -------------------------------------
    
    virtual void genBuffers(GAPI::UInt amount, GAPI::UInt &bufferID) = 0;
    
    virtual void bindBuffer(GAPI::BufferTypes bufferType, GAPI::UInt buffer) = 0;
    
    virtual void unbindBuffer(GAPI::BufferTypes bufferType) = 0;
    
    virtual std::vector<float> getBufferDataF(GAPI::UInt bufferId) = 0;
    
    virtual std::vector<unsigned int> getBufferDataUI(GAPI::UInt bufferId) = 0;
    
    virtual std::vector<int> getBufferDataI(GAPI::UInt bufferId) = 0;
    
    virtual void deleteBuffer(GAPI::UInt buffer) = 0;
    
    virtual void allocateDynamicBuffer(GAPI::UInt size, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const GAPI::Float *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const GAPI::UInt *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const GAPI::Int *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const Vec2F *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const Vec3F *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const Vec4F *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const Mat2F *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const Mat3F *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    virtual void
    setBufferStaticData(const Mat4F *data, GAPI::Size count, GAPI::BufferTypes bufferType) = 0;
    
    
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
    
    
    virtual GAPI::TextureID createTexture(GAPI::Texture::Filters::Min minFilter,
                                     GAPI::Texture::Filters::Mag magFilter,
                                     GAPI::Texture::Filters::WrapMode wrapS,
                                     GAPI::Texture::Filters::WrapMode wrapT) = 0;
    
    virtual GAPI::Void
    setTextureData(GAPI::Int level,
                   GAPI::UInt width,
                   GAPI::UInt height,
                   GAPI::Texture::CPUBufferFormat inputFormat,
                   GAPI::Texture::BitDepth bitsPerPixel,
                   GAPI::UByte *texelBuffer) = 0;
    
    virtual std::vector<GAPI::UByte> getTextureData(GAPI::TextureID textureID) = 0;
    
    virtual GAPI::Texture::GPUBufferFormat getTextureColorFormat(GAPI::TextureID textureID) = 0;
    
    virtual GAPI::UInt getTextureWidth(GAPI::TextureID textureID) = 0;
    
    virtual GAPI::UInt getTextureHeight(GAPI::TextureID textureID) = 0;
    
    virtual void bindTexture(GAPI::TextureID textureID) = 0;
    
    virtual GAPI::Void bindTextureOnSlot(GAPI::TextureID textureID, GAPI::UInt slot) = 0;
    
    virtual GAPI::Void unbindTexture() = 0;
    
    virtual void deleteTexture(GAPI::TextureID textureID) = 0;
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    virtual void useShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual bool isShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual void deleteShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual GAPI::UInt
    loadAndCompileShader(GAPI::ShaderTypes shaderType, const std::string &shaderSource) = 0;
    
    virtual bool compilationOK(GAPI::UInt shaderID, GAPI::Char *message) = 0;
    
    virtual GAPI::UInt
    createShaderProgram(GAPI::UInt vertexShaderID, GAPI::UInt fragmentShaderID) = 0;
    
    virtual void destroyShaderProgram(GAPI::UInt shaderProgram) = 0;
    
    virtual bool linkOK(GAPI::UInt programID, GAPI::Char *message) = 0;
    
    virtual void deleteShader(GAPI::UInt shaderID) = 0;
    
    
    // Uniforms
    virtual UniformSetter setUniform(const std::string &name) = 0;

protected:
    virtual GAPI::Bool isTexture(GAPI::UInt textureID) = 0;
    
    virtual GAPI::Bool isTextureBound(GAPI::UInt textureID) = 0;
    
    virtual GAPI::Bool anyTextureBound() = 0;
    
    /**
     * @brief Check if the uniform location is cached
     * @param name
     * @return -1 if the uniform location is not cached, otherwise the uniform location
     */
    virtual GAPI::Int getUniformLocation(const std::string &uName) const = 0;
    
    std::set<GAPI::TextureID> textureCache{};
    
    mutable std::unordered_map<std::string, GAPI::UInt> uniformLocationsCache;
    
    GAPI::TextureID boundTexture{};
    
    GAPI::ShaderProgramID boundShaderProgram{};
    
    
};

