/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/low-level-renderer/graphic-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/exceptions/core/low-level-renderer/GDIInitException.h"
#include "engine/core/low-level-renderer/graphic-device-interface/concrete-gdi/opengl/OpenGLDebugger.h"
#include <string>
#include "GL/glew.h"
#include "engine/core/asserts/Asserts.h"
#include "engine/Config.h"


OpenGLGDI::OpenGLGDI() : context(nullptr) {
    glslMajorVersion = GLESC_GL_MAJOR_VERSION;
    glslMinorVersion = GLESC_GL_MINOR_VERSION;
    isGlslCore = GLESC_GL_CORE_PROFILE;
    ASSERT(glslMajorVersion >= 4 && glslMinorVersion >= 3,
           "OpenGL version must be at least 4.3 for this engine to work");


}

void OpenGLGDI::createContext(SDL_Window &window, GDIint w, GDIint h, GDIint x, GDIint y) {
    // OpenGL context initialization over the SDL windowManager, needed for using OpenGL functions
    if ((this->context = SDL_GL_CreateContext(&window)) == nullptr)
        throw EngineException("Unable to create context: " + std::string(SDL_GetError()));
    
    Logger::get().success("GL context created!");
    // Must be called after creating the context
    this->setViewport(x, y, w, h);
}



std::function<void(SDL_Window &)> OpenGLGDI::getSwapBuffersFunc() {
    return [](SDL_Window &window) {
        SDL_GL_SwapWindow(&window);
    };
}

void OpenGLGDI::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void OpenGLGDI::setViewport(int width, int height) {
    this->setViewport(0, 0, width, height);
}

void OpenGLGDI::setViewport() {

}


void OpenGLGDI::setSDLGLAttribute(SDL_GLattr attrib, int val) {
    if (SDL_GL_SetAttribute(attrib, val) == -1)
        throw GDIException("Unable to set gl attribute: " + std::string(SDL_GetError()));
}


void OpenGLGDI::deleteContext() {
    SDL_GL_DeleteContext(this->context);
}


GDIint OpenGLGDI::translateEnumToOpenGL(GDIValues value) {
    switch (static_cast<int>(value)) {
        // Texture Filter
        case static_cast<GLuint>(GDIValues::MinFilterNearest):
            return GL_NEAREST;
        case static_cast<GLuint>(GDIValues::MinFilterLinear):
            return GL_LINEAR;
        case static_cast<GLuint>(GDIValues::MinFilterNearestMipmapNearest):
            return GL_NEAREST_MIPMAP_NEAREST;
        case static_cast<GLuint>(GDIValues::MinFilterLinearMipmapNearest):
            return GL_LINEAR_MIPMAP_NEAREST;
        case static_cast<GLuint>(GDIValues::MinFilterNearestMipmapLinear):
            return GL_NEAREST_MIPMAP_LINEAR;
        case static_cast<GLuint>(GDIValues::MinFilterLinearMipmapLinear):
            return GL_LINEAR_MIPMAP_LINEAR;
        case static_cast<GLuint>(GDIValues::MagFilterNearest):
            return GL_NEAREST;
        case static_cast<GLuint>(GDIValues::MagFilterLinear):
            return GL_LINEAR;
        case static_cast<GLuint>(GDIValues::WrapModeRepeat):
            return GL_REPEAT;
        case static_cast<GLuint>(GDIValues::WrapModeMirroredRepeat):
            return GL_MIRRORED_REPEAT;
        case static_cast<GLuint>(GDIValues::WrapModeClampToEdge):
            return GL_CLAMP_TO_EDGE;
        case static_cast<GLuint>(GDIValues::WrapModeClampToBorder):
            return GL_CLAMP_TO_BORDER;
            // Buffers
            // Vertex target (type)
        case static_cast<GLuint>(GDIValues::BufferTypeVertex):
            return GL_ARRAY_BUFFER;
        case static_cast<GLuint>(GDIValues::BufferTypeIndex):
            return GL_ELEMENT_ARRAY_BUFFER;
            // Usage
        case static_cast<GLuint>(GDIValues::BufferUsageStatic):
            return GL_STATIC_READ;
        case static_cast<GLuint>(GDIValues::BufferUsageDynamic):
            return GL_DYNAMIC_READ;
            
            // Shader Types
        case static_cast<GLuint>(GDIValues::ShaderTypeVertex):
            return GL_VERTEX_SHADER;
        case static_cast<GLuint>(GDIValues::ShaderTypeFragment):
            return GL_FRAGMENT_SHADER;
        default:
            throw GDIException("Texture filter not supported");
        
    }
}

