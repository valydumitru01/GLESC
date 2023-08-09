/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>
#include "SDL2/SDL.h"
#include <functional>

// TODO: Make the types be defined by the graphic API
typedef unsigned char GDIbool;
typedef unsigned int GDIuint;
typedef float GDIfloat;
typedef int GDIint;
typedef unsigned int GDIsize;
typedef char GDIchar;

enum class GraphicsAPI {
    OPENGL [[maybe_unused]] = 0, VULKAN [[maybe_unused]]
};

enum class GDIValues {
/**
 * @brief This class is used to define the different texture filters that can be used
 * @details It contains the different types of filters that can be used for the textures.
 * All the filters are defined as enums, each enum starts with a different number to avoid
 * overlapping between the different enums.
 */
    // Texture Filters
    MinFilterNearest [[maybe_unused]] = 0,
    MinFilterLinear [[maybe_unused]],
    MinFilterNearestMipmapNearest [[maybe_unused]],
    MinFilterLinearMipmapNearest [[maybe_unused]],
    MinFilterNearestMipmapLinear [[maybe_unused]],
    MinFilterLinearMipmapLinear [[maybe_unused]],
    MagFilterNearest [[maybe_unused]],
    MagFilterLinear [[maybe_unused]],
    WrapModeRepeat [[maybe_unused]],
    WrapModeMirroredRepeat [[maybe_unused]],
    WrapModeClampToEdge [[maybe_unused]],
    WrapModeClampToBorder [[maybe_unused]],
    // Buffers
    BufferTypeVertex [[maybe_unused]],
    BufferTypeIndex [[maybe_unused]],
    BufferUsageStatic [[maybe_unused]],
    BufferUsageDynamic [[maybe_unused]],
    BufferUsageStream [[maybe_unused]],
    // Clear Bits
    ClearBitsColor [[maybe_unused]],
    ClearBitsDepth [[maybe_unused]],
    ClearBitsStencil [[maybe_unused]],
    // Shader Type
    ShaderTypeVertex [[maybe_unused]],
    ShaderTypeFragment [[maybe_unused]]
};

class GraphicInterface {
public:
    GraphicInterface() = default;
    
    virtual ~GraphicInterface() = default;
    
    [[nodiscard]] virtual GraphicsAPI getGraphicsAPI() const = 0;
    
    virtual void clear(GDIValues clearBits...) = 0;
    
    virtual void clearColor(GDIfloat r, GDIfloat g, GDIfloat b, GDIfloat a) = 0;
    
    virtual void setViewport(int x, int y, int width, int height) = 0;
    
    virtual void setViewport(int width, int height) = 0;
    
    virtual void setViewport() = 0;
    
    virtual std::function<void(SDL_Window &)> getSwapBuffersFunc() = 0;
    
    virtual void createContext(SDL_Window &window, GDIint w, GDIint h, GDIint x, GDIint y) = 0;
    
    virtual void deleteContext() = 0;
    
    virtual void postWindowCreationInit() = 0;
    
    
    // ------------------------------------------------------------------------------
    // -------------------------------- Buffers -------------------------------------
    
    virtual void genBuffers(GDIuint amount, GDIint &bufferID) = 0;
    
    virtual void bindBuffer(GDIValues bufferType, GDIuint buffer) = 0;
    
    virtual void unbindBuffer(GDIValues bufferType) = 0;
    
    virtual void deleteBuffer(GDIuint buffer) = 0;
    
    virtual void
    setBufferData(const void *data, GDIsize size, GDIuint buffer, GDIValues bufferType, GDIValues bufferUsage) = 0;
    
    // ------------------------------------------------------------------------------
    // -------------------------------- Texture -------------------------------------
    
