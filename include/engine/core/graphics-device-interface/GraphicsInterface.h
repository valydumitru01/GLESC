#pragma once

#include <functional>
#include <string>
#include <memory>
#include "engine/core/window/WindowManager.h"

typedef unsigned char GDIBoolean;
typedef unsigned int GDIuint;
typedef int GDIint;
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
        NEAREST [[maybe_unused]] = 0,
        LINEAR [[maybe_unused]],
        NEAREST_MIPMAP_NEAREST [[maybe_unused]],
        LINEAR_MIPMAP_NEAREST [[maybe_unused]],
        NEAREST_MIPMAP_LINEAR [[maybe_unused]],
        LINEAR_MIPMAP_LINEAR [[maybe_unused]]
    };
    enum class MagFilter {
        NEAREST [[maybe_unused]] = 10, LINEAR [[maybe_unused]]
    };
    enum class WrapMode {
        REPEAT [[maybe_unused]] = 100,
        MIRRORED_REPEAT [[maybe_unused]],
        CLAMP_TO_EDGE [[maybe_unused]],
        CLAMP_TO_BORDER [[maybe_unused]]
    };
};

class GraphicsInterface {
public:
    GraphicsInterface();
    
    virtual void init() = 0;
    
    virtual GraphicsAPI getGraphicsAPI() const = 0;
    
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
    
    virtual GDIuint
    createTexture(SDL_Surface &surface, TextureFilter::MinFilter minFilter = TextureFilter::MinFilter::LINEAR,
                  TextureFilter::MagFilter magFilter = TextureFilter::MagFilter::LINEAR,
                  TextureFilter::WrapMode wrapS = TextureFilter::WrapMode::REPEAT,
                  TextureFilter::WrapMode wrapT = TextureFilter::WrapMode::REPEAT) = 0;
    
    virtual void deleteTexture(GDIuint textureID) = 0;
    
    virtual void bindTexture(GDIuint textureID) = 0;
    
    virtual std::function <void(SDL_Window *)> getSwapBuffersFunc() = 0;
    
    virtual std::function<void(SDL_Window&, GDIint, GDIint, GDIint, GDIint )> getCreateContextFunc() = 0;
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    virtual int getUniformLocation(int program, const std::string &name) = 0;
    
    virtual void setUniform1Float(int location, float v0) = 0;
    
    virtual void setUniform1FloatVector(int location, int count, const float *value) = 0;
    
    virtual void setUniform1Int(int location, int v0) = 0;
    
    virtual void setUniform1IntVector(int location, int count, const int *value) = 0;
    
    virtual void setUniform2Float(int location, float v0, float v1) = 0;
    
    virtual void setUniform2FloatVector(int location, int count, const float *value) = 0;
    
    virtual void setUniform2Int(int location, int v0, int v1) = 0;
    
    virtual void setUniform2IntVector(int location, int count, const int *value) = 0;
    
    virtual void setUniform3Float(int location, float v0, float v1, float v2) = 0;
    
    virtual void setUniform3FloatVector(int location, int count, const float *value) = 0;
    
    virtual void setUniform3Int(int location, int v0, int v1, int v2) = 0;
    
    virtual void setUniform3IntVector(int location, int count, const int *value) = 0;
    
    virtual void setUniform4Float(int location, float v0, float v1, float v2, float v3) = 0;
    
    virtual void setUniform4FloatVector(int location, int count, const float *value) = 0;
    
    virtual void setUniform4Int(int location, int v0, int v1, int v2, int v3) = 0;
    
    virtual void setUniform4IntVector(int location, int count, const int *value) = 0;
    
    virtual void setUniformMatrix2FloatVector(int location, int count, GDIBoolean transpose, const float *value) = 0;
    
    virtual void setUniformMatrix3FloatVector(int location, int count, GDIBoolean transpose, const float *value) = 0;
    
    virtual void setUniformMatrix4FloatVector(int location, int count, GDIBoolean transpose, const float *value) = 0;
    
    virtual void useShaderProgram(int shaderProgram) = 0;
    
    virtual int getShaderProgram() = 0;
    
    virtual ~GraphicsInterface() = default;

private:
    virtual void createContext(SDL_Window& window, GDIint w, GDIint h, GDIint x, GDIint y) = 0;
};