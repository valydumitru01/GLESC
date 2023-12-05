/**************************************************************************************************
 * @file   Shader.cpp
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/subsystems/renderer/shaders/Shader.h"
#include "engine/core/low-level-renderer/shader/ShaderLoader.h"

using namespace GLESC;

Shader::Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) :
        shaderProgram(ShaderLoader::loadShader(vertexShaderSource, fragmentShaderSource)) {
}


Shader::Shader(const std::string &fileName) :
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

UniformSetter Shader::setUniform(const std::string &name) const {
    return {shaderProgram, name};
}

