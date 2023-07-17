#pragma once

#include "glm/glm.hpp"
#include "engine/plat-independence/window/WindowManager.h"
#include <string>
#include <memory>

typedef unsigned char GDIBoolean;

class GraphicsInterface {
public:
    virtual void init(std::shared_ptr <WindowManager> window) = 0;
    
    /**
     * @brief Set the Attributes for the Graphics Device Interface
     * @details This is where the configuration attributes for the GDI are set, such as the version,
     * the profile, the context flags, etc.
     */
    virtual void setAttributes() = 0;
    
    virtual void update() = 0;
    
    virtual void swapBuffers() = 0;
    
    virtual void setViewport(int x, int y, int width, int height) = 0;
    
    virtual void setViewport(int width, int height) = 0;
    
    virtual void setViewport() = 0;
    
    virtual void useShader(const std::string &shaderName) = 0;
    
    virtual void bindMesh(const std::string &meshName) = 0;
    
    virtual int loadTexture(const std::string &texturePath) = 0;
    
    virtual void bindTexture(int textureID) = 0;
    
    // Shaders
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
    virtual void createContext() = 0;
};