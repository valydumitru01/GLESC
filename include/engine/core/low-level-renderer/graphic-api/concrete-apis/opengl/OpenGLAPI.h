/******************************************************************************
 * @file   OpenGLAPI.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief Implementation of the OpenGL graphics API.
 * @details This class provides an implementation for interfacing with the OpenGL graphics API.
 * It includes methods for managing OpenGL contexts, setting viewports, handling textures, buffers,
 * and shaders, and performing various rendering tasks. The class ensures that OpenGL functions
 * are called correctly and logs the operations for debugging purposes.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <GL/glew.h>
#include <functional>
#include <string>
#include <engine/core/low-level-renderer/graphic-api/debugger/GapiDebugger.h>

#include "engine/Config.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/low-level-renderer/asserts/GAPIAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/debugger/GAPIDebugger.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/debugger/OpenGLDebugger.h"
#include "engine/core/math/algebra/vector/Vector.h"

namespace GLESC::GAPI {
    class OpenGLAPI final : public IGraphicInterface {
    public:
        explicit OpenGLAPI() {
            D_ASSERT_GL_CORRECT_VERSION();
        }


        void deleteContext() override {
            GAPI_FUNCTION_NO_ARGS_LOG("deleteContext");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_DeleteContext", this->context);
            SDL_GL_DeleteContext(this->context);
        }

        void setViewport(Int width, Int height) override {
            this->setViewport(0, 0, width, height);
        }

        void setViewport(Int x, Int y, Int width, Int height) override {
            GAPI_FUNCTION_LOG("setViewport", x, y, width, height);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glViewport", x, y, width, height);
            glViewport(x, y, width, height);
        }

        Viewport getViewport() override {
            GAPI_FUNCTION_NO_ARGS_LOG("getViewport");
            Int viewport[4];
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetIntegerv", GL_VIEWPORT, viewport);
            glGetIntegerv(GL_VIEWPORT, viewport);
            return Viewport{viewport[0], viewport[1], viewport[2], viewport[3]};
        }


        void swapBuffers(SDL_Window& window) override {
            GAPI_FUNCTION_LOG("swapBuffers", "SDL_Window");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_SwapWindow", "SDL_Window");
            SDL_GL_SwapWindow(&window);
        }

        [[nodiscard]] SDL_GLContext getContext() const { return context; };

        void preWindowCreationInit() override {
            PRINT_GAPI_INIT("OpenGL", std::to_string(GLESC_GL_MAJOR_VERSION) + "." +
                            std::to_string(GLESC_GL_MINOR_VERSION));
            // Core functions of OpenGL a.k.a. full modern openGL functionality.
            // More info: https://wiki.libsdl.org/SDL_GLprofile
#ifdef GLESC_GLSL_CORE_PROFILE
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_PROFILE_MASK",
                                             SDL_GL_CONTEXT_PROFILE_CORE);
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_PROFILE_MASK",
                                             SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
#endif
            // We're using OpenGL Version 4.3 (released in 2012).
            // Changing this numbers will change some functions available of OpenGL.
            // Choosing a relatively old version of OpenGl allow most computers to use it.
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_MAJOR_VERSION",
                                             GLESC_GL_MAJOR_VERSION);
            setSDLGLAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GLESC_GL_MAJOR_VERSION);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_MINOR_VERSION",
                                             GLESC_GL_MINOR_VERSION);
            setSDLGLAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GLESC_GL_MINOR_VERSION);
            // Stencil size of 4 bits is used
            // Could be increased later if needed
            // Increases performance the lower it is, fewer data stored in each pixel
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_STENCIL_SIZE", 4);
            setSDLGLAttribute(SDL_GL_STENCIL_SIZE, 4);
            // Enable debug context
            // Possible performance loss
            GL_SET_DEBUG_CONTEXT_ATTRIBUTE();
        }

        void postWindowCreationInit() override {
            // Initialize GLEW, must be called before the following OpenGL calls
            initGLEW();

            Logger::get().success("Glew Initialized!");
            // Enable depth test
            // Fragments will be discarded if they are behind
            // More info: https://www.khronos.org/opengl/wiki/Depth_Test
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnable", GL_DEPTH_TEST);
            glEnable(GL_DEPTH_TEST);
            // Accept fragment if it closer to the camera than the former one
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDepthFunc", GL_LESS);
            glDepthFunc(GL_LESS);
            // Enable back face culling
            // Important for performance
            // More info: https://www.khronos.org/opengl/wiki/Face_Culling
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnable", GL_CULL_FACE);
            glEnable(GL_CULL_FACE);
            // Cull back faces (default)
            // Important for performance and to avoid self-shadowing
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCullFace", GL_BACK);
            glCullFace(GL_BACK);
            // Set the front face to be counter-clockwise (default)
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glFrontFace", GL_CCW);
            glFrontFace(GL_CCW);
            // Enable blending
            // Important for transparency and other effects
            // More info: https://www.khronos.org/opengl/wiki/Blending
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnable", GL_BLEND);
            glEnable(GL_BLEND);
            // Set blending function to alpha blending
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBlendFunc", GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // Set blending equation to add (default)
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBlendEquation", GL_FUNC_ADD);
            glBlendEquation(GL_FUNC_ADD);

            // Enable opengl debug callback
            // Improves debugging outputs
            GL_ENABLE_DEBUG_CALLBACK();

            // This makes our buffer swap synchronized with the monitor's vertical refresh
            // Parameters: 0 for immediate updates,
            // 1 for updates synchronized with the vertical retrace,
            // -1 for adaptive v-sync
            // More info: https://wiki.libsdl.org/SDL2/SDL_GL_SetSwapInterval
            //GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_SetSwapInterval", 1);
            //if (SDL_GL_SetSwapInterval(1) == -1)
            //    throw EngineException(std::string("Unable activate v-sync (swap interval): ") +
            //        std::string(SDL_GetError()));
        }

        void enableDepthBuffer(Bool enabled) override {
            GAPI_FUNCTION_NO_ARGS_LOG("enableDepthBuffer");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnable", GL_DEPTH_TEST);
            glDepthMask(static_cast<GLboolean>(enabled));
        }

        void setDepthFunction(Enums::DepthFuncs depthFunction) override {
            GAPI_FUNCTION_LOG("setDepthFunction", depthFunction);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDepthFunc", depthFunction);
            glDepthFunc(static_cast<GLenum>(depthFunction));
        }

        void drawTriangles(UInt start, UInt count) override {
            GAPI_FUNCTION_LOG("drawTriangles", start, count);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDrawArrays", GL_TRIANGLES, start, count);
            glDrawArrays(static_cast<GLenum>(Enums::PrimitiveTypes::Triangles), start, count);
        }

        void drawTrianglesIndexed(UInt indicesCount) override {
            GAPI_FUNCTION_LOG("drawTrianglesIndexed", indicesCount);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDrawElements", GL_TRIANGLES, indicesCount,
                                             GL_UNSIGNED_INT, nullptr);
            glDrawElements(static_cast<GLenum>(Enums::PrimitiveTypes::Triangles),
                           indicesCount,
                           static_cast<GLenum>(Enums::Types::UInt),
                           nullptr);
        }

        void drawTrianglesIndexedInstanced(UInt indicesCount, UInt instanceCount) override {
            GAPI_FUNCTION_LOG("drawTrianglesIndexedInstanced", indicesCount, instanceCount);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDrawElementsInstanced", GL_TRIANGLES, indicesCount,
                                             GL_UNSIGNED_INT, nullptr, instanceCount);
            glDrawElementsInstanced(static_cast<GLenum>(Enums::PrimitiveTypes::Triangles),
                                    static_cast<int>(indicesCount),
                                    static_cast<GLenum>(Enums::Types::UInt),
                                    nullptr,
                                    static_cast<int>(instanceCount));
        }


        RGBAColor readPixelColor(int x, int y) override {
            GAPI_FUNCTION_LOG("readPixelColor", x, y);
            RGBAColor color;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_UNSIGNED_BYTE, color.r, color.g, color.b, color.a);
            glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_UNSIGNED_BYTE, color.r, color.g, color.b, color.a);
            return color;
        }

        RGBAColorNormalized readPixelColorNormalized(UInt x, UInt y) override {
            GAPI_FUNCTION_LOG("readPixelColorNormalized", x, y);
            RGBAColorNormalized color{};
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_FLOAT, color.r, color.g, color.b, color.a);
            glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, &color);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_UNSIGNED_BYTE, color.r, color.g, color.b, color.a);
            return color;
        }

        // -------------------------------------------------------------------------
        // ------------------------------ Texture ----------------------------------

        [[nodiscard]] TextureID createTexture(Enums::Texture::Types textureType,
                                              Enums::Texture::Filters::Min minFilter,
                                              Enums::Texture::Filters::Mag magFilter,
                                              Enums::Texture::Filters::WrapMode wrapS,
                                              Enums::Texture::Filters::WrapMode wrapT,
                                              Enums::Texture::Filters::WrapMode wrapR =
                                                  Enums::Texture::Filters::WrapMode::ClampToEdge) override {
            GAPI_FUNCTION_LOG("createTexture", "SDL_Surface", minFilter, magFilter, wrapS, wrapT);

            auto textureTypeGL = static_cast<GLint>(textureType);
            auto minFilterGL = static_cast<GLint>(minFilter);
            auto magFilterGL = static_cast<GLint>(magFilter);
            auto wrapSGL = static_cast<GLint>(wrapS);
            auto wrapTGL = static_cast<GLint>(wrapT);
            auto wrapRGL = static_cast<GLint>(wrapR);

            int numTextures = 1;
            TextureID textureID = 0;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGenTextures", numTextures, &textureID);
            glGenTextures(numTextures, &textureID);
            textureCache.insert(textureID);
            this->bindTexture(textureID, textureType);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", textureTypeGL,
                                             GL_TEXTURE_MIN_FILTER,
                                             minFilterGL);
            glTexParameteri(textureTypeGL, GL_TEXTURE_MIN_FILTER, minFilterGL);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", textureTypeGL,
                                             GL_TEXTURE_MAG_FILTER,
                                             magFilterGL);
            glTexParameteri(textureTypeGL, GL_TEXTURE_MAG_FILTER, magFilterGL);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", textureTypeGL,
                                             GL_TEXTURE_WRAP_S,
                                             wrapSGL);
            glTexParameteri(textureTypeGL, GL_TEXTURE_WRAP_S, wrapSGL);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", textureTypeGL,
                                             GL_TEXTURE_WRAP_T,
                                             wrapTGL);
            glTexParameteri(textureTypeGL, GL_TEXTURE_WRAP_T, wrapTGL);

            if (textureType != Enums::Texture::Types::Texture2D) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", textureTypeGL,
                                                 GL_TEXTURE_WRAP_R,
                                                 wrapTGL);
                glTexParameteri(textureTypeGL, GL_TEXTURE_WRAP_R, wrapRGL);
            }

            return textureID;
        }

        void deleteTexture(TextureID textureID) override {
            GAPI_FUNCTION_LOG("deleteTexture", textureID);

            D_ASSERT_TRUE(isTexture(textureID), "Bound object is not a texture.");

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteTextures", textureID);
            glDeleteTextures(1, &textureID);

            this->textureCache.erase(textureID);
        }

        Void setTextureData(Enums::Texture::Types textureType,
                            Int level,
                            UInt width,
                            UInt height,
                            Enums::Texture::CPUBufferFormat inputFormat,
                            Enums::Texture::BitDepth bitsPerPixel,
                            const UByte* texelBuffer) override {
            GAPI_FUNCTION_LOG("setTextureData", level, height, width, "texelBuffer");
            D_ASSERT_TRUE(anyTextureBound(), "No texture bound.");

            GLenum GLinternalFormat;
            auto inputFormatGL = static_cast<GLenum>(inputFormat);
            auto textureTypeGL = static_cast<GLenum>(textureType);
            GLuint padding;



            if (inputFormat == Enums::Texture::CPUBufferFormat::RGB &&
                bitsPerPixel == Enums::Texture::BitDepth::Bit24) {
                GLinternalFormat = GL_RGB8;
                padding = 1;
            }
            else if (inputFormat == Enums::Texture::CPUBufferFormat::RGBA &&
                bitsPerPixel == Enums::Texture::BitDepth::Bit32) {
                GLinternalFormat = GL_RGBA8;
                padding = 4;
            }
            else
                D_ASSERT_FALSE(true, "Invalid texture format.");

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glPixelStorei", GL_UNPACK_ALIGNMENT, padding);
            glPixelStorei(GL_UNPACK_ALIGNMENT, padding);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexImage2D", textureTypeGL, level, GLinternalFormat,
                                             width, height, 0, inputFormatGL,
                                             GL_UNSIGNED_BYTE, texelBuffer);
            glTexImage2D(textureTypeGL, level, GLinternalFormat, width, height, 0, inputFormatGL,
                         GL_UNSIGNED_BYTE, texelBuffer);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glPixelStorei", GL_UNPACK_ALIGNMENT, 4);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Reset to default
        }

        Enums::Texture::GPUBufferFormat getTextureColorFormat(TextureID textureID) override {
            GAPI_FUNCTION_LOG("getTextureColorFormat", textureID);
            D_ASSERT_TRUE(isTexture(textureID), "Passed object is not a texture.");
            D_ASSERT_TRUE(isTextureBound(textureID), "Passed texture is not bound.");

            GLint internalFormat;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetTexLevelParameteriv", GL_TEXTURE_2D, 0,
                                             GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);


            Enums::Texture::GPUBufferFormat externalFormatEnum =
                static_cast<Enums::Texture::GPUBufferFormat>(internalFormat);
            Logger::get().info("\t\tInternal format: " + Enums::toString(externalFormatEnum));
            return externalFormatEnum;
        }

        UInt getTextureHeight(TextureID textureID) override {
            GAPI_FUNCTION_LOG("getTextureHeight", textureID);
            D_ASSERT_TRUE(isTexture(textureID), "Passed object is not a texture.");
            D_ASSERT_TRUE(isTextureBound(textureID), "Passed texture is not bound.");

            GLint textureHeight;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetTexLevelParameteriv", GL_TEXTURE_2D, 0,
                                             GL_TEXTURE_HEIGHT, &textureHeight);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);


            D_ASSERT_TRUE(textureHeight > 0, "Invalid texture height.");
            return static_cast<UInt>(textureHeight);
        }

        UInt getTextureWidth(TextureID textureID) override {
            GAPI_FUNCTION_LOG("getTextureWidth", textureID);
            D_ASSERT_TRUE(isTexture(textureID), "Passed object is not a texture.");
            D_ASSERT_TRUE(isTextureBound(textureID), "Passed texture is not bound.");

            GLint textureWidth;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetTexLevelParameteriv", GL_TEXTURE_2D, 0,
                                             GL_TEXTURE_WIDTH, &textureWidth);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);


            D_ASSERT_TRUE(textureWidth > 0, "Invalid texture width.");
            return static_cast<UInt>(textureWidth);
        }

        std::vector<UByte> getTextureData(TextureID textureID,
                                          Enums::Texture::Types textureType) override {
            GAPI_FUNCTION_LOG("getTextureData", textureID);
            D_ASSERT_TRUE(isTexture(textureID), "Object is not a texture");
            D_ASSERT_TRUE(isTextureBound(textureID), "Passed texture is not bound.");

            bindTexture(textureID, textureType);

            GLint textureWidth = getTextureWidth(textureID);
            GLint textureHeight = getTextureHeight(textureID);
            Enums::Texture::GPUBufferFormat internalBufferFormat = getTextureColorFormat(textureID);


            size_t numBytes;
            GLuint padding;
            Enums::Texture::CPUBufferFormat extractedFormat;
            if (internalBufferFormat == Enums::Texture::GPUBufferFormat::RGB ||
                internalBufferFormat == Enums::Texture::GPUBufferFormat::RGB8) {
                numBytes = textureWidth * textureHeight * 3;
                extractedFormat = Enums::Texture::CPUBufferFormat::RGB;
                padding = 1;
            }
            else if (internalBufferFormat == Enums::Texture::GPUBufferFormat::RGBA ||
                internalBufferFormat == Enums::Texture::GPUBufferFormat::RGBA8) {
                numBytes = textureWidth * textureHeight * 4;
                extractedFormat = Enums::Texture::CPUBufferFormat::RGBA;
                padding = 4;
            }
            else
                D_ASSERT_FALSE(true, "Invalid texture format.");

            std::vector<UByte> data(numBytes);
            auto extractedFormatGL = static_cast<GLenum>(extractedFormat);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glPixelStorei", GL_PACK_ALIGNMENT, padding);
            glPixelStorei(GL_PACK_ALIGNMENT, padding);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetTexImage", GL_TEXTURE_2D, 0, extractedFormatGL,
                                             GL_UNSIGNED_BYTE, "data.data()");
            glGetTexImage(GL_TEXTURE_2D, 0, extractedFormatGL, GL_UNSIGNED_BYTE, data.data());

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glPixelStorei", GL_PACK_ALIGNMENT, 4);
            glPixelStorei(GL_PACK_ALIGNMENT, 4); // Reset to default
            return data;
        }


        Void bindTexture(TextureID textureID, Enums::Texture::Types textureType) override {
            GAPI_FUNCTION_LOG("bindTexture", textureID);
            D_ASSERT_TRUE(isTexture(textureID), "Object is not a texture");

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindTexture", GL_TEXTURE_2D, textureID);
            glBindTexture(static_cast<GLenum>(textureType), textureID);

            boundTexture = textureID;
        }

        Void bindTextureOnSlot(TextureID textureID, Enums::Texture::Types textureType, UInt slot) override {
            GAPI_FUNCTION_LOG("bindTextureOnSlot", textureID, slot);
            D_ASSERT_TRUE(isTexture(textureID), "Object is not a texture");

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glActiveTexture", GL_TEXTURE0 + slot);
            glActiveTexture(GL_TEXTURE0 + slot);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindTexture", GL_TEXTURE_2D, textureID);

            bindTexture(textureID, textureType);
        }

        Void unbindTexture(Enums::Texture::Types textureType) override {
            GAPI_FUNCTION_NO_ARGS_LOG("unbindTexture");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindTexture", GL_TEXTURE_2D, 0);
            glBindTexture(GL_TEXTURE_2D, 0);

            boundTexture = 0;
        }


        // -------------------------------------------------------------------------
        // ------------------------------ Buffers ----------------------------------
        Bool isBuffer(UInt bufferID) override {
            GAPI_FUNCTION_LOG("isBuffer", bufferID);
            return glIsBuffer(bufferID) ? Bool::True : Bool::False;
        }

        void genBuffers(UInt amount, UInt& bufferID) override {
            GAPI_FUNCTION_LOG("genBuffers", amount);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGenBuffers", amount, &bufferID);
            glGenBuffers(static_cast<int>(amount), &bufferID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glGenBuffers", amount, &bufferID);
        }

        void bindBuffer(Enums::BufferTypes bufferType, UInt buffer) override {
            GAPI_FUNCTION_LOG("bindBuffer", bufferType, buffer);
            auto bufferTypeGL = static_cast<GLenum>(bufferType);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", bufferTypeGL, buffer);
            glBindBuffer(bufferTypeGL, buffer);
        }

        void unbindBuffer(Enums::BufferTypes bufferType) override {
            GAPI_FUNCTION_LOG("unbindBuffer", bufferType);
            auto bufferTypeGL = static_cast<GLenum>(bufferType);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", bufferTypeGL, 0);
            glBindBuffer(bufferTypeGL, 0);
        }

        void deleteBuffer(UInt& buffer) override {
            GAPI_FUNCTION_LOG("deleteBuffer", buffer);
            //D_ASSERT_EQUAL(this->isBuffer(buffer), Bool::True, "Bound object is not a buffer");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteBuffers", 1, &buffer);
            glDeleteBuffers(1, &buffer);
        }

        void setDynamicBufferData(UInt size, Enums::BufferTypes bufferType) override {
            GAPI_FUNCTION_LOG("allocateDynamicBuffer", size, bufferType);
            auto bufferTypeGL = static_cast<GLenum>(bufferType);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBufferData", bufferTypeGL, size, nullptr);
            glBufferData(bufferTypeGL, size, nullptr, GL_DYNAMIC_DRAW);
        }

        void setIndexBufferData(const UInt* data, Size count, Enums::BufferUsages buferUsage) override {
            GAPI_FUNCTION_LOG("setIndexBufferData", "vectorData (is a pointer,can't be printed)",
                              count);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBufferData", data, count, sizeof(UInt),
                                             Enums::BufferTypes::Index, buferUsage);
            setBufferData(data, count, sizeof(UInt), Enums::BufferTypes::Index, buferUsage);
        }

        void setBufferData(const Void* data,
                           Size elementCount,
                           Size elementSize,
                           Enums::BufferTypes bufferType,
                           Enums::BufferUsages bufferUsage) override {
            GAPI_FUNCTION_LOG("setBufferStaticData", "vectorData (is a pointer,can't be printed)",
                              elementCount, elementSize, bufferType, bufferUsage);
            // Only uncomment for debugging purposes, it will print the buffer data
            // It's VERY slow
            //if (bufferType == Enums::BufferTypes::Index)
            //    GAPI_PRINT_BUFFER_DATA(UInt, data, elementCount*elementSize);
            //else
            //    GAPI_PRINT_BUFFER_DATA(Float, data, elementCount*elementSize);
            auto type = static_cast<GLenum>(bufferType);
            auto usage = static_cast<GLenum>(bufferUsage);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBufferData", type, elementCount * elementSize, data, usage);
            glBufferData(type, elementCount * elementSize, data, usage);
        }


        std::vector<float> getBufferDataF(UInt bufferId) override {
            GAPI_FUNCTION_LOG("getBufferDataF", bufferId);
            return getBufferDataGL<float>(bufferId);
        }

        std::vector<unsigned int> getBufferDataUI(UInt bufferId) override {
            GAPI_FUNCTION_LOG("getBufferDataUI", bufferId);
            return getBufferDataGL<unsigned int>(bufferId);
        }

        std::vector<int> getBufferDataI(UInt bufferId) override {
            GAPI_FUNCTION_LOG("getBufferDataI", bufferId);
            return getBufferDataGL<int>(bufferId);
        }

        template <typename T>
        std::vector<T> getBufferDataGL(GLuint bufferId) {
            GAPI_FUNCTION_LOG("getBufferDataGL", bufferId);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", GL_ARRAY_BUFFER, bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, bufferId);

            GLint sizeBytes = 0;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetBufferParameteriv", GL_ARRAY_BUFFER,
                                             GL_BUFFER_SIZE, &sizeBytes);
            glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &sizeBytes);


            D_ASSERT_GREATER(sizeBytes, 0, "Invalid buffer size.");

            auto numElements = sizeBytes / sizeof(T);
            std::vector<T> data(numElements);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetBufferSubData", GL_ARRAY_BUFFER, 0, sizeBytes);
            glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeBytes, data.data());
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glGetBufferSubData", data);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);


            return data;
        }

        void genVertexArray(UInt& vertexArrayID) override {
            GAPI_FUNCTION_LOG("genVertexArray", vertexArrayID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGenVertexArrays", 1, &vertexArrayID);
            glGenVertexArrays(1, &vertexArrayID);
        };


        void setVertexAttribDivisor(UInt index, UInt divisor) override {
            GAPI_FUNCTION_LOG("setVertexAttribDivisor", index, divisor);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glVertexAttribDivisor", index, divisor);
            glVertexAttribDivisor(index, divisor);
        }

        void bindVertexArray(UInt vertexArrayID) override {
            GAPI_FUNCTION_LOG("bindVertexArray", vertexArrayID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindVertexArray", vertexArrayID);
            glBindVertexArray(vertexArrayID);
        }

        void unbindVertexArray() override {
            GAPI_FUNCTION_NO_ARGS_LOG("unbindVertexArray");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindVertexArray", 0);
            glBindVertexArray(0);
        }

        void deleteVertexArray(UInt& vertexArrayID) override {
            GAPI_FUNCTION_LOG("deleteVertexArray", vertexArrayID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteVertexArrays", 1, &vertexArrayID);
            glDeleteVertexArrays(1, &vertexArrayID);
        }

        /**
         * @brief Enables the vertex data.
         *
         * @details This method enables the generic vertex attribute array specified by the index.
         *
         * @param index The index of the vertex attribute to be enabled.
         */
        void enableVertexData(UInt index) override {
            GAPI_FUNCTION_LOG("enableVertexData", index);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnableVertexAttribArray", index);
            glEnableVertexAttribArray(index);
        }


        /**
         * @brief Configures the layout of the vertex data.
         *
         * This method sets up how OpenGL interprets the vertex buffer data.
         * It is used to specify the location and data format of the array of generic vertex
         * attributes.
         *
         * @param index The index of the vertex attribute to be modified.
         * @param count The number of components per generic vertex attribute.
         *              Typically, this is 1, 2, 3, or 4.
         * @param type The data type of each component in the array.
         *             For example, GL_FLOAT, GL_INT, etc.
         * @param isNormalized Specifies whether fixed-point data values should be normalized or
         *                     converted directly as fixed-point values when they are accessed.
         * @param stride The byte offset between consecutive vertex attributes.
         *               If the attributes are tightly packed, this value is 0.
         * @param offset The offset of the first component of the first vertex attribute in the
         *               buffer.
         *               This is usually a byte offset.
         */
        void createVertexData(UInt index,
                              UInt count,
                              Enums::Types type,
                              Bool isNormalized,
                              UInt stride,
                              UInt offset) override {
            GAPI_FUNCTION_LOG("createVertexData", index, count, type, isNormalized, stride,
                              offset);

            auto glType = static_cast<GLenum>(type);
            auto glNormalized = static_cast<GLboolean>(isNormalized);
            // Calls glVertexAttribPointer to define an array of generic vertex attribute data.
            // The parameters are set according to the function arguments, allowing for flexible
            // configuration of vertex data.
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glVertexAttribPointer",
                                             index,
                                             count,
                                             glType,
                                             glNormalized,
                                             stride,
                                             offset);

            glVertexAttribPointer(index, // Specifies the index of the generic vertex attribute.
                                  static_cast<int>(count), // Number of components per generic vertex attribute.
                                  glType, // Converts the GAPITypes enum to GLenum.
                                  glNormalized, // Specifies whether to normalize the data.
                                  static_cast<int>(stride), // Byte offset between consecutive vertex attributes.
                                  reinterpret_cast<GLvoid*>(offset)); // Offset of the first component in the buffer.
        }


        // ---------------------------- Shader functions --------------------------------
        // ------------------------------------------------------------------------------


        UInt
        loadAndCompileShader(Enums::ShaderTypes shaderType,
                             const std::string& shaderSource) override {
            GAPI_FUNCTION_LOG("loadAndCompileShader", shaderType, shaderSource);
            auto shaderTypeGL = static_cast<GLenum>(shaderType);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCreateShader", shaderTypeGL);
            GLuint vertexShader = glCreateShader(shaderTypeGL);
            const Char* source = shaderSource.c_str();

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glShaderSource", vertexShader, 1, &source, nullptr);
            glShaderSource(vertexShader, 1, &source, nullptr);

            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCompileShader", vertexShader);
            glCompileShader(vertexShader);

            return vertexShader;
        }


        UInt
        createShaderProgram(UInt vertexShaderID, UInt fragmentShaderID) override {
            GAPI_FUNCTION_LOG("createShaderProgram", vertexShaderID, fragmentShaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCreateProgram", 0);
            GLuint shaderProgram = glCreateProgram();
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glAttachShader", shaderProgram, vertexShaderID);
            glAttachShader(shaderProgram, vertexShaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glAttachShader", shaderProgram, fragmentShaderID);
            glAttachShader(shaderProgram, fragmentShaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glLinkProgram", shaderProgram);
            glLinkProgram(shaderProgram);

            return shaderProgram;
        }

        void destroyShaderProgram(UInt shaderProgram) {
            GAPI_FUNCTION_LOG("destroyShaderProgram", shaderProgram);
            glDeleteProgram(shaderProgram);
        }

        [[nodiscard]] bool compilationOK(UInt shaderID, Char* message) override {
            GAPI_FUNCTION_LOG("compilationOK", shaderID, message);
            GLint success;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetShaderiv", shaderID, GL_COMPILE_STATUS,
                                             &success);
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetShaderInfoLog", shaderID, 512, nullptr,
                                                 message);
                glGetShaderInfoLog(shaderID, 512, nullptr, message);
                return false;
            }
            return true;
        }

        [[nodiscard]] bool linkOK(UInt shaderProgram, Char* message) override {
            GAPI_FUNCTION_LOG("linkOK", shaderProgram, message);
            GLint success;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetProgramiv", shaderProgram, GL_LINK_STATUS,
                                             &success);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetProgramInfoLog", shaderProgram, 512,
                                                 nullptr, message);
                glGetProgramInfoLog(shaderProgram, 512, nullptr, message);
                return false;
            }
            return true;
        }

        void useShaderProgram(UInt shaderProgram) override {
            GAPI_FUNCTION_LOG("useShaderProgram", shaderProgram);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUseProgram", shaderProgram);
            glUseProgram(shaderProgram);
            boundShaderProgram = shaderProgram;
        }

        /**
         * @brief Checks if the given shader program is a shader program.
         * @param shaderProgram The shader program ID
         * @return true if the given shader program is a shader program, false otherwise.
         */
        bool isShaderProgram(UInt shaderProgram) override {
            GAPI_FUNCTION_LOG("isShaderProgram", shaderProgram);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glIsProgram", shaderProgram);
            // TODO: Cache shader programs instead of calling glIsProgram every time.
            return glIsProgram(shaderProgram);
        }

        void deleteShaderProgram(UInt shaderProgram) override {
            GAPI_FUNCTION_LOG("deleteShaderProgram", shaderProgram);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteProgram", shaderProgram);
            glDeleteProgram(shaderProgram);
        }

        void deleteShader(UInt shaderID) override {
            GAPI_FUNCTION_LOG("deleteShader", shaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteShader", shaderID);
            glDeleteShader(shaderID);
        }

        // -------------------------------- Uniforms ------------------------------------

        template <typename Type>
        static void setUniform(Int location, Type value) {
            GAPI_FUNCTION_LOG("setUniformValue", location, value);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1i", location, value);
            // Floats
            if constexpr (std::is_floating_point_v<Type>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1f", location, value);
                glUniform1f(location, value);
            }
            else if constexpr (std::is_same_v<Type, Vec2F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2f", location, value.x(), value.y());
                glUniform2f(location, value.x(), value.y());
            }
            else if constexpr (std::is_same_v<Type, Vec3F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3f", location, value.x(), value.y(), value.z());
                glUniform3f(location, value.x(), value.y(), value.z());
            }
            else if constexpr (std::is_same_v<Type, Vec4F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4f", location, value.x(), value.y(), value.z(),
                                                 value.w());
                glUniform4f(location, value.x(), value.y(), value.z(), value.w());
            }
            else if constexpr (std::is_same_v<Type, Mat2F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix2fv", location, 1, GL_TRUE,
                                                 &value[0][0]);
                glUniformMatrix2fv(location, 1, rowMajorMatrix, &value[0][0]);
            }
            else if constexpr (std::is_same_v<Type, Mat3F>) {
                glUniformMatrix3fv(location, 1, rowMajorMatrix, &value[0][0]);
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix3fv", location, 1, GL_TRUE,
                                                 &value[0][0]);
            }
            else if constexpr (std::is_same_v<Type, Mat4F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix4fv", location, 1, GL_TRUE,
                                                 &value[0][0]);
                glUniformMatrix4fv(location, 1, rowMajorMatrix, &value[0][0]);
            }
            // Integers
            else if constexpr (std::is_same_v<Type, Int>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1i", location, value);
                glUniform1i(location, value);
            }
            else if constexpr (std::is_same_v<Type, Vec2I>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, value.x(), value.y());
                glUniform2i(location, value.x(), value.y());
            }
            else if constexpr (std::is_same_v<Type, Vec3I>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, value.x(), value.y(), value.z());
                glUniform3i(location, value.x(), value.y(), value.z());
            }
            else if constexpr (std::is_same_v<Type, Vec4I>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, value.x(), value.y(), value.z(),
                                                 value.w());
                glUniform4i(location, value.x(), value.y(), value.z(), value.w());
            }
            // Unsigned Integers
            else if constexpr (std::is_unsigned_v<Type>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1ui", location, value);
                glUniform1ui(location, value);
            }
            else if constexpr (std::is_same_v<Type, Vec2UI>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2ui", location, value.x(), value.y());
                glUniform2ui(location, value.x(), value.y());
            }
            else if constexpr (std::is_same_v<Type, Vec3UI>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3ui", location, value.x(), value.y(), value.z());
                glUniform3ui(location, value.x(), value.y(), value.z());
            }
            else if constexpr (std::is_same_v<Type, Vec4UI>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4ui", location, value.x(), value.y(), value.z(),
                                                 value.w());
                glUniform4ui(location, value.x(), value.y(), value.z(), value.w());
            }
            // Boolean
            else if constexpr (std::is_same_v<Type, Bool>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1i", location, value);
                glUniform1i(location, value);
            }
            else if constexpr (std::is_same_v<Type, Vec2B>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, value.x(), value.y());
                glUniform2i(location, value.x(), value.y());
            }
            else if constexpr (std::is_same_v<Type, Vec3B>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, value.x(), value.y(), value.z());
                glUniform3i(location, value.x(), value.y(), value.z());
            }
            else if constexpr (std::is_same_v<Type, Vec4B>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, value.x(), value.y(), value.z(),
                                                 value.w());
                glUniform4i(location, value.x(), value.y(), value.z(), value.w());
            }
        }

        template <typename Type>
        auto getUniformValue(Int location) {
            GAPI_FUNCTION_LOG("getUniformValue", location);
            Type value{};
            // Floats
            if constexpr (std::is_floating_point_v<Type>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformfv", boundShaderProgram, location,
                                                 &value);
                glGetUniformfv(boundShaderProgram, location, &value);
            }
            else if constexpr (std::is_same_v<Type, Vec2F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformfv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformfv(boundShaderProgram, location, value.data.data());
            }
            else if constexpr (std::is_same_v<Type, Vec3F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformfv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformfv(boundShaderProgram, location, value.data.data());
            }
            else if constexpr (std::is_same_v<Type, Vec4F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformfv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformfv(boundShaderProgram, location, value.data.data());
            }
            else if constexpr (std::is_same_v<Type, Mat2F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformfv", boundShaderProgram, location,
                                                 &value[0][0]);
                glGetUniformfv(boundShaderProgram, location, &value[0][0]);
                if constexpr (rowMajorMatrix) {
                    value = value.transpose();
                }
            }
            else if constexpr (std::is_same_v<Type, Mat3F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformfv", boundShaderProgram, location,
                                                 &value[0][0]);
                glGetUniformfv(boundShaderProgram, location, &value[0][0]);
                if constexpr (rowMajorMatrix) {
                    value = value.transpose();
                }
            }
            else if constexpr (std::is_same_v<Type, Mat4F>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformfv", boundShaderProgram, location,
                                                 &value[0][0]);
                glGetUniformfv(boundShaderProgram, location, &value[0][0]);
                if constexpr (rowMajorMatrix) {
                    value = value.transpose();
                }
            }
            // Integers
            else if constexpr (std::is_same_v<Type, Int>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 &value);
                glGetUniformiv(boundShaderProgram, location, &value);
            }
            else if constexpr (std::is_same_v<Type, Vec2I>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformiv(boundShaderProgram, location, value.data.data());
            }
            else if constexpr (std::is_same_v<Type, Vec3I>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformiv(boundShaderProgram, location, value.data.data());
            }
            else if constexpr (std::is_same_v<Type, Vec4I>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformiv(boundShaderProgram, location, value.data.data());
            }
            // Unsigned Integers
            else if constexpr (std::is_unsigned_v<Type>) {
                unsigned int temp = static_cast<unsigned int>(value);
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformuiv", boundShaderProgram, location,
                                                 &value);
                glGetUniformuiv(boundShaderProgram, location, &temp);
                value = static_cast<Type>(temp);
            }
            else if constexpr (std::is_same_v<Type, Vec2UI>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformuiv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformuiv(boundShaderProgram, location, value.data.data());
            }
            else if constexpr (std::is_same_v<Type, Vec3UI>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformuiv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformuiv(boundShaderProgram, location, value.data.data());
            }
            else if constexpr (std::is_same_v<Type, Vec4UI>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformuiv", boundShaderProgram, location,
                                                 value.data.data());
                glGetUniformuiv(boundShaderProgram, location, value.data.data());
            }
            // Boolean
            else if constexpr (std::is_same_v<Type, Bool>) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 &value);
                glGetUniformiv(boundShaderProgram, location, &value);
                return static_cast<bool>(value);
            }
            else if constexpr (std::is_same_v<Type, Vec2B>) {
                Vec2I temp;
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 temp.data.data());
                glGetUniformiv(boundShaderProgram, location, temp.data.data());
                value.x() = static_cast<bool>(temp.x());
                value.y() = static_cast<bool>(temp.y());
            }
            else if constexpr (std::is_same_v<Type, Vec3B>) {
                Vec3I temp;
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 temp.data.data());
                glGetUniformiv(boundShaderProgram, location, temp.data.data());
                value.x() = static_cast<bool>(temp.x());
                value.y() = static_cast<bool>(temp.y());
                value.z() = static_cast<bool>(temp.z());
            }
            else if constexpr (std::is_same_v<Type, Vec4B>) {
                Vec4I temp;
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformiv", boundShaderProgram, location,
                                                 temp.data.data());
                glGetUniformiv(boundShaderProgram, location, temp.data.data());
                value.x() = static_cast<bool>(temp.x());
                value.y() = static_cast<bool>(temp.y());
                value.z() = static_cast<bool>(temp.z());
                value.w() = static_cast<bool>(temp.w());
            }
            else {
                D_ASSERT_TRUE(false, "Invalid uniform type.");
            }
            return value;
        }

        Int getUniformLocation(const std::string& uName) const override {
            GAPI_FUNCTION_LOG("getUniformLocation", uName);
            auto it = uniformLocationsCache.find(uName);
            if (it != uniformLocationsCache.end()) {
                // If the uniform is found, return the location.
                GAPI_FUNCTION_IMPLEMENTATION_LOG("cacheing uniform location...", uName);
                return it->second;
            }
            // If the uniform is not found, get the location and cache it.
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetUniformLocation", boundShaderProgram,
                                             uName);
            GLint location = glGetUniformLocation(boundShaderProgram, uName.c_str());
            D_ASSERT_NOT_EQUAL(location, -1, "Uniform " + uName + " not found.");
            uniformLocationsCache[uName] = location;
            return location;
        }

        std::vector<std::string> getAllUniforms() const override {
            D_ASSERT_TRUE(boundShaderProgram != 0, "No shader program bound.");
            GAPI_FUNCTION_NO_ARGS_LOG("getAllUniforms");
            std::vector<std::string> uniforms;
            GLint numUniforms;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetProgramiv", boundShaderProgram,
                                             GL_ACTIVE_UNIFORMS, &numUniforms);
            glGetProgramiv(boundShaderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
            for (int i = 0; i < numUniforms; i++) {
                char name[256];
                GLsizei length;
                GLint size;
                GLenum type;
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetActiveUniform", boundShaderProgram, i,
                                                 256, &length, &size, &type, name);
                glGetActiveUniform(boundShaderProgram, i, 256, &length, &size, &type, name);
                std::string uniform = std::string(name) + "(type:" + std::to_string(type) + " size:" +
                    std::to_string(size) + ")";
                uniforms.emplace_back(uniform);
            }
            return uniforms;
        }

        void clear(const std::initializer_list<Enums::ClearBits>& values) override {
            GAPI_FUNCTION_LOG("clear", values);
            GLuint mask = 0;
            for (auto value : values) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glClear", value);
                mask |= static_cast<GLenum>(value);
            }
            glClear(mask);
        }

        void clearColor(Float r, Float g, Float b, Float a) override {
            GAPI_FUNCTION_LOG("clearColor", r, g, b, a);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glClearColor", r, g, b, a);
            glClearColor(r, g, b, a);
        }


        void createContext(SDL_Window& window) override {
            GAPI_FUNCTION_NO_ARGS_LOG("createContext");
            // OpenGL context initialization over the SDL windowManager,
            // needed for using OpenGL functions
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CreateContext", "SDL_Window");
            this->context = SDL_GL_CreateContext(&window);
            D_ASSERT_NOT_EQUAL(this->context, nullptr,
                               "Unable to create context: " + std::string(SDL_GetError()));
            Logger::get().success("GL context created!");
        }

    private:
        void setSDLGLAttribute(SDL_GLattr attrib, int val) {
            GAPI_FUNCTION_LOG("setSDLGLAttribute", attrib, val);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_SetAttribute", attrib, val);
            int err = SDL_GL_SetAttribute(attrib, val);
            D_ASSERT_NOT_EQUAL(err, -1, "Unable to set gl attribute: " + std::string(SDL_GetError()));
        }


        /**
         * @brief Must be called after creating the window and before
         * enabling gl functions like glEnable() or glCullFace()
         */
        static void initGLEW() {
            GAPI_FUNCTION_NO_ARGS_LOG("initGLEW");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glewExperimental", GL_TRUE);
            glewExperimental = GL_TRUE;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glewInit", 0);
            GLuint err = glewInit();
            std::string
                errStr = std::string(reinterpret_cast<const char*>(glewGetErrorString(err)));
            D_ASSERT_GLEW_OK((err == GLEW_OK), errStr);
        }


        Bool isTexture(TextureID textureID) override {
            Bool isTextureBool =
                static_cast<Bool>(textureCache.find(textureID) != textureCache.end());
            return isTextureBool;
        }

        Bool isTextureBound(TextureID textureID) override {
            Bool isTextureBoundBool =
                static_cast<Bool>(textureID == boundTexture);
            return isTextureBoundBool;
        }

        Bool anyTextureBound() override {
            Bool anyTextureBoundBool =
                static_cast<Bool>(boundTexture != 0);
            return anyTextureBoundBool;
        }


        SDL_GLContext context{};
    };
}
