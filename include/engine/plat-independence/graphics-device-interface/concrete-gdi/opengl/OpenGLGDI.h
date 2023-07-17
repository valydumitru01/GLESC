#pragma once

#include "engine/plat-independence/graphics-device-interface/GraphicsInterface.h"

class OpenGLGDI : public GraphicsInterface {
    void init(std::shared_ptr <WindowManager> window) override;
    
    /**
     * @brief Attributes that configure OpenGL
     * @details This is where the configuration attributes for the GDI are set, such as the OpenGL version,
     * @see https://wiki.libsdl.org/SDL_GLattr
     */
    void setAttributes() override;
    
    void update() override;
    
    void swapBuffers() override;
    
    void setViewport(int x, int y, int width, int height) override;
    
    void setViewport(int width, int height) override;
    
    void setViewport() override;
    
    void useShader(const std::string &shaderName) override;
    
    void bindMesh(const std::string &meshName) override;
    
    int loadTexture(const std::string &texturePath) override;
    
    void bindTexture(int textureID) override;
    
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
    
    void setUniformMatrix2FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    
    void setUniformMatrix3FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    
    void setUniformMatrix4FloatVector(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) override;
    
    void useShaderProgram(int shaderProgram) override;


private:
    
    void createContext() override;
    
    static void setGlAttribute(SDL_GLattr attrib, int val);
    
    SDL_GLContext context;
    
    std::shared_ptr <SDL_Window> window;
};