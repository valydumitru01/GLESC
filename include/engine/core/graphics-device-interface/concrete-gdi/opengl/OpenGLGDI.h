#pragma once

#include "engine/core/graphics-device-interface/GraphicsInterface.h"
#include <SDL2/SDL.h>
#include <functional>

class OpenGLGDI : public GraphicsInterface {
    
    explicit OpenGLGDI();
    
    
    [[nodiscard]] GraphicsAPI getGraphicsAPI() const override { return GraphicsAPI::OPENGL; }
    
    /**
     * @brief Attributes that configure OpenGL
     * @details This is where the configuration attributes for the GDI are set, such as the OpenGL version,
     * @see https://wiki.libsdl.org/SDL_GLattr
     */
    void setAttributes() override;
    
    void setViewport(int x, int y, int width, int height) override;
    
    void setViewport(int width, int height) override;

public:
    void deleteTexture(GDIuint textureID) override;
    
    void deleteContext() override;
    
    void setViewport() override;
    
    void useShader(const std::string &shaderName) override;
    
    GDIuint createTexture(SDL_Surface &surface, TextureFilter::MinFilter minFilter, TextureFilter::MagFilter magFilter,
                          TextureFilter::WrapMode wrapS, TextureFilter::WrapMode wrapT) override;
    
    GDIuint createTexture(SDL_Surface &surface) override;
    
    void bindTexture(GDIuint textureID) override;
    
    std::function <void(SDL_Window &)> getSwapBuffersFunc() override;
    
    
    // Shaders
    GDIint getUniformLocation(GDIint program, const std::string &name) override;
    
    void setUniform1Float(GDIint location, GDIfloat v0) override;
    
    void setUniform1FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform1Int(GDIint location, GDIint v0) override;
    
    void setUniform1IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void setUniform2Float(GDIint location, GDIfloat v0, GDIfloat v1) override;
    
    void setUniform2FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform2Int(GDIint location, GDIint v0, GDIint v1) override;
    
    void setUniform2IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void setUniform3Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2) override;
    
    void setUniform3FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform3Int(GDIint location, GDIint v0, GDIint v1, GDIint v2) override;
    
    void setUniform3IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void setUniform4Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2, GDIfloat v3) override;
    
    void setUniform4FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform4Int(GDIint location, GDIint v0, GDIint v1, GDIint v2, GDIint v3) override;
    
    void setUniform4IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void
    setUniformMatrix2FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) override;
    
    void
    setUniformMatrix3FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) override;
    
    void
    setUniformMatrix4FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) override;
    
    void useShaderProgram(int shaderProgram) override;


private:
    
    virtual void createContext(SDL_Window &window, GDIint w, GDIint h, GDIint x, GDIint y) = 0;
    
    static void setGlAttribute(SDL_GLattr attrib, int val);
    
    /**
     * @brief Converts a TextureFilter enum to its OpenGL equivalent
     * @details This function converts a TextureFilter enum to its OpenGL equivalent, returns
     * GDIint because glTexParameter takes a GDIint as a parameter.
     * @tparam T enum type within TextureFilter class
     * @param value
     * @return
     */
    template <typename T>
    GDIint textureFilterToGl(T value);
    
    SDL_GLContext context;
    
    
};

#include "engine/core/exceptions/plat-indep/GDIException.h"
#include <GL/glew.h>

template <typename T>
GDIint OpenGLGDI::textureFilterToGl(T value) {
    // Check if T is a TextureFilter enum
    static_assert(std::is_enum <T>::value, "T must be an enum");
    // Check if T is a member of TextureFilter
    static_assert(
            std::is_same <T, TextureFilter::MinFilter>::value || std::is_same <T, TextureFilter::MagFilter>::value ||
            std::is_same <T, TextureFilter::WrapMode>::value, "T must be a member of TextureFilter");
    switch (static_cast<int>(value)) {
        case static_cast<int>(TextureFilter::MinFilter::Nearest):
            return GL_NEAREST;
        case static_cast<int>(TextureFilter::MinFilter::Linear):
            return GL_LINEAR;
        case static_cast<int>(TextureFilter::MinFilter::NearestMipmapNearest):
            return GL_NEAREST_MIPMAP_NEAREST;
        case static_cast<int>(TextureFilter::MinFilter::LinearMipmapNearest):
            return GL_LINEAR_MIPMAP_NEAREST;
        case static_cast<int>(TextureFilter::MinFilter::NearestMipmapLinear):
            return GL_NEAREST_MIPMAP_LINEAR;
        case static_cast<int>(TextureFilter::MinFilter::LinearMipmapLinear):
            return GL_LINEAR_MIPMAP_LINEAR;
        case static_cast<int>(TextureFilter::MagFilter::Nearest):
            return GL_NEAREST;
        case static_cast<int>(TextureFilter::MagFilter::Linear):
            return GL_LINEAR;
        case static_cast<int>(TextureFilter::WrapMode::Repeat):
            return GL_REPEAT;
        case static_cast<int>(TextureFilter::WrapMode::MirroredRepeat):
            return GL_MIRRORED_REPEAT;
        case static_cast<int>(TextureFilter::WrapMode::ClampToEdge):
            return GL_CLAMP_TO_EDGE;
        case static_cast<int>(TextureFilter::WrapMode::ClampToBorder):
            return GL_CLAMP_TO_BORDER;
        default:
            throw GDIException("Texture filter not supported");
    }
}