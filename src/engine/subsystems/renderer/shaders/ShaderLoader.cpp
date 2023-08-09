/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/shaders/ShaderLoader.h"
#include "engine/core/logger/Logger.h"
#include "engine/res-mng/files/FileManager.h"
#include "engine/core/exceptions/subsystems/ShaderException.h"

ShaderLoader::ShaderLoader(GraphicInterface &graphicInterface) :
        vertexShader(0), fragmentShader(0), shaderProgram(0), graphicInterface(graphicInterface) {
}

GDIint ShaderLoader::loadShaders() {
    std::string vertexPath = VERT_SHADER;
    vertexShaderSource = FileManager::readFile(vertexPath);
    Logger::get().success("Shader file read successfully: " + vertexPath);
    
    std::string fragmentPath = FRAG_SHADER;
    fragmentShaderSource = FileManager::readFile(fragmentPath);
    Logger::get().success("Shader file read successfully: " + fragmentPath);
    
    std::string glslCoreStr = graphicInterface.getIsGlslCore() ? "core" : "";
    
    std::string glslVersionStr = "#version " + std::to_string(graphicInterface.getGlslMajorVersion()) + "" +
                                 std::to_string(graphicInterface.getGlslMinorVersion()) + " " + glslCoreStr + "\n";
    
    // Setting the glsl version to the shader source
    vertexShaderSource = glslVersionStr + vertexShaderSource;
    fragmentShaderSource = glslVersionStr + fragmentShaderSource;
    
    Logger::get().info("Shader file content: \n" + vertexShaderSource);
    Logger::get().info("Shader file content: \n" + fragmentShaderSource);
    
    loadVertexShader();
    Logger::get().success("Vertex shader loaded successfully");
    loadFragmentShader();
    Logger::get().success("Fragment shader loaded successfully");
    createShaderProgram();
    Logger::get().success("Shader program created successfully");
    
    clean();
    return shaderProgram;
}

void ShaderLoader::loadVertexShader() {
    vertexShader = graphicInterface.loadAndCompileShader(GDIValues::ShaderTypeVertex, vertexShaderSource);
    shaderNamesMap.emplace(vertexShader, "VERTEX");
    handleErrorsCompilation(vertexShader);
}

void ShaderLoader::loadFragmentShader() {
    fragmentShader = graphicInterface.loadAndCompileShader(GDIValues::ShaderTypeFragment, fragmentShaderSource);
    shaderNamesMap.emplace(fragmentShader, "FRAGMENT");
    handleErrorsCompilation(fragmentShader);
}

void ShaderLoader::createShaderProgram() {
    shaderProgram = graphicInterface.createShaderProgram(vertexShader, fragmentShader);
    handleErrorsLinking();
}

void ShaderLoader::clean() const {
    std::destroy(shaderNamesMap.begin(), shaderNamesMap.end()); //Delete pointers from map
    graphicInterface.deleteShader(vertexShader);
    graphicInterface.deleteShader(fragmentShader);
}

void ShaderLoader::handleErrorsLinking() {
    char *infoLog = new char[512];
    if (!graphicInterface.linkOK(shaderProgram, infoLog)) {
        throw ShaderLinkingException(std::string(infoLog));
    }
    delete[] infoLog;
}

void ShaderLoader::handleErrorsCompilation(unsigned int shaderType) {
    char *infoLog = new char[512];
    if (!graphicInterface.compilationOK(shaderType, infoLog)) {
        throw ShaderCompilationException(std::string(shaderNamesMap.at(shaderType)), infoLog);
    }
    delete[] infoLog;
}

