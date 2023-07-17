#include "engine/core/renderer/shaders/ShaderManager.h"
#include "engine/resources/files/FileReader.h"
#include "engine/foundation/logger/Logger.h"

void ShaderManager::setBool(const std::string &name, bool value) {
    graphicsInterface.setUniform1Int(graphicsInterface.getUniformLocation(shaderProgram, name), (int) value);
}

void ShaderManager::setInt(const std::string &name, int value) {
    graphicsInterface.setUniform1Int(graphicsInterface.getUniformLocation(shaderProgram, name), value);
}

void ShaderManager::setFloat(const std::string &name, float value) {
    graphicsInterface.setUniform1Float(graphicsInterface.getUniformLocation(shaderProgram, name), value);
}

void ShaderManager::setVec2(const std::string &name, const glm::vec2 &value) {
    graphicsInterface.setUniform2FloatVector(graphicsInterface.getUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderManager::setVec2(const std::string &name, float x, float y) {
    graphicsInterface.setUniform2Float(graphicsInterface.getUniformLocation(shaderProgram, name), x, y);
}

void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) {
    graphicsInterface.setUniform3FloatVector(graphicsInterface.getUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderManager::setVec3(const std::string &name, float x, float y, float z) {
    graphicsInterface.setUniform3Float(graphicsInterface.getUniformLocation(shaderProgram, name), x, y, z);
}

void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) {
    graphicsInterface.setUniform4FloatVector(graphicsInterface.getUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderManager::setVec4(const std::string &name, float x, float y, float z, float w) {
    graphicsInterface.setUniform4Float(graphicsInterface.getUniformLocation(shaderProgram, name), x, y, z, w);
}

void ShaderManager::setMat2(const std::string &name, const glm::mat2 &mat) {
    graphicsInterface
            .setUniformMatrix2FloatVector(graphicsInterface.getUniformLocation(shaderProgram, name), 1, GL_FALSE,
                                          &mat[0][0]);
}

void ShaderManager::setMat3(const std::string &name, const glm::mat3 &mat) {
    graphicsInterface
            .setUniformMatrix3FloatVector(graphicsInterface.getUniformLocation(shaderProgram, name), 1, GL_FALSE,
                                          &mat[0][0]);
}

void ShaderManager::setMat4(const std::string &name, const glm::mat4 &mat) {
    graphicsInterface
            .setUniformMatrix4FloatVector(graphicsInterface.getUniformLocation(shaderProgram, name), 1, GL_FALSE,
                                          &mat[0][0]);
}

void ShaderManager::use() {
    graphicsInterface.useShaderProgram(shaderProgram);
}