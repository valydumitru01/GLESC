#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <functional>

typedef unsigned char GDIbool;
typedef unsigned int GDIuint;
typedef float GDIfloat;
typedef int GDIint;
typedef unsigned int GDIsize;
enum class GraphicsAPI {
    OPENGL [[maybe_unused]] = 0, VULKAN [[maybe_unused]]
};

/**
 * @brief This class is used to define the different texture filters that can be used
 * @details It contains the different types of filters that can be used for the textures.
 * All the filters are defined as enums, each enum starts with a different number to avoid
 * overlapping between the different enums.
 */
class TextureFilter {
public:
    enum class MinFilter {
        Nearest [[maybe_unused]] = 0,
        Linear [[maybe_unused]],
        NearestMipmapNearest [[maybe_unused]],
        LinearMipmapNearest [[maybe_unused]],
        NearestMipmapLinear [[maybe_unused]],
        LinearMipmapLinear [[maybe_unused]]
    };
    enum class MagFilter {
        Nearest [[maybe_unused]] = 100, Linear [[maybe_unused]]
    };
    enum class WrapMode {
        Repeat [[maybe_unused]] = 200,
        MirroredRepeat [[maybe_unused]],
        ClampToEdge [[maybe_unused]],
        ClampToBorder [[maybe_unused]]
    };
};

class Buffers {
public:
    enum class Type {
        Vertex [[maybe_unused]] = 0, Index [[maybe_unused]]
    };
    enum class Usage {
        Static [[maybe_unused]] = 0, Dynamic [[maybe_unused]], Stream [[maybe_unused]]
    };
};

class GraphicsInterface {
public:
    GraphicsInterface() = default;
    
    [[nodiscard]] virtual GraphicsAPI getGraphicsAPI() const = 0;
    
    virtual void genBuffers(GDIuint amount, GDIint &bufferID) = 0;
    
    virtual void bindBuffer(Buffers::Type bufferType, GDIuint buffer) = 0;
    
    virtual void unbindBuffer(GDIint bufferID) = 0;
    
    virtual void deleteBuffer(GDIuint buffer) = 0;
    
    virtual void setBufferData(const void *data, GDIsize size, GDIuint buffer, Buffers::Type bufferType,
                               Buffers::Usage bufferUsage) = 0;
    
    /**
     * @brief Set the Attributes for the Graphics Device Interface
     * @details This is where the configuration attributes for the GDI are set, such as the version,
     * the profile, the context flags, etc.
     */
    virtual void setAttributes() = 0;
    
    virtual void swapBuffers() = 0;
    
    virtual void setViewport(int x, int y, int width, int height) = 0;
    
    virtual void setViewport(int width, int height) = 0;
    
    virtual void setViewport() = 0;
    
    virtual void useShader(const std::string &shaderName) = 0;
    
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
    createTexture(SDL_Surface &surface, TextureFilter::MinFilter minFilter, TextureFilter::MagFilter magFilter,
                  TextureFilter::WrapMode wrapS, TextureFilter::WrapMode wrapT) = 0;
    
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
    
    virtual void deleteTexture(GDIuint textureID) = 0;
    
    virtual void bindTexture(GDIuint textureID) = 0;
    
    virtual std::function <void(SDL_Window &)> getSwapBuffersFunc() = 0;
    
    virtual void createContext(SDL_Window &window, GDIint w, GDIint h, GDIint x, GDIint y) = 0;
    
    virtual void deleteContext() = 0;
    
    
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    
    virtual int getUniformLocation(GDIint program, const std::string &name) = 0;
    
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
    
    virtual void useShaderProgram(int shaderProgram) = 0;
    
    
    virtual ~GraphicsInterface() = default;

private:
};