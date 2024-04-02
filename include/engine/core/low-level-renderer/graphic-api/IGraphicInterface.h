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


namespace GLESC::GAPI {
    class IGraphicInterface {
    public:
        IGraphicInterface() = default;

        virtual ~IGraphicInterface() = default;

        virtual Void preWindowCreationInit() = 0;

        virtual Void postWindowCreationInit() = 0;

        virtual Void clear(const std::initializer_list<Enums::ClearBits> &values) = 0;

        virtual Void clearColor(Float r, Float g, Float b, Float a) = 0;

        virtual Void setViewport(Int width, Int height) = 0;

        virtual Void setViewport(Int x, Int y, Int width, Int height) = 0;

        virtual Viewport getViewport() = 0;

        virtual Void swapBuffers(SDL_Window &window) = 0;

        virtual Void createContext(SDL_Window &window) = 0;

        virtual Void deleteContext() = 0;

        virtual Void drawTriangles(UInt start, UInt count) = 0;

        virtual Void drawTrianglesIndexed(UInt count) = 0;

        virtual Void drawTrianglesIndexedInstanced(UInt count, UInt instanceCount) = 0;

        virtual RGBAColor readPixelColor(int x, int y) = 0;

        virtual RGBAColorNormalized readPixelColorNormalized(UInt x, UInt y) = 0;


        // ------------------------------------------------------------------------------
        // -------------------------------- Buffers -------------------------------------

        virtual Void genBuffers(UInt amount, UInt &bufferID) = 0;

        virtual Void bindBuffer(Enums::BufferTypes bufferType, UInt buffer) = 0;

        virtual Void unbindBuffer(Enums::BufferTypes bufferType) = 0;

        virtual std::vector<float> getBufferDataF(UInt bufferId) = 0;

        virtual std::vector<unsigned int> getBufferDataUI(UInt bufferId) = 0;

        virtual std::vector<int> getBufferDataI(UInt bufferId) = 0;

        virtual Void deleteBuffer(UInt buffer) = 0;

        virtual Void setDynamicBufferData(UInt size, Enums::BufferTypes bufferType) = 0;

        virtual Void setIndexBufferData(const UInt *data, Size count, Enums::BufferUsages buferUsage) =
        0;

        virtual Void
        setBufferData(const Void *data,
                      Size count,
                      Size size,
                      Enums::BufferTypes bufferType,
                      Enums::BufferUsages bufferUsage) = 0;

        virtual Void genVertexArray(UInt &vertexArrayID) = 0;

        virtual Void setVertexAttribDivisor(UInt index, UInt divisor) = 0;

        virtual Void bindVertexArray(UInt vertexArrayID) = 0;

        virtual Void unbindVertexArray() = 0;

        virtual Void deleteVertexArray(UInt vertexArrayID) = 0;

        virtual Void enableVertexData(UInt index) = 0;

        virtual Void createVertexData(UInt vertexArray,
                                            UInt count,
                                            Enums::Types type,
                                            Bool isNormalized,
                                            UInt stride,
                                            UInt offset) = 0;

        // ------------------------------------------------------------------------------
        // -------------------------------- Texture -------------------------------------


        virtual TextureID createTexture(Enums::Texture::Filters::Min minFilter,
                                              Enums::Texture::Filters::Mag magFilter,
                                              Enums::Texture::Filters::WrapMode wrapS,
                                              Enums::Texture::Filters::WrapMode wrapT) = 0;

        virtual Void
        setTextureData(Int level,
                       UInt width,
                       UInt height,
                       Enums::Texture::CPUBufferFormat inputFormat,
                       Enums::Texture::BitDepth bitsPerPixel,
                       UByte *texelBuffer) = 0;

        [[nodiscard]] virtual std::vector<UByte> getTextureData(TextureID textureID) = 0;

        virtual Enums::Texture::GPUBufferFormat getTextureColorFormat(TextureID textureID) = 0;

        virtual UInt getTextureWidth(TextureID textureID) = 0;

        virtual UInt getTextureHeight(TextureID textureID) = 0;

        virtual Void bindTexture(TextureID textureID) = 0;

        virtual Void bindTextureOnSlot(TextureID textureID, UInt slot) = 0;

        virtual Void unbindTexture() = 0;

        virtual Void deleteTexture(TextureID textureID) = 0;

        // -------------------------------- Shaders -------------------------------------
        // ------------------------------------------------------------------------------
        virtual Void useShaderProgram(UInt shaderProgram) = 0;

        [[nodiscard]] virtual bool isShaderProgram(UInt shaderProgram) = 0;

        virtual Void deleteShaderProgram(UInt shaderProgram) = 0;

        virtual UInt
        loadAndCompileShader(Enums::ShaderTypes shaderType, const std::string &shaderSource) = 0;

        virtual bool compilationOK(UInt shaderID, Char *message) = 0;

        virtual UInt
        createShaderProgram(UInt vertexShaderID, UInt fragmentShaderID) = 0;

        virtual Void destroyShaderProgram(UInt shaderProgram) = 0;

        [[nodiscard]] virtual bool linkOK(UInt programID, Char *message) = 0;

        virtual Void deleteShader(UInt shaderID) = 0;


        // Uniforms
        virtual UniformSetter setUniform(const std::string &name) = 0;

        [[nodiscard]] virtual std::vector<std::string> getAllUniforms() const = 0;

    protected:
        [[nodiscard]] virtual Bool isTexture(UInt textureID) = 0;

        [[nodiscard]] virtual Bool isTextureBound(UInt textureID) = 0;

        [[nodiscard]] virtual Bool anyTextureBound() = 0;

        /**
         * @brief Check if the uniform location is cached
         * @param uName The name of the uniform
         * @return -1 if the uniform location is not cached, otherwise the uniform location
         */
        [[nodiscard]] virtual Int getUniformLocation(const std::string &uName) const = 0;

        std::set<TextureID> textureCache{};

        mutable std::unordered_map<std::string, UInt> uniformLocationsCache;

        TextureID boundTexture{};

        ShaderProgramID boundShaderProgram{};
    };
} // namespace GLESC
