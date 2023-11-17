/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <functional>
#include <SDL2/SDL.h>
#include <string>
#include <GL/glew.h>
#include <engine/core/math/Vec.h>

#include "engine/Config.h"
#include "engine/core/exceptions/core/low-level-renderer/GAPIInitException.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/low-level-renderer/asserts/GAPIAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLDebugger.h"
#include "engine/core/low-level-renderer/debugger/graphic-api/GAPIDebugger.h"

namespace GLESC {
    class OpenGLAPI final : public IGraphicInterface {
    public:
        explicit OpenGLAPI() {
            ASSERT_GL_CORRECT_VERSION();
        }
        
        
        void deleteTexture(GAPIuint textureID) override {
            glDeleteTextures(1, &textureID);
        }
        
        void deleteContext() override {
            SDL_GL_DeleteContext(this->context);
        }
        
        void setViewport(GAPIint width, GAPIint height) override {
            this->setViewport(0, 0, width, height);
        }
        
        void setViewport(GAPIint x, GAPIint y, GAPIint width, GAPIint height) override {
            glViewport(x, y, width, height);
        }
        
        std::tuple<GAPIint, GAPIint, GAPIint, GAPIint> getViewport() override {
            GAPIint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            return std::make_tuple(viewport[0], viewport[1], viewport[2], viewport[3]);
        }
        
        
        GAPIuint createTexture(SDL_Surface &surface,
                               GAPIValues minFilter,
                               GAPIValues magFilter,
                               GAPIValues wrapS,
                               GAPIValues wrapT) override {
            GAPIuint textureID;
            glGenTextures(1, &textureID);
            bindTexture(textureID);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, translateEnumToOpenGL(minFilter));
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, translateEnumToOpenGL(magFilter));
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, translateEnumToOpenGL(wrapS));
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, translateEnumToOpenGL(wrapT));
            
            // TODO: Check this, it assumes that any 4-byte-per-pixel texture is RGBA,
            //  and any other texture is RGB.
            //  This might not always be correct depending on the specifics of the SDL_Surface
            //  format.
            GLenum format = (surface.format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
            // Generate the texture
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface.w, surface.h, 0, format,
                         GL_UNSIGNED_BYTE, surface.pixels);
            glGenerateMipmap(GL_TEXTURE_2D);
            
            
            bindTexture(0);
            return textureID;
        }
        
        
        GAPIuint createTexture(SDL_Surface &surface) override {
            return this->createTexture(surface, GAPIValues::MinFilterLinear,
                                       GAPIValues::MagFilterLinear, GAPIValues::WrapModeRepeat,
                                       GAPIValues::WrapModeRepeat);
        }
        
        void bindTexture(GAPIuint textureID) override {
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
        
        void swapBuffers(SDL_Window &window) override {
            SDL_GL_SwapWindow(&window);
        }
        
        [[nodiscard]] SDL_GLContext getContext() const { return context; };
        
        void preWindowConfig() override {
            PRINT_GAPI_INIT("OpenGL", std::to_string(GLESC_GL_MAJOR_VERSION) + "." +
                                      std::to_string(GLESC_GL_MINOR_VERSION));
            // Core functions of OpenGL a.k.a. full modern openGL functionality.
            // More info: https://wiki.libsdl.org/SDL_GLprofile
            #ifdef GLESC_GLSL_CORE_PROFILE
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            #else
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
            #endif
            // We're using OpenGL Version 4.3 (released in 2012).
            // Changing this numbers will change some functions available of OpenGL.
            // Choosing a relatively old version of OpenGl allow most computers to use it.
            setSDLGLAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GLESC_GL_MAJOR_VERSION);
            setSDLGLAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GLESC_GL_MINOR_VERSION);
            // Stencil size of 4 bits is used
            // Could be increased later if needed
            // Increases performance the lower it is, fewer data stored in each pixel
            setSDLGLAttribute(SDL_GL_STENCIL_SIZE, 4);
            // Enable debug context
            // Possible performance loss
            GL_SET_DEBUG_CONTEXT_ATTRIBUTE();
        }
        
        void postWindowCreationInit() override {
            // Initialize GLEW, must be called before the following OpenGL calls
            initGLEW();
            
            GLESC::Logger::get().success("Glew Initialized!");
            // Enable depth test
            // Fragments will be discarded if they are behind
            // More info: https://www.khronos.org/opengl/wiki/Depth_Test
            glEnable(GL_DEPTH_TEST);
            // Accept fragment if it closer to the camera than the former one
            glDepthFunc(GL_LESS);
            // Enable back face culling
            // Important for performance
            // More info: https://www.khronos.org/opengl/wiki/Face_Culling
            glEnable(GL_CULL_FACE);
            // Cull back faces (default)
            // Important for performance and to avoid self-shadowing
            glCullFace(GL_BACK);
            // Set the front face to be counter-clockwise (default)
            glFrontFace(GL_CCW);
            // Enable blending
            // Important for transparency and other effects
            // More info: https://www.khronos.org/opengl/wiki/Blending
            glEnable(GL_BLEND);
            // Set blending function to alpha blending (default)
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // Set blending equation to add (default)
            glBlendEquation(GL_FUNC_ADD);
            
            // Enable opengl debug callback
            // Improves debugging outputs
            GL_ENABLE_DEBUG_CALLBACK();
            
            // This makes our buffer swap synchronized with the monitor's vertical refresh
            // Parameters: 0 for immediate updates,
            // 1 for updates synchronized with the vertical retrace,
            // -1 for adaptive v-sync
            // More info: https://wiki.libsdl.org/SDL2/SDL_GL_SetSwapInterval
            if (SDL_GL_SetSwapInterval(1) == -1)
                throw EngineException(std::string("Unable activate v-sync (swap interval): ") +
                                      std::string(SDL_GetError()));
        }
        
        void draw(GAPIValues primitiveType, GAPIuint start, GAPIuint count) override {
            glDrawArrays(translateEnumToOpenGL(primitiveType), start, count);
        }
        
        RGBColor readPixelColor(int x, int y) {
            RGBColor color;
            glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
            return color;
        }
        
        RGBColorNormalized readPixelColorNormalized(int x, int y) {
            RGBColorNormalized color;
            glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
            return color;
        }
        
        
        // -------------------------------------------------------------------------
        // ------------------------------ Buffers ----------------------------------
        
        void genBuffers(GAPIuint amount, GAPIuint &bufferID) override {
            glGenBuffers(amount, &bufferID);
        }
        
        void bindBuffer(GAPIValues bufferType, GAPIuint buffer) override {
            glBindBuffer(translateEnumToOpenGL(bufferType), buffer);
        }
        
        void unbindBuffer(GAPIValues bufferType) override {
            glBindBuffer(translateEnumToOpenGL(bufferType), 0);
        }
        
        void deleteBuffer(GAPIuint buffer) override {
            glDeleteBuffers(1, &buffer);
        }
        
        void setBufferData(const void *data,
                           GAPIsize size,
                           GAPIValues bufferType,
                           GAPIValues bufferUsage) override {
            glBufferData(translateEnumToOpenGL(bufferType), size, data,
                         translateEnumToOpenGL(bufferUsage));
        }
        
        void genVertexArray(GAPIuint &vertexArrayID) override {
            glGenVertexArrays(1, &vertexArrayID);
        };
        
        void bindVertexArray(GAPIuint vertexArrayID) override {
            glBindVertexArray(vertexArrayID);
        }
        
        void unbindVertexArray() override {
            glBindVertexArray(0);
        }
        
        void deleteVertexArray(GAPIuint vertexArrayID) override {
            glDeleteVertexArrays(1, &vertexArrayID);
        }
        
        void enableVertexAttribArray(GAPIuint index) override {
            glEnableVertexAttribArray(index);
        }
        
        void vertexAttribPointer(GAPIuint vertexArray,
                                 GAPIuint count,
                                 GAPITypes type,
                                 GAPIbool isNormalized,
                                 GAPIuint stride,
                                 GAPIuint offset) override {
            glVertexAttribPointer(vertexArray, count, static_cast<GLenum>(type), isNormalized,
                                  stride, (GLvoid *) (offset));
        }
        
        
        // ---------------------------- Shader functions --------------------------------
        // ------------------------------------------------------------------------------
        
        
        GAPIuint
        loadAndCompileShader(GAPIValues shaderType, const std::string &shaderSource) override {
            GLuint vertexShader = glCreateShader(translateEnumToOpenGL(shaderType));
            const GAPIchar *source = shaderSource.c_str();
            
            glShaderSource(vertexShader, 1, &source, nullptr);
            glCompileShader(vertexShader);
            
            return vertexShader;
        }
        
        
        GAPIuint createShaderProgram(GAPIuint vertexShaderID, GAPIuint fragmentShaderID) override {
            GLuint shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShaderID);
            glAttachShader(shaderProgram, fragmentShaderID);
            
            glLinkProgram(shaderProgram);
            
            return shaderProgram;
        }
        
        void destroyShaderProgram(GAPIuint shaderProgram) {
            glDeleteProgram(shaderProgram);
        }
        
        [[nodiscard]] bool compilationOK(GAPIuint shaderID, GAPIchar *message) override {
            GLint success;
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shaderID, 512, nullptr, message);
                return false;
            }
            return true;
        }
        
        [[nodiscard]] bool linkOK(GAPIuint shaderProgram, GAPIchar *message) override {
            GLint success;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, nullptr, message);
                return false;
            }
            return true;
        }
        
        void useShaderProgram(GAPIuint shaderProgram) override {
            glUseProgram(shaderProgram);
        }
        
        void deleteShader(GAPIuint shaderID) override {
            glDeleteShader(shaderID);
        }
        // -------------------------------- Uniforms ------------------------------------
        
        class GLUniformSetter : public IUniformSetter {
            friend class OpenGLAPI;
        
        public:
            // Implement single value setters
            void u1F(GAPIfloat v0) override {
                glUniform1f(location, v0);
            }
            
            void u1I(GAPIint v0) override {
                glUniform1i(location, v0);
            }
            
            void u1Ui(GAPIuint v0) override {
                glUniform1ui(location, v0);
            }
            
            void u1B(GAPIbool v0) override {
                glUniform1i(location, static_cast<GAPIint>(v0));
            }
            
            
            // Single vectors
            // Floats
            void u2F(Vec2F vec2) override {
                glUniform2f(location, vec2.x(), vec2.y());
            }
            
            void u3F(Vec3F vec3) override {
                glUniform3f(location, vec3.x(), vec3.y(), vec3.z());
            }
            
            void u4F(Vec4F vec4) override {
                glUniform4f(location, vec4.x(), vec4.y(), vec4.z(), vec4.w());
            }
            
            void u2F(GAPIfloat vec2[2]) override {
                glUniform2f(location, vec2[0], vec2[1]);
            }
            
            void u3F(GAPIfloat vec3[3]) override {
                glUniform3f(location, vec3[0], vec3[1], vec3[2]);
            }
            
            void u4F(GAPIfloat vec4[4]) override {
                glUniform4f(location, vec4[0], vec4[1], vec4[2], vec4[3]);
            }
            
            void u2F(GAPIfloat v0, GAPIfloat v1) override {
                glUniform2f(location, v0, v1);
            }
            
            void u3F(GAPIfloat v0, GAPIfloat v1, GAPIfloat v2) override {
                glUniform3f(location, v0, v1, v2);
            }
            
            void u4F(GAPIfloat v0, GAPIfloat v1, GAPIfloat v2, GAPIfloat v3) override {
                glUniform4f(location, v0, v1, v2, v3);
            }
            
            // Ints
            void u2I(Vec2I vec2) override {
                glUniform2i(location, vec2.x(), vec2.y());
            }
            
            void u3I(Vec3I vec3) override {
                glUniform3i(location, vec3.x(), vec3.y(), vec3.z());
            }
            
            void u4I(Vec4I vec4) override {
                glUniform4i(location, vec4.x(), vec4.y(), vec4.z(), vec4.w());
            }
            
            void u2I(GAPIint vec2[2]) override {
                glUniform2i(location, vec2[0], vec2[1]);
            }
            
            void u3I(GAPIint vec3[3]) override {
                glUniform3i(location, vec3[0], vec3[1], vec3[2]);
            }
            
            void u4I(GAPIint vec4[4]) override {
                glUniform4i(location, vec4[0], vec4[1], vec4[2], vec4[3]);
            }
            
            void u2I(GAPIint v0, GAPIint v1) override {
                glUniform2i(location, v0, v1);
            }
            
            void u3I(GAPIint v0, GAPIint v1, GAPIint v2) override {
                glUniform3i(location, v0, v1, v2);
            }
            
            void u4I(GAPIint v0, GAPIint v1, GAPIint v2, GAPIint v3) override {
                glUniform4i(location, v0, v1, v2, v3);
            }
            
            // Unsigned ints
            void u2Ui(Vec2Ui vec2) override {
                glUniform2ui(location, vec2.x(), vec2.y());
            }
            
            void u3Ui(Vec3Ui vec3) override {
                glUniform3ui(location, vec3.x(), vec3.y(), vec3.z());
            }
            
            void u4Ui(Vec4Ui vec4) override {
                glUniform4ui(location, vec4.x(), vec4.y(), vec4.z(), vec4.w());
            }
            
            void u2Ui(GAPIuint vec2[2]) override {
                glUniform2ui(location, vec2[0], vec2[1]);
            }
            
            void u3Ui(GAPIuint vec3[3]) override {
                glUniform3ui(location, vec3[0], vec3[1], vec3[2]);
            }
            
            void u4Ui(GAPIuint vec4[4]) override {
                glUniform4ui(location, vec4[0], vec4[1], vec4[2], vec4[3]);
            }
            
            void u2Ui(GAPIuint v0, GAPIuint v1) override {
                glUniform2ui(location, v0, v1);
            }
            
            void u3Ui(GAPIuint v0, GAPIuint v1, GAPIuint v2) override {
                glUniform3ui(location, v0, v1, v2);
            }
            
            void u4Ui(GAPIuint v0, GAPIuint v1, GAPIuint v2, GAPIuint v3) override {
                glUniform4ui(location, v0, v1, v2, v3);
            }
            
            // Booleans
            void u2B(Vec2B vec2) override {
                glUniform2i(location, static_cast<GAPIint>(vec2.x()),
                            static_cast<GAPIint>(vec2.y()));
            }
            
            void u3B(Vec3B vec3) override {
                glUniform3i(location, static_cast<GAPIint>(vec3.x()),
                            static_cast<GAPIint>(vec3.y()),
                            static_cast<GAPIint>(vec3.z()));
            }
            
            void u4B(Vec4B vec4) override {
                glUniform4i(location, static_cast<GAPIint>(vec4.x()),
                            static_cast<GAPIint>(vec4.y()),
                            static_cast<GAPIint>(vec4.z()), static_cast<GAPIint>(vec4.w()));
            }
            
            void u2B(GAPIbool vec2[2]) override {
                glUniform2i(location, static_cast<GAPIint>(vec2[0]), static_cast<GAPIint>(vec2[1]));
            }
            
            void u3B(GAPIbool vec3[3]) override {
                glUniform3i(location, static_cast<GAPIint>(vec3[0]), static_cast<GAPIint>(vec3[1]),
                            static_cast<GAPIint>(vec3[2]));
            }
            
            void u4B(GAPIbool vec4[4]) override {
                glUniform4i(location, static_cast<GAPIint>(vec4[0]), static_cast<GAPIint>(vec4[1]),
                            static_cast<GAPIint>(vec4[2]), static_cast<GAPIint>(vec4[3]));
            }
            
            void u2B(GAPIbool v0, GAPIbool v1) override {
                glUniform2i(location, static_cast<GAPIint>(v0), static_cast<GAPIint>(v1));
            }
            
            void u3B(GAPIbool v0, GAPIbool v1, GAPIbool v2) override {
                glUniform3i(location, static_cast<GAPIint>(v0), static_cast<GAPIint>(v1),
                            static_cast<GAPIint>(v2));
            }
            
            void u4B(GAPIbool v0, GAPIbool v1, GAPIbool v2, GAPIbool v3) override {
                glUniform4i(location, static_cast<GAPIint>(v0), static_cast<GAPIint>(v1),
                            static_cast<GAPIint>(v2), static_cast<GAPIint>(v3));
            }
            
            
            // Single matrices
            // Floats
            void uMat2F(Mat2F mat) override {
                glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
            }
            
            void uMat3F(Mat3F mat) override {
                glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
            }
            
            void uMat4F(Mat4F mat) override {
                glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
            }
            
            // Vectors of vectors
            // Floats
            void u1FVec(const std::vector<GAPIfloat> &values) override {
                glUniform1fv(location, values.size(), values.data());
            }
            
            void u2FVec(const std::vector<Vec2F> &values) override {
                glUniform2fv(location, values.size(),
                             reinterpret_cast<const GLfloat *>(values.data()));
            }
            
            void u3FVec(const std::vector<Vec3F> &values) override {
                glUniform3fv(location, values.size(),
                             reinterpret_cast<const GLfloat *>(values.data()));
            }
            
            void u4FVec(const std::vector<Vec4F> &values) override {
                glUniform4fv(location, values.size(),
                             reinterpret_cast<const GLfloat *>(values.data()));
            }
            
            // Ints
            void u1IVec(const std::vector<GAPIint> &values) override {
                glUniform1iv(location, values.size(), values.data());
            }
            
            void u2IVec(const std::vector<Vec2I> &values) override {
                glUniform2iv(location, values.size(),
                             reinterpret_cast<const GLint *>(values.data()));
            }
            
            void u3IVec(const std::vector<Vec3I> &values) override {
                glUniform3iv(location, values.size(),
                             reinterpret_cast<const GLint *>(values.data()));
            }
            
            void u4IVec(const std::vector<Vec4I> &values) override {
                glUniform4iv(location, values.size(),
                             reinterpret_cast<const GLint *>(values.data()));
            }
            
            // Unsigned ints
            void u1UiVec(const std::vector<GAPIuint> &values) override {
                glUniform1uiv(location, values.size(), values.data());
            }
            
            void u2UiVec(const std::vector<Vec2Ui> &values) override {
                glUniform2uiv(location, values.size(),
                              reinterpret_cast<const GLuint *>(values.data()));
            }
            
            void u3UiVec(const std::vector<Vec3Ui> &values) override {
                glUniform3uiv(location, values.size(),
                              reinterpret_cast<const GLuint *>(values.data()));
            }
            
            void u4UiVec(const std::vector<Vec4Ui> &values) override {
                glUniform4uiv(location, values.size(),
                              reinterpret_cast<const GLuint *>(values.data()));
            }
            
            // Booleans
            void u1BVec(const std::vector<GAPIbool> &values) override {
                glUniform1iv(location, values.size(),
                             reinterpret_cast<const GLint *>(values.data()));
            }
            
            void u2BVec(const std::vector<Vec2B> &values) override {
                glUniform2iv(location, values.size(),
                             reinterpret_cast<const GLint *>(values.data()));
            }
            
            void u3BVec(const std::vector<Vec3B> &values) override {
                glUniform3iv(location, values.size(),
                             reinterpret_cast<const GLint *>(values.data()));
            }
            
            void u4BVec(const std::vector<Vec4B> &values) override {
                glUniform4iv(location, values.size(),
                             reinterpret_cast<const GLint *>(values.data()));
            }
            
            
            // Implement multiple matrix setters
            void uMat2FVec(const std::vector<Mat2F> &mats) override {
                glUniformMatrix2fv(location, mats.size(), GL_FALSE,
                                   reinterpret_cast<const GLfloat *>(mats.data()));
            }
            
            void uMat3FVec(const std::vector<Mat3F> &mats) override {
                glUniformMatrix3fv(location, mats.size(), GL_FALSE,
                                   reinterpret_cast<const GLfloat *>(mats.data()));
            }
            
            void uMat4FVec(const std::vector<Mat4F> &mats) override {
                glUniformMatrix4fv(location, mats.size(), GL_FALSE,
                                   reinterpret_cast<const GLfloat *>(mats.data()));
            }
        
        
        private:
            GLUniformSetter(GAPIuint program, const std::string uName) {
                // First, check if the program is a valid program generated by OpenGL
                if (!glIsProgram(program)) {
                    throw GAPIException("Can't set uniform, shader program is invalid");
                }
                // Get the location of the uniform
                GAPIint tempLocation = glGetUniformLocation(program, uName.c_str());
                
                // Check if the uniform location was found
                if (tempLocation == -1) {
                    throw GAPIException("Can't set uniform, uniform " + uName + " not found");
                }
                
                this->location = tempLocation;
            }
        
        private:
            GAPIuint location;
        };
        
        virtual std::unique_ptr<IUniformSetter>
        setUniform(GAPIuint program, const std::string &uName) override {
            return std::make_unique<GLUniformSetter>(GLUniformSetter(program, uName));
        }
        
        
        void clear(const std::initializer_list<GAPIValues> &values) override {
            GLuint mask = 0;
            for (auto value : values) {
                mask |= translateEnumToOpenGL(value);
            }
            glClear(mask);
        }
        
        void clearColor(GAPIfloat r, GAPIfloat g, GAPIfloat b, GAPIfloat a) override {
            glClearColor(r, g, b, a);
        }
        
        
        void createContext(SDL_Window &window) override {
            // OpenGL context initialization over the SDL windowManager,
            // needed for using OpenGL functions
            this->context = SDL_GL_CreateContext(&window);
            D_ASSERT_NOT_EQUAL(this->context, nullptr,
                               "Unable to create context: " + std::string(SDL_GetError()));
            GLESC::Logger::get().success("GL context created!");
        }
    
    
    private:
        
        void setSDLGLAttribute(SDL_GLattr attrib, int val) {
            if (SDL_GL_SetAttribute(attrib, val) == -1)
                throw GAPIException("Unable to set gl attribute: " + std::string(SDL_GetError()));
        }
        
        
        /**
         * @brief Must be called after creating the window and before
         * enabling gl functions like glEnable() or glCullFace()
         */
        static void initGLEW() {
            glewExperimental = GL_TRUE;
            GLuint err = glewInit();
            std::string
                    errStr = std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
            ASSERT_GLEW_OK((err == GLEW_OK), errStr);
        }
        
        static GAPIint translateEnumToOpenGL(GAPIValues value) {
            switch (static_cast<GAPIint>(value)) {
                // Texture Filter
                case static_cast<GLuint>(GAPIValues::MinFilterNearest):
                    return GL_NEAREST;
                case static_cast<GLuint>(GAPIValues::MinFilterLinear):
                    return GL_LINEAR;
                case static_cast<GLuint>(GAPIValues::MinFilterNearestMipmapNearest):
                    return GL_NEAREST_MIPMAP_NEAREST;
                case static_cast<GLuint>(GAPIValues::MinFilterLinearMipmapNearest):
                    return GL_LINEAR_MIPMAP_NEAREST;
                case static_cast<GLuint>(GAPIValues::MinFilterNearestMipmapLinear):
                    return GL_NEAREST_MIPMAP_LINEAR;
                case static_cast<GLuint>(GAPIValues::MinFilterLinearMipmapLinear):
                    return GL_LINEAR_MIPMAP_LINEAR;
                case static_cast<GLuint>(GAPIValues::MagFilterNearest):
                    return GL_NEAREST;
                case static_cast<GLuint>(GAPIValues::MagFilterLinear):
                    return GL_LINEAR;
                case static_cast<GLuint>(GAPIValues::WrapModeRepeat):
                    return GL_REPEAT;
                case static_cast<GLuint>(GAPIValues::WrapModeMirroredRepeat):
                    return GL_MIRRORED_REPEAT;
                case static_cast<GLuint>(GAPIValues::WrapModeClampToEdge):
                    return GL_CLAMP_TO_EDGE;
                case static_cast<GLuint>(GAPIValues::WrapModeClampToBorder):
                    return GL_CLAMP_TO_BORDER;
                    // Buffers
                    // Vertex target (type)
                case static_cast<GLuint>(GAPIValues::BufferTypeVertex):
                    return GL_ARRAY_BUFFER;
                case static_cast<GLuint>(GAPIValues::BufferTypeIndex):
                    return GL_ELEMENT_ARRAY_BUFFER;
                    // Usage
                case static_cast<GLuint>(GAPIValues::BufferUsageStaticDraw):
                    return GL_STATIC_DRAW;
                case static_cast<GLuint>(GAPIValues::BufferUsageDynamicDraw):
                    return GL_DYNAMIC_DRAW;
                case static_cast<GLuint>(GAPIValues::BufferUsageStreamDraw):
                    return GL_STREAM_DRAW;
                case static_cast<GLuint>(GAPIValues::BufferUsageStaticRead):
                    return GL_STATIC_READ;
                case static_cast<GLuint>(GAPIValues::BufferUsageDynamicRead):
                    return GL_DYNAMIC_READ;
                case static_cast<GLuint>(GAPIValues::BufferUsageStreamRead):
                    return GL_STREAM_READ;
                    
                    // Shader Types
                case static_cast<GLuint>(GAPIValues::ShaderTypeVertex):
                    return GL_VERTEX_SHADER;
                case static_cast<GLuint>(GAPIValues::ShaderTypeFragment):
                    return GL_FRAGMENT_SHADER;
                    
                    // Clear
                case static_cast<GLuint>(GAPIValues::ClearBitsDepth):
                    return GL_DEPTH_BUFFER_BIT;
                case static_cast<GLuint>(GAPIValues::ClearBitsColor):
                    return GL_COLOR_BUFFER_BIT;
                case static_cast<GLuint>(GAPIValues::ClearBitsStencil):
                    return GL_STENCIL_BUFFER_BIT;
                    
                    // Stencil
                case static_cast<GLuint>(GAPIValues::StencilTest):
                    return GL_STENCIL_TEST;
                case static_cast<GLuint>(GAPIValues::StencilTestAlways):
                    return GL_ALWAYS;
                case static_cast<GLuint>(GAPIValues::StencilTestNever):
                    return GL_NEVER;
                case static_cast<GLuint>(GAPIValues::StencilTestLess):
                    return GL_LESS;
                case static_cast<GLuint>(GAPIValues::StencilTestLessEqual):
                    return GL_LEQUAL;
                case static_cast<GLuint>(GAPIValues::StencilTestGreater):
                    return GL_GREATER;
                case static_cast<GLuint>(GAPIValues::StencilTestGreaterEqual):
                    return GL_GEQUAL;
                case static_cast<GLuint>(GAPIValues::StencilTestEqual):
                    return GL_EQUAL;
                case static_cast<GLuint>(GAPIValues::StencilTestNotEqual):
                    return GL_NOTEQUAL;
                case static_cast<GLuint>(GAPIValues::StencilFail):
                    return GL_STENCIL_FAIL;
                case static_cast<GLuint>(GAPIValues::StencilPassDepthFail):
                    return GL_STENCIL_PASS_DEPTH_FAIL;
                case static_cast<GLuint>(GAPIValues::StencilPassDepthPass):
                    return GL_STENCIL_PASS_DEPTH_PASS;
                case static_cast<GLuint>(GAPIValues::StencilFunc):
                    return GL_STENCIL_FUNC;
                case static_cast<GLuint>(GAPIValues::StencilRef):
                    return GL_STENCIL_REF;
                case static_cast<GLuint>(GAPIValues::StencilValueMask):
                    return GL_STENCIL_VALUE_MASK;
                case static_cast<GLuint>(GAPIValues::StencilWriteMask):
                    return GL_STENCIL_WRITEMASK;
                case static_cast<GLuint>(GAPIValues::StencilBackFunc):
                    return GL_STENCIL_BACK_FUNC;
                case static_cast<GLuint>(GAPIValues::StencilBackFail):
                    return GL_STENCIL_BACK_FAIL;
                case static_cast<GLuint>(GAPIValues::StencilBackPassDepthFail):
                    return GL_STENCIL_BACK_PASS_DEPTH_FAIL;
                case static_cast<GLuint>(GAPIValues::StencilBackPassDepthPass):
                    return GL_STENCIL_BACK_PASS_DEPTH_PASS;
                case static_cast<GLuint>(GAPIValues::StencilBackRef):
                    return GL_STENCIL_BACK_REF;
                case static_cast<GLuint>(GAPIValues::StencilBackValueMask):
                    return GL_STENCIL_BACK_VALUE_MASK;
                case static_cast<GLuint>(GAPIValues::StencilBackWriteMask):
                    return GL_STENCIL_BACK_WRITEMASK;
                    // Primitive types
                case static_cast<GLuint>(GAPIValues::PrimitiveTypeTriangles):
                    return GL_TRIANGLES;
                case static_cast<GLuint>(GAPIValues::PrimitiveTypeTriangleStrip):
                    return GL_TRIANGLE_STRIP;
                case static_cast<GLuint>(GAPIValues::PrimitiveTypeTriangleFan):
                    return GL_TRIANGLE_FAN;
                case static_cast<GLuint>(GAPIValues::PrimitiveTypeLines):
                    return GL_LINES;
                case static_cast<GLuint>(GAPIValues::PrimitiveTypeLineStrip):
                    return GL_LINE_STRIP;
                case static_cast<GLuint>(GAPIValues::PrimitiveTypeLineLoop):
                    return GL_LINE_LOOP;
                
            }
        }
        
        
        SDL_GLContext context{};
        
    };
    
}

