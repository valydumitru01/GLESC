/******************************************************************************
 * @file   IGraphicInterface.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
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

    virtual GAPI::Void preWindowCreationInit() = 0;

    virtual GAPI::Void postWindowCreationInit() = 0;

    virtual GAPI::Void clear(const std::initializer_list<GAPI::ClearBits>& values) = 0;

    virtual GAPI::Void clearColor(GAPI::Float r, GAPI::Float g, GAPI::Float b, GAPI::Float a) = 0;

    virtual GAPI::Void setViewport(GAPI::Int width, GAPI::Int height) = 0;

    virtual GAPI::Void setViewport(GAPI::Int x, GAPI::Int y, GAPI::Int width, GAPI::Int height) = 0;

    virtual GAPI::Viewport getViewport() = 0;

    virtual GAPI::Void swapBuffers(SDL_Window& window) = 0;

    virtual GAPI::Void createContext(SDL_Window& window) = 0;

    virtual GAPI::Void deleteContext() = 0;

    virtual GAPI::Void drawTriangles(GAPI::UInt start, GAPI::UInt count) = 0;

    virtual GAPI::Void drawTrianglesIndexed(GAPI::UInt count) = 0;

    virtual GAPI::Void drawTrianglesIndexedInstanced(GAPI::UInt count, GAPI::UInt instanceCount) = 0;

    virtual GAPI::RGBAColor readPixelColor(int x, int y) = 0;

    virtual GAPI::RGBAColorNormalized readPixelColorNormalized(GAPI::UInt x, GAPI::UInt y) = 0;


    // ------------------------------------------------------------------------------
    // -------------------------------- Buffers -------------------------------------

    virtual GAPI::Void genBuffers(GAPI::UInt amount, GAPI::UInt& bufferID) = 0;

    virtual GAPI::Void bindBuffer(GAPI::BufferTypes bufferType, GAPI::UInt buffer) = 0;

    virtual GAPI::Void unbindBuffer(GAPI::BufferTypes bufferType) = 0;

    virtual std::vector<float> getBufferDataF(GAPI::UInt bufferId) = 0;

    virtual std::vector<unsigned int> getBufferDataUI(GAPI::UInt bufferId) = 0;

    virtual std::vector<int> getBufferDataI(GAPI::UInt bufferId) = 0;

    virtual GAPI::Void deleteBuffer(GAPI::UInt buffer) = 0;

    virtual GAPI::Void setDynamicBufferData(GAPI::UInt size, GAPI::BufferTypes bufferType) = 0;

    virtual GAPI::Void setIndexBufferData(const GAPI::UInt* data, GAPI::Size count, GAPI::BufferUsages buferUsage) = 0;

    virtual GAPI::Void
    setBufferData(const GAPI::Void* data,
                  GAPI::Size count,
                  GAPI::Size size,
                  GAPI::BufferTypes bufferType,
                  GAPI::BufferUsages bufferUsage) = 0;

    virtual GAPI::Void genVertexArray(GAPI::UInt& vertexArrayID) = 0;

    virtual GAPI::Void setVertexAttribDivisor(GAPI::UInt index, GAPI::UInt divisor) = 0;

    virtual GAPI::Void bindVertexArray(GAPI::UInt vertexArrayID) = 0;

    virtual GAPI::Void unbindVertexArray() = 0;

    virtual GAPI::Void deleteVertexArray(GAPI::UInt vertexArrayID) = 0;

    virtual GAPI::Void enableVertexData(GAPI::UInt index) = 0;

    virtual GAPI::Void createVertexData(GAPI::UInt vertexArray,
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
                   GAPI::UByte* texelBuffer) = 0;

    [[nodiscard]] virtual std::vector<GAPI::UByte> getTextureData(GAPI::TextureID textureID) = 0;

    virtual GAPI::Texture::GPUBufferFormat getTextureColorFormat(GAPI::TextureID textureID) = 0;

    virtual GAPI::UInt getTextureWidth(GAPI::TextureID textureID) = 0;

    virtual GAPI::UInt getTextureHeight(GAPI::TextureID textureID) = 0;

    virtual GAPI::Void bindTexture(GAPI::TextureID textureID) = 0;

    virtual GAPI::Void bindTextureOnSlot(GAPI::TextureID textureID, GAPI::UInt slot) = 0;

    virtual GAPI::Void unbindTexture() = 0;

    virtual GAPI::Void deleteTexture(GAPI::TextureID textureID) = 0;

    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    virtual GAPI::Void useShaderProgram(GAPI::UInt shaderProgram) = 0;

    [[nodiscard]] virtual bool isShaderProgram(GAPI::UInt shaderProgram) = 0;

    virtual GAPI::Void deleteShaderProgram(GAPI::UInt shaderProgram) = 0;

    virtual GAPI::UInt
    loadAndCompileShader(GAPI::ShaderTypes shaderType, const std::string& shaderSource) = 0;

    virtual bool compilationOK(GAPI::UInt shaderID, GAPI::Char* message) = 0;

    virtual GAPI::UInt
    createShaderProgram(GAPI::UInt vertexShaderID, GAPI::UInt fragmentShaderID) = 0;

    virtual GAPI::Void destroyShaderProgram(GAPI::UInt shaderProgram) = 0;

    [[nodiscard]] virtual bool linkOK(GAPI::UInt programID, GAPI::Char* message) = 0;

    virtual GAPI::Void deleteShader(GAPI::UInt shaderID) = 0;


    // Uniforms
    virtual UniformSetter setUniform(const std::string& name) = 0;

    [[nodiscard]] virtual std::vector<std::string> getAllUniforms() const = 0;

protected:
    [[nodiscard]] virtual GAPI::Bool isTexture(GAPI::UInt textureID) = 0;

    [[nodiscard]] virtual GAPI::Bool isTextureBound(GAPI::UInt textureID) = 0;

    [[nodiscard]] virtual GAPI::Bool anyTextureBound() = 0;

    /**
     * @brief Check if the uniform location is cached
     * @param name
     * @return -1 if the uniform location is not cached, otherwise the uniform location
     */
    [[nodiscard]] virtual GAPI::Int getUniformLocation(const std::string& uName) const = 0;

    std::set<GAPI::TextureID> textureCache{};

    mutable std::unordered_map<std::string, GAPI::UInt> uniformLocationsCache;

    GAPI::TextureID boundTexture{};

    GAPI::ShaderProgramID boundShaderProgram{};
};

