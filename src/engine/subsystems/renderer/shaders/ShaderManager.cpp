/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/shaders/ShaderManager.h"
#include "engine/res-mng/files/FileManager.h"
#include "engine/core/logger/Logger.h"


ShaderManager::ShaderManager(GraphicInterface &graphicInterfaceParam) : graphicInterface(graphicInterfaceParam) {
    ShaderLoader shaderLoader(graphicInterface);
    shaderProgram = shaderLoader.loadShaders();
}

void ShaderManager::setBool(const std::string &name, bool value) {
    graphicInterface.setUniform1Int(graphicInterface.getUniformLocation(shaderProgram, name), (int) value);
}

void ShaderManager::setInt(const std::string &name, int value) {
    graphicInterface.setUniform1Int(graphicInterface.getUniformLocation(shaderProgram, name), value);
}

void ShaderManager::setFloat(const std::string &name, float value) {
    graphicInterface.setUniform1Float(graphicInterface.getUniformLocation(shaderProgram, name), value);
}

void ShaderManager::setVec2(const std::string &name, const glm::vec2 &value) {
    graphicInterface.setUniform2FloatVector(graphicInterface.getUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderManager::setVec2(const std::string &name, float x, float y) {
    graphicInterface.setUniform2Float(graphicInterface.getUniformLocation(shaderProgram, name), x, y);
}

void ShaderManager::setVec3(const std::string &name, const glm::vec3 &value) {
    graphicInterface.setUniform3FloatVector(graphicInterface.getUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderManager::setVec3(const std::string &name, float x, float y, float z) {
    graphicInterface.setUniform3Float(graphicInterface.getUniformLocation(shaderProgram, name), x, y, z);
}

void ShaderManager::setVec4(const std::string &name, const glm::vec4 &value) {
    graphicInterface.setUniform4FloatVector(graphicInterface.getUniformLocation(shaderProgram, name), 1, &value[0]);
}

void ShaderManager::setVec4(const std::string &name, float x, float y, float z, float w) {
    graphicInterface.setUniform4Float(graphicInterface.getUniformLocation(shaderProgram, name), x, y, z, w);
}

void ShaderManager::setMat2(const std::string &name, const glm::mat2 &mat) {
    graphicInterface.setUniformMatrix2FloatVector(graphicInterface.getUniformLocation(shaderProgram, name), 1, GL_FALSE,
                                                  &mat[0][0]);
}

void ShaderManager::setMat3(const std::string &name, const glm::mat3 &mat) {
    graphicInterface.setUniformMatrix3FloatVector(graphicInterface.getUniformLocation(shaderProgram, name), 1, GL_FALSE,
                                                  &mat[0][0]);
}

void ShaderManager::setMat4(const std::string &name, const glm::mat4 &mat) {
    graphicInterface.setUniformMatrix4FloatVector(graphicInterface.getUniformLocation(shaderProgram, name), 1, GL_FALSE,
                                                  &mat[0][0]);
}

void ShaderManager::use() {
    graphicInterface.useShaderProgram(shaderProgram);
}