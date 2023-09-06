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

#include "engine/Config.h"
#include "engine/core/exceptions/core/low-level-renderer/GAPIInitException.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/low-level-renderer/asserts/GAPIAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLDebugger.h"
#include "engine/core/low-level-renderer/debugger/graphic-api/GAPIDebugger.h"


class OpenGLAPI final : public IGraphicInterface {
public:
    explicit OpenGLAPI() {
        ASSERT_GL_CORRECT_VERSION();
    }
    
    
    [[nodiscard]] GraphicsAPI getGraphicsAPI() const override { return GraphicsAPI::OPENGL; }
    
    
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
        
        // TODO: Check this, it assumes that any 4-byte-per-pixel texture is RGBA, and any other texture is RGB.
        //  This might not always be correct depending on the specifics of the SDL_Surface format.
        GLenum format = (surface.format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        // Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface.w, surface.h, 0, format, GL_UNSIGNED_BYTE, surface.pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        
        bindTexture(0);
        return textureID;
    }
    
    
    GAPIuint createTexture(SDL_Surface &surface) override {
        return this
                ->createTexture(surface, GAPIValues::MinFilterLinear, GAPIValues::MagFilterLinear,
                                GAPIValues::WrapModeRepeat,
                                GAPIValues::WrapModeRepeat);
    }
    
    void bindTexture(GAPIuint textureID) override {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    
    std::function<void(SDL_Window &)> getSwapBuffersFunc() override {
        return [](SDL_Window &window) {
            SDL_GL_SwapWindow(&window);
        };
    }
    
    [[nodiscard]] SDL_GLContext getContext() const { return context; };
    
    void preWindowCreationInit() override {
        PRINT_GAPI_INIT("OpenGL",
                        std::to_string(GLESC_GL_MAJOR_VERSION) + "." + std::to_string(GLESC_GL_MINOR_VERSION));
        // Core functions of OpenGL a.k.a. full modern openGL functionality.
        // More info: https://wiki.libsdl.org/SDL_GLprofile
        if (GLESC_GLSL_CORE_PROFILE) [[likely]]
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        else
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
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
        OpenGLDebugger::setSdlGlDebugContextAttribute();
    }
    
    void postWindowCreationInit() override {
        // Initialize GLEW, must be called before the following OpenGL calls
        initGLEW();
        
        Logger::get().success("Glew Initialized!");
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
        OpenGLDebugger::enableGlDebugCallback();
        
        // This makes our buffer swap synchronized with the monitor's vertical refresh
        // Parameters: 0 for immediate updates,
        // 1 for updates synchronized with the vertical retrace,
        // -1 for adaptive v-sync
        // More info: https://wiki.libsdl.org/SDL2/SDL_GL_SetSwapInterval
        if (SDL_GL_SetSwapInterval(1) == -1)
            throw EngineException(
                    std::string("Unable activate v-sync (swap interval): ") + std::string(SDL_GetError()));
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
    
    void
    setBufferData(const std::any *data,
                  GAPIsize size,
                  GAPIuint buffer,
                  GAPIValues bufferType,
                  GAPIValues bufferUsage) override {
        glBufferData(translateEnumToOpenGL(bufferType), size, data, translateEnumToOpenGL(bufferUsage));
    }
    
    // ---------------------------- Shader functions --------------------------------
    // ------------------------------------------------------------------------------
    
    
    GAPIuint loadAndCompileShader(GAPIValues shaderType, const std::string &shaderSource) override {
        GLuint vertexShader = glCreateShader(translateEnumToOpenGL(shaderType));
        const GAPIchar *source = shaderSource.c_str();
        
        glShaderSource(vertexShader, 1, &source, nullptr);
        glCompileShader(vertexShader);
        
        return vertexShader;
    }
    
    
    [[nodiscard]] bool compilationOK(GAPIuint shaderID, GAPIchar *message) override {
        int error;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &error);
        if (error == GL_TRUE) {
            glGetShaderInfoLog(shaderID, 512, nullptr, message);
            return true;
        }
        return false;
    }
    
    GAPIuint createShaderProgram(GAPIuint vertexShaderID, GAPIuint fragmentShaderID) override {
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShaderID);
        glAttachShader(shaderProgram, fragmentShaderID);
        
        glLinkProgram(shaderProgram);
        
        return shaderProgram;
    }
    