    /**
     * @brief Create a texture from an SDL_Surface
     * @details This function creates a texture from an SDL_Surface. It also sets the texture parameters.
     * @param surface
     * @param minFilter
     * @param magFilter
     * @param wrapS
     * @param wrapT
     * @return
     */
    virtual GDIuint
    createTexture(SDL_Surface &surface, GDIValues minFilter, GDIValues magFilter, GDIValues wrapS, GDIValues wrapT) = 0;
    
    /**
     * @brief Create texture with default parameters
     * @details The default parameters are:
     * minFilter = LINEAR
     * magFilter = LINEAR
     * wrapS = REPEAT
     * wrapT = REPEAT
     * @param textureID
     */
    virtual GDIuint createTexture(SDL_Surface &surface) = 0;
    
    virtual void bindTexture(GDIuint textureID) = 0;
    
    virtual void deleteTexture(GDIuint textureID) = 0;
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    
    
    virtual void useShaderProgram(GDIuint shaderProgram) = 0;
    
    virtual GDIuint loadAndCompileShader(GDIValues shaderType, const std::string &shaderSource) = 0;
    
    virtual bool compilationOK(GDIuint shaderID, GDIchar *message) = 0;
    
    virtual GDIuint createShaderProgram(GDIuint vertexShaderID, GDIuint fragmentShaderID) = 0;
    
    virtual bool linkOK(GDIuint programID, GDIchar *message) = 0;
    
    virtual void deleteShader(GDIuint shaderID) = 0;
    
    
    // -------------------------------- Uniforms ------------------------------------
    
    virtual int getUniformLocation(GDIuint program, const std::string &name) = 0;
    
    virtual void setUniform1Float(GDIint location, GDIfloat v0) = 0;
    
    virtual void setUniform1FloatVector(GDIint location, GDIsize count, const GDIfloat *value) = 0;
    
    virtual void setUniform1Int(GDIint location, GDIint v0) = 0;
    
    virtual void setUniform1IntVector(GDIint location, GDIsize count, const int *value) = 0;
    
    virtual void setUniform2Float(GDIint location, GDIfloat v0, GDIfloat v1) = 0;
    
    virtual void setUniform2FloatVector(GDIint location, GDIsize count, const GDIfloat *value) = 0;
    
    virtual void setUniform2Int(GDIint location, GDIint v0, GDIint v1) = 0;
    
    virtual void setUniform2IntVector(GDIint location, GDIsize count, const int *value) = 0;
    
    virtual void setUniform3Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2) = 0;
    
    virtual void setUniform3FloatVector(GDIint location, GDIsize count, const GDIfloat *value) = 0;
    
    virtual void setUniform3Int(GDIint location, GDIint v0, GDIint v1, GDIint v2) = 0;
    
    virtual void setUniform3IntVector(GDIint location, GDIsize count, const GDIint *value) = 0;
    
    virtual void setUniform4Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2, GDIfloat v3) = 0;
    
    virtual void setUniform4FloatVector(GDIint location, GDIsize count, const GDIfloat *value) = 0;
    
    virtual void setUniform4Int(GDIint location, GDIint v0, GDIint v1, GDIint v2, GDIint v3) = 0;
    
    virtual void setUniform4IntVector(GDIint location, GDIsize count, const int *value) = 0;
    
    virtual void
    setUniformMatrix2FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) = 0;
    
    virtual void
    setUniformMatrix3FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) = 0;
    
    virtual void
    setUniformMatrix4FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) = 0;
    
    
    [[nodiscard]] GDIint getGlslMajorVersion() const { return glslMajorVersion; };
    
    [[nodiscard]] GDIint getGlslMinorVersion() const { return glslMinorVersion; };
    
    [[nodiscard]] GDIint getIsGlslCore() const { return isGlslCore; };


protected:
    /**
     * @brief Major version of the GLSL language
     */
    GDIint glslMajorVersion{};
    /**
     * @brief Minor version of the GLSL language
     */
    GDIint glslMinorVersion{};
    /**
     * @brief Flag to indicate if the GLSL version is core or not
     */
    GDIint isGlslCore{};
};