#include "engine/core/renderer/shaders/ShaderManager.h"
#include "engine/resources/files/FileReader.h"
#include "engine/foundation/logger/Logger.h"

void ShaderManager::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int) value);
}

void ShaderManager::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderManager::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderManager::setVec2(const std::string &name, const glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec2(const std::string &name, float x, float y) {
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}

void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    
}

void ShaderManager::setVec3(const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
    
}

void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    
}

void ShaderManager::setVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
    
}

void ShaderManager::setMat2(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    
}

void ShaderManager::setMat3(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    
}

void ShaderManager::setMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    
}

void ShaderManager::use() {
    glUseProgram(shaderProgram);
}