    [[nodiscard]] bool linkOK(GAPIuint shaderProgram, GAPIchar *message) override {
        int error;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &error);
        if (error == GL_TRUE) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, message);
            return true;
        }
        return false;
    }
    
    
    
    // -------------------------------- Uniforms ------------------------------------
    
    
    inline GAPIint getUniformLocation(GAPIuint program, const std::string &name) override {
        return glGetUniformLocation(program, name.c_str());
    }
    
    inline void setUniform1Float(GAPIint location, GAPIfloat v0) override {
        glUniform1f(location, v0);
    }
    
    inline void setUniform1FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) override {
        glUniform1fv(location, count, value);
    }
    
    inline void setUniform1Int(GAPIint location, GAPIint v0) override {
        glUniform1i(location, v0);
    }
    
    inline void setUniform1IntVector(GAPIint location, GAPIsize count, const GAPIint *value) override {
        glUniform1iv(location, count, value);
    }
    
    inline void setUniform2Float(GAPIint location, GAPIfloat v0, GAPIfloat v1) override {
        glUniform2f(location, v0, v1);
    }
    
    inline void setUniform2FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) override {
        glUniform2fv(location, count, value);
    }
    
    inline void setUniform2Int(GAPIint location, GAPIint v0, GAPIint v1) override {
        glUniform2i(location, v0, v1);
    }
    
    inline void setUniform2IntVector(GAPIint location, GAPIsize count, const GAPIint *value) override {
        glUniform2iv(location, count, value);
    }
    
    inline void setUniform3Float(GAPIint location, GAPIfloat v0, GAPIfloat v1, GAPIfloat v2) override {
        glUniform3f(location, v0, v1, v2);
    }
    
    inline void setUniform3FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) override {
        glUniform3fv(location, count, value);
    }
    
    inline void setUniform3Int(GAPIint location, GAPIint v0, GAPIint v1, GAPIint v2) override {
        glUniform3i(location, v0, v1, v2);
    }
    
    inline void setUniform3IntVector(GAPIint location, GAPIsize count, const GAPIint *value) override {
        glUniform3iv(location, count, value);
    }
    
    inline void setUniform4Float(GAPIint location, GAPIfloat v0, GAPIfloat v1, GAPIfloat v2, GAPIfloat v3) override {
        glUniform4f(location, v0, v1, v2, v3);
    }
    
    inline void setUniform4FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) override {
        glUniform4fv(location, count, value);
    }
    
    inline void setUniform4Int(GAPIint location, GAPIint v0, GAPIint v1, GAPIint v2, GAPIint v3) override {
        glUniform4i(location, v0, v1, v2, v3);
    }
    
    inline void setUniform4IntVector(GAPIint location, GAPIsize count, const GAPIint *value) override {
        glUniform4iv(location, count, value);
    }
    
    inline void
    setUniformMatrix2FloatVector(GAPIint location,
                                 GAPIsize count,
                                 GAPIbool transpose,
                                 const GAPIfloat *value) override {
        glUniformMatrix2fv(location, count, transpose, value);
    }
    
    inline void
    setUniformMatrix3FloatVector(GAPIint location,
                                 GAPIsize count,
                                 GAPIbool transpose,
                                 const GAPIfloat *value) override {
        glUniformMatrix3fv(location, count, transpose, value);
    }
    
    inline void
    setUniformMatrix4FloatVector(GAPIint location,
                                 GAPIsize count,
                                 GAPIbool transpose,
                                 const GAPIfloat *value) override {
        glUniformMatrix4fv(location, count, transpose, value);
    }
    
    
    void useShaderProgram(GAPIuint shaderProgram) override {
        glUseProgram(shaderProgram);
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
    
    
    void deleteShader(GAPIuint shaderID) override {
        glDeleteShader(shaderID);
    }
    
    void createContext(SDL_Window &window, GAPIint w, GAPIint h, GAPIint x, GAPIint y) override {
        // OpenGL context initialization over the SDL windowManager, needed for using OpenGL functions
        this->context = SDL_GL_CreateContext(&window);
        ASSERT_NOT_EQUAL(this->context, nullptr, "Unable to create context: " + std::string(SDL_GetError()));
        Logger::get().success("GL context created!");
        // Must be called after creating the context
        this->setViewport(x, y, w, h);
    }

private:
    
    void setSDLGLAttribute(SDL_GLattr attrib, int val) {
        if (SDL_GL_SetAttribute(attrib, val) == -1)
            throw GAPIException("Unable to set gl attribute: " + std::string(SDL_GetError()));
    }
    
    
    /**
     * @brief Must be called after creating the window and before enabling gl functions like glEnable() or glCullFace()
     */
    static void initGLEW() {
        GLuint err;
        glewExperimental = GL_TRUE;
        if ((err = glewInit()) != GLEW_OK)
            throw GAPIInitException(
                    "Unable to initialize GLEW: " +
                    std::string(reinterpret_cast<const char *>(glewGetErrorString(err))));
    }
    
    static GAPIint translateEnumToOpenGL(GAPIValues value) {
        switch (static_cast<int>(value)) {
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
            case static_cast<GLuint>(GAPIValues::BufferUsageStatic):
                return GL_STATIC_READ;
            case static_cast<GLuint>(GAPIValues::BufferUsageDynamic):
                return GL_DYNAMIC_READ;
                
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
            default:
                throw GAPIException("Texture filter not supported");
            
        }
    }
    
    
    SDL_GLContext context{};
    
};