void OpenGLGDI::clear(GDIValues clearBits, ...) {

}

void OpenGLGDI::clearColor(GDIfloat r, GDIfloat g, GDIfloat b, GDIfloat a) {

}




// -------------------------------------------------------------------------
// ------------------------------ Buffers ----------------------------------



void OpenGLGDI::genBuffers(GDIuint amount, GDIint &bufferID) {

}

void OpenGLGDI::bindBuffer(GDIValues bufferType, GDIuint buffer) {

}

void OpenGLGDI::unbindBuffer(GDIValues bufferType) {

}

void OpenGLGDI::deleteBuffer(GDIuint buffer) {

}

void
OpenGLGDI::setBufferData(const void *data, GDIsize size, GDIuint buffer, GDIValues bufferType, GDIValues bufferUsage) {

}



// -------------------------------------------------------------------------
// ------------------------------ Texture ----------------------------------




GDIuint OpenGLGDI::createTexture(SDL_Surface &surface,
                                 GDIValues minFilter,
                                 GDIValues magFilter,
                                 GDIValues wrapS,
                                 GDIValues wrapT) {
    GDIuint textureID;
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


void OpenGLGDI::deleteTexture(GDIuint textureID) {
    glDeleteTextures(1, &textureID);
}

GDIuint OpenGLGDI::createTexture(SDL_Surface &surface) {
    return this
            ->createTexture(surface, GDIValues::MinFilterLinear, GDIValues::MagFilterLinear, GDIValues::WrapModeRepeat,
                            GDIValues::WrapModeRepeat);
}


void OpenGLGDI::bindTexture(GDIuint textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void OpenGLGDI::initGLEW() {
    GLuint err;
    glewExperimental = GL_TRUE;
    if ((err = glewInit()) != GLEW_OK)
        throw GDIInitException(
                "Unable to initialize GLEW: " + std::string(reinterpret_cast<const char *>(glewGetErrorString(err))));
}

void OpenGLGDI::postWindowCreationInit() {
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
    // Parameters: 0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive v-sync
    // More info: https://wiki.libsdl.org/SDL2/SDL_GL_SetSwapInterval
    if (SDL_GL_SetSwapInterval(1) == -1)
        throw EngineException(std::string("Unable activate v-sync (swap interval): ") + std::string(SDL_GetError()));
    // Core functions of OpenGL a.k.a. full modern openGL functionality.
    // More info: https://wiki.libsdl.org/SDL_GLprofile
    if (isGlslCore)
        setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    else
        setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    // We're using OpenGL Version 4.3 (released in 2012).
    // Changing this numbers will change some functions available of OpenGL.
    // Choosing a relatively old version of OpenGl allow most computers to use it.
    setSDLGLAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glslMajorVersion);
    setSDLGLAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glslMinorVersion);
    // Stencil size of 4 bits is used
    // Could be increased later if needed
    // Increases performance the lower it is, less data stored in each pixel
    setSDLGLAttribute(SDL_GL_STENCIL_SIZE, 4);
    // Enable debug context
    // Possible performance loss
    OpenGLDebugger::setSdlGlDebugContextAttribute();
    

}

// -------------------------------------------------------------------------
// --------------------------- Shader functions ----------------------------




GDIuint OpenGLGDI::loadAndCompileShader(GDIValues shaderType, const std::string &shaderSource) {
    GLuint vertexShader = glCreateShader(translateEnumToOpenGL(shaderType));
    const GDIchar *source = shaderSource.c_str();
    
    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);
    
    return vertexShader;
}

