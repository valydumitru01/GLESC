#pragma once

#include "engine/core/graphics-device-interface/GraphicsInterface.h"

class OpenGLGDI : public GraphicsInterface {
    
    explicit OpenGLGDI();
    
    
    [[nodiscard]] GraphicsAPI getGraphicsAPI() const override { return GraphicsAPI::OPENGL; }
    
    /**
     * @brief Attributes that configure OpenGL
     * @details This is where the configuration attributes for the GDI are set, such as the OpenGL version,
     * @see https://wiki.libsdl.org/SDL_GLattr
     */
    void setAttributes() override;
    
    void setViewport(int width, int height,int x  = 0, int y  = 0) override;
    
    void setViewport(int width, int height) override;
    
    void setViewport() override;
    
    void useShader(const std::string &shaderName) override;
    /**
     * @brief Create a texture from an SDL_Surface
     * @details This function creates a texture from an SDL_Surface. It also sets the texture parameters
     * @param surface
     * @param minFilter
     * @param magFilter
     * @param wrapS
     * @param wrapT
     * @return
     */
    GDIuint createTexture(SDL_Surface &surface,
                          TextureFilter::MinFilter minFilter = TextureFilter::MinFilter::LINEAR,
                          TextureFilter::MagFilter magFilter = TextureFilter::MagFilter::LINEAR,
                          TextureFilter::WrapMode wrapS = TextureFilter::WrapMode::REPEAT,
                          TextureFilter::WrapMode wrapT = TextureFilter::WrapMode::REPEAT);
    
    void bindTexture(GDIuint textureID) override;
    
    std::function<void(SDL_Window*)> getSwapBuffersFunc() override;
    
    std::function<void(SDL_Window&, GDIint, GDIint, GDIint, GDIint )> getCreateContextFunc() override;
    // Shaders
    GLint getUniformLocation(GLint program, const std::string &name) override;
    
    void setUniform1Float(GLint location, GLfloat v0) override;
    
    void setUniform1FloatVector(GLint location, GLsizei count, const GLfloat *value) override;
    
    void setUniform1Int(GLint location, GLint v0) override;
    
    void setUniform1IntVector(GLint location, GLsizei count, const GLint *value) override;
    
    void setUniform2Float(GLint location, GLfloat v0, GLfloat v1) override;
    
    void setUniform2FloatVector(GLint location, GLsizei count, const GLfloat *value) override;
    
    void setUniform2Int(GLint location, GLint v0, GLint v1) override;
    
    void setUniform2IntVector(GLint location, GLsizei count, const GLint *value) override;
    
    void setUniform3Float(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) override;
    
    void setUniform3FloatVector(GLint location, GLsizei count, const GLfloat *value) override;
    
    void setUniform3Int(GLint location, GLint v0, GLint v1, GLint v2) override;
    
    void setUniform3IntVector(GLint location, GLsizei count, const GLint *value) override;
    
    void setUniform4Float(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) override;
    
    void setUniform4FloatVector(GLint location, GLsizei count, const GLfloat *value) override;
    
    void setUniform4Int(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) override;
    
    void setUniform4IntVector(GLint location, GLsizei count, const GLint *value) override;
    
    void
    setUniformMatrix2FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    
    void
    setUniformMatrix3FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    
    void
    setUniformMatrix4FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    
    void useShaderProgram(int shaderProgram) override;


private:
    
    virtual void createContext(SDL_Window& window, GDIint w, GDIint h, GDIint x, GDIint y) = 0;
    
    static void setGlAttribute(SDL_GLattr attrib, int val);
    
    /**
     * @brief Converts a TextureFilter enum to its OpenGL equivalent
     * @details This function converts a TextureFilter enum to its OpenGL equivalent, returns
     * GLint because glTexParameter takes a GLint as a parameter.
     * @tparam T enum type within TextureFilter class
     * @param value
     * @return
     */
    template <typename T>
    GLint textureFilterToGl(T value);
    
    SDL_GLContext context;
    
    
    
};

#include "engine/core/exceptions/plat-indep/GDIException.h"

template <typename T>
GLint OpenGLGDI::textureFilterToGl(T value) {
    // Check if T is a TextureFilter enum
    static_assert(std::is_enum<T>::value, "T must be an enum");
    // Check if T is a member of TextureFilter
    static_assert(std::is_same<T, TextureFilter::MinFilter>::value ||
                  std::is_same<T, TextureFilter::MagFilter>::value ||
                  std::is_same<T, TextureFilter::WrapMode>::value,
                  "T must be a member of TextureFilter");
    switch (static_cast<int>(value)) {
        case static_cast<int>(TextureFilter::MinFilter::NEAREST):
            return GL_NEAREST;
        case static_cast<int>(TextureFilter::MinFilter::LINEAR):
            return GL_LINEAR;
        case static_cast<int>(TextureFilter::MinFilter::NEAREST_MIPMAP_NEAREST):
            return GL_NEAREST_MIPMAP_NEAREST;
        case static_cast<int>(TextureFilter::MinFilter::LINEAR_MIPMAP_NEAREST):
            return GL_LINEAR_MIPMAP_NEAREST;
        case static_cast<int>(TextureFilter::MinFilter::NEAREST_MIPMAP_LINEAR):
            return GL_NEAREST_MIPMAP_LINEAR;
        case static_cast<int>(TextureFilter::MinFilter::LINEAR_MIPMAP_LINEAR):
            return GL_LINEAR_MIPMAP_LINEAR;
        case static_cast<int>(TextureFilter::MagFilter::NEAREST):
            return GL_NEAREST;
        case static_cast<int>(TextureFilter::MagFilter::LINEAR):
            return GL_LINEAR;
        case static_cast<int>(TextureFilter::WrapMode::REPEAT):
            return GL_REPEAT;
        case static_cast<int>(TextureFilter::WrapMode::MIRRORED_REPEAT):
            return GL_MIRRORED_REPEAT;
        case static_cast<int>(TextureFilter::WrapMode::CLAMP_TO_EDGE):
            return GL_CLAMP_TO_EDGE;
        case static_cast<int>(TextureFilter::WrapMode::CLAMP_TO_BORDER):
            return GL_CLAMP_TO_BORDER;
        default:
            throw GDIException("Texture filter not supported");
    }
}