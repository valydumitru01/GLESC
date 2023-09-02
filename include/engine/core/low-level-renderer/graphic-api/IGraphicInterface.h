/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>
#include <functional>
#include <any>
#include <SDL2/SDL.h>

// TODO: Make the types be defined by the graphic API
using GAPIbool = unsigned char;
using GAPIuint = unsigned int;
using GAPIfloat = float;
using GAPIint = int;
using GAPIsize = unsigned int;
using GAPIchar = char;

enum class GraphicsAPI {
    OPENGL [[maybe_unused]] = 0, VULKAN [[maybe_unused]]
};
/**
 * @brief This class is used to define the different texture filters that can be used
 * @details It contains the different types of filters that can be used for the textures.
 * All the filters are defined as enums, each enum starts with a different number to avoid
 * overlapping between the different enums.
 */
enum class GAPIValues {
    
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

class IGraphicInterface {
public:
    IGraphicInterface() = default;
    
    virtual ~IGraphicInterface() = default;
    
    [[nodiscard]] virtual GraphicsAPI getGraphicsAPI() const = 0;
    
    virtual void clear(const std::initializer_list<GAPIValues>& values) = 0;
    
    virtual void clearColor(GAPIfloat r, GAPIfloat g, GAPIfloat b, GAPIfloat a) = 0;
    
    virtual void setViewport(GAPIint width, GAPIint height) = 0;
    
    virtual void setViewport(GAPIint x, GAPIint y, GAPIint width, GAPIint height) = 0;
    
    virtual std::function<void(SDL_Window &)> getSwapBuffersFunc() = 0;
    
    virtual void createContext(SDL_Window &window, GAPIint w, GAPIint h, GAPIint x, GAPIint y) = 0;
    
    virtual void deleteContext() = 0;
    
    virtual void preWindowCreationInit() = 0;
    
    virtual void postWindowCreationInit() = 0;
    
    
    // ------------------------------------------------------------------------------
    // -------------------------------- Buffers -------------------------------------
    
    virtual void genBuffers(GAPIuint amount, GAPIuint &bufferID) = 0;
    
    virtual void bindBuffer(GAPIValues bufferType, GAPIuint buffer) = 0;
    
    virtual void unbindBuffer(GAPIValues bufferType) = 0;
    
    virtual void deleteBuffer(GAPIuint buffer) = 0;
    
    virtual void
    setBufferData(const std::any *data,
                  GAPIsize size,
                  GAPIuint buffer,
                  GAPIValues bufferType,
                  GAPIValues bufferUsage) = 0;
    
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
    virtual GAPIuint
    createTexture(SDL_Surface &surface,
                  GAPIValues minFilter,
                  GAPIValues magFilter,
                  GAPIValues wrapS,
                  GAPIValues wrapT) = 0;
    
    /**
     * @brief Create texture with default parameters
     * @details The default parameters are:
     * minFilter = LINEAR
     * magFilter = LINEAR
     * wrapS = REPEAT
     * wrapT = REPEAT
     * @param textureID
     */
    virtual GAPIuint createTexture(SDL_Surface &surface) = 0;
    
    virtual void bindTexture(GAPIuint textureID) = 0;
    
    virtual void deleteTexture(GAPIuint textureID) = 0;
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    
    
    virtual void useShaderProgram(GAPIuint shaderProgram) = 0;
    
    virtual GAPIuint loadAndCompileShader(GAPIValues shaderType, const std::string &shaderSource) = 0;
    
    virtual bool compilationOK(GAPIuint shaderID, GAPIchar *message) = 0;
    
    virtual GAPIuint createShaderProgram(GAPIuint vertexShaderID, GAPIuint fragmentShaderID) = 0;
    
    virtual bool linkOK(GAPIuint programID, GAPIchar *message) = 0;
    
    virtual void deleteShader(GAPIuint shaderID) = 0;
    
    
    // -------------------------------- Uniforms ------------------------------------
    
    virtual int getUniformLocation(GAPIuint program, const std::string &name) = 0;
    
    virtual void setUniform1Float(GAPIint location, GAPIfloat v0) = 0;
    
    virtual void setUniform1FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) = 0;
    
    virtual void setUniform1Int(GAPIint location, GAPIint v0) = 0;
    
    virtual void setUniform1IntVector(GAPIint location, GAPIsize count, const int *value) = 0;
    
    virtual void setUniform2Float(GAPIint location, GAPIfloat v0, GAPIfloat v1) = 0;
    
    virtual void setUniform2FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) = 0;
    
    virtual void setUniform2Int(GAPIint location, GAPIint v0, GAPIint v1) = 0;
    
    virtual void setUniform2IntVector(GAPIint location, GAPIsize count, const int *value) = 0;
    
    virtual void setUniform3Float(GAPIint location, GAPIfloat v0, GAPIfloat v1, GAPIfloat v2) = 0;
    
    virtual void setUniform3FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) = 0;
    
    virtual void setUniform3Int(GAPIint location, GAPIint v0, GAPIint v1, GAPIint v2) = 0;
    
    virtual void setUniform3IntVector(GAPIint location, GAPIsize count, const GAPIint *value) = 0;
    
    virtual void setUniform4Float(GAPIint location, GAPIfloat v0, GAPIfloat v1, GAPIfloat v2, GAPIfloat v3) = 0;
    
    virtual void setUniform4FloatVector(GAPIint location, GAPIsize count, const GAPIfloat *value) = 0;
    
    virtual void setUniform4Int(GAPIint location, GAPIint v0, GAPIint v1, GAPIint v2, GAPIint v3) = 0;
    
    virtual void setUniform4IntVector(GAPIint location, GAPIsize count, const int *value) = 0;
    
    virtual void
    setUniformMatrix2FloatVector(GAPIint location, GAPIsize count, GAPIbool transpose, const GAPIfloat *value) = 0;
    
    virtual void
    setUniformMatrix3FloatVector(GAPIint location, GAPIsize count, GAPIbool transpose, const GAPIfloat *value) = 0;
    
    virtual void
    setUniformMatrix4FloatVector(GAPIint location, GAPIsize count, GAPIbool transpose, const GAPIfloat *value) = 0;

};


#if GLESC_RENDER_API == OpenGLAPI
    #include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/OpenGLAPI.h"
#elif GLESC_RENDER_API == VulkanAPI
    #include "engine/core/low-level-renderer/graphic-api/concrete-apis/vulkan/VulkanAPI.h"
#elif GLESC_RENDER_API == DirectXAPI
    #include "engine/core/low-level-renderer/graphic-api/concrete-apis/directx/DirectXAPI.h"
#endif