bool OpenGLGDI::compilationOK(GDIuint shaderID, GDIchar *message) {
    int error;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &error);
    if (error == GL_TRUE) {
        glGetShaderInfoLog(shaderID, 512, nullptr, message);
        return true;
    }
    return false;
    
    
}

GDIuint OpenGLGDI::createShaderProgram(GDIuint vertexShaderID, GDIuint fragmentShaderID) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragmentShaderID);
    
    glLinkProgram(shaderProgram);
    
    return shaderProgram;
}

bool OpenGLGDI::linkOK(GDIuint shaderProgram, GDIchar *message) {
    int error;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &error);
    if (error == GL_TRUE) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, message);
        return true;
    }
    return false;
}

void OpenGLGDI::useShaderProgram(GDIuint shaderProgram) {
    glUseProgram(shaderProgram);
}

void OpenGLGDI::deleteShader(GDIuint shaderID) {
    glDeleteShader(shaderID);
}


// --------------------------- Uniforms ----------------------------

GDIint OpenGLGDI::getUniformLocation(GDIuint program, const std::string &name) {
    return glGetUniformLocation(program, name.c_str());
}

void OpenGLGDI::setUniform1Float(GDIint location, GDIfloat v0) {
    glUniform1f(location, v0);
}

void OpenGLGDI::setUniform1FloatVector(GDIint location, GDIsize count, const GDIfloat *value) {
    glUniform1fv(location, count, value);
}

void OpenGLGDI::setUniform1Int(GDIint location, GDIint v0) {
    glUniform1i(location, v0);
}

void OpenGLGDI::setUniform1IntVector(GDIint location, GDIsize count, const GDIint *value) {
    glUniform1iv(location, count, value);
}

void OpenGLGDI::setUniform2Float(GDIint location, GDIfloat v0, GDIfloat v1) {
    glUniform2f(location, v0, v1);
}

void OpenGLGDI::setUniform2FloatVector(GDIint location, GDIsize count, const GDIfloat *value) {
    glUniform2fv(location, count, value);
}

void OpenGLGDI::setUniform2Int(GDIint location, GDIint v0, GDIint v1) {
    glUniform2i(location, v0, v1);
}

void OpenGLGDI::setUniform2IntVector(GDIint location, GDIsize count, const GDIint *value) {
    glUniform2iv(location, count, value);
}

void OpenGLGDI::setUniform3Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2) {
    glUniform3f(location, v0, v1, v2);
}

void OpenGLGDI::setUniform3FloatVector(GDIint location, GDIsize count, const GDIfloat *value) {
    glUniform3fv(location, count, value);
}

void OpenGLGDI::setUniform3Int(GDIint location, GDIint v0, GDIint v1, GDIint v2) {
    glUniform3i(location, v0, v1, v2);
}

void OpenGLGDI::setUniform3IntVector(GDIint location, GDIsize count, const GDIint *value) {
    glUniform3iv(location, count, value);
}

void OpenGLGDI::setUniform4Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2, GDIfloat v3) {
    glUniform4f(location, v0, v1, v2, v3);
}

void OpenGLGDI::setUniform4FloatVector(GDIint location, GDIsize count, const GDIfloat *value) {
    glUniform4fv(location, count, value);
}

void OpenGLGDI::setUniform4Int(GDIint location, GDIint v0, GDIint v1, GDIint v2, GDIint v3) {
    glUniform4i(location, v0, v1, v2, v3);
}

void OpenGLGDI::setUniform4IntVector(GDIint location, GDIsize count, const GDIint *value) {
    glUniform4iv(location, count, value);
}

void OpenGLGDI::setUniformMatrix2FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) {
    glUniformMatrix2fv(location, count, transpose, value);
}

void OpenGLGDI::setUniformMatrix3FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) {
    glUniformMatrix3fv(location, count, transpose, value);
}

void OpenGLGDI::setUniformMatrix4FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) {
    glUniformMatrix4fv(location, count, transpose, value);
}
