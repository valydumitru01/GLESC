/**************************************************************************************************
 * @file   Shader.cpp
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/shaders/Shader.h"
#include "engine/subsystems/renderer/shaders/UniformHandler.h"
#include "engine/subsystems/renderer/shaders/ShaderLoader.h"

using namespace GLESC;

Shader::Shader(const std::string& fileName) :
        shaderProgram(ShaderLoader::loadShader(fileName)) {
}

Shader::~Shader() {
    gapi.deleteShader(shaderProgram);
}

void Shader::bind() const {
    gapi.useShaderProgram(shaderProgram);
}

void Shader::unbind() const {
    gapi.useShaderProgram(0);
}


void Shader::setBool(const std::string &name, bool value) {
    UniformHandler::setBool(shaderProgram, name, value);
}

void Shader::setInt(const std::string &name, int value) {
    UniformHandler::setInt(shaderProgram, name, value);
}


void Shader::setFloat(const std::string &name, float value) {
    UniformHandler::setFloat(shaderProgram, name, value);
}


void Shader::setVec2(const std::string &name, const Vec2 &value) {
    UniformHandler::setVec2(shaderProgram, name, value);
}

[[maybe_unused]] void Shader::setVec2(const std::string &name, float x, float y) {
    UniformHandler::setVec2(shaderProgram, name, x, y);
}

void Shader::setVec3(const std::string &name, const Vec3 &value) {
    UniformHandler::setVec3(shaderProgram, name, value);
}


[[maybe_unused]] void Shader::setVec3(const std::string &name, float x, float y, float z) {
    UniformHandler::setVec3(shaderProgram, name, x, y, z);
}

[[maybe_unused]] void Shader::setVec4(const std::string &name, const Vec4 &value) {
    UniformHandler::setVec4(shaderProgram, name, value);
}


[[maybe_unused]] void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    UniformHandler::setVec4(shaderProgram, name, x, y, z, w);
}


[[maybe_unused]] void Shader::setMat2(const std::string &name, const Matrix2 &mat) {
    UniformHandler::setMat2(shaderProgram, name, mat);
}

[[maybe_unused]] void Shader::setMat3(const std::string &name, const Matrix3 &mat) {
    UniformHandler::setMat3(shaderProgram, name, mat);
}

[[maybe_unused]] void Shader::setMat4(const std::string &name, const Matrix4 &mat) {
    UniformHandler::setMat4(shaderProgram, name, mat);
}