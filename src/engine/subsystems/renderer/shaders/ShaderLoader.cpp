/**************************************************************************************************
 * @file   ShaderLoader.cpp
 * @author Valentin Dumitru
 * @date   2023-11-08
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/core/exceptions/subsystems/ShaderException.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/low-level-renderer/asserts/ShaderAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/res-mng/files/FileManager.h"
#include "engine/core/low-level-renderer/shader/ShaderLoader.h"

GAPI::UInt ShaderLoader::loadShader(const std::string& fileName) {
    std::string shaderPath = std::string(SHADER_PATH) + "/" + fileName;
    std::string shaderSource = FileManager::readFile(shaderPath);
    GLESC::Logger::get().success("Shader file read successfully: " + shaderPath);
    
    extractShaderCode(shaderSource, vertexShaderSource, fragmentShaderSource);
    prependGLSLVersion(vertexShaderSource, fragmentShaderSource);
    
    GLESC::Logger::get().info("Vertex Shader:\n" + vertexShaderSource);
    GLESC::Logger::get().info("Fragment Shader:\n" + fragmentShaderSource);
    
    vertexShader=loadVertexShader(vertexShaderSource);
    GLESC::Logger::get().success("Vertex shader loaded successfully");
    fragmentShader=loadFragmentShader(fragmentShaderSource);
    GLESC::Logger::get().success("Fragment shader loaded successfully");
    GAPI::UInt shaderProgram = createShaderProgram();
    GLESC::Logger::get().success("Shader program created successfully");
    
    clean();
    return shaderProgram;
}

GAPI::UInt ShaderLoader::loadShader(const std::string& vertexShaderSourceParam,
                                    const std::string& fragmentShaderSourceParam) {
    vertexShaderSource = vertexShaderSourceParam;
    fragmentShaderSource = fragmentShaderSourceParam;
    prependGLSLVersion(vertexShaderSource, fragmentShaderSource);
    
    GLESC::Logger::get().info("Vertex Shader:\n" + vertexShaderSource);
    GLESC::Logger::get().info("Fragment Shader:\n" + fragmentShaderSource);
    
    vertexShader=loadVertexShader(vertexShaderSource);
    GLESC::Logger::get().success("Vertex shader loaded successfully");
    fragmentShader=loadFragmentShader(fragmentShaderSource);
    GLESC::Logger::get().success("Fragment shader loaded successfully");
    GAPI::UInt shaderProgram = createShaderProgram();
    GLESC::Logger::get().success("Shader program created successfully");
    
    clean();
    return shaderProgram;
}

void ShaderLoader::extractShaderCode(const std::string& shaderSource,
                                     std::string& vertexCode,
                                     std::string& fragmentCode) {
    const char* tokenVertex = "#shader vertex";
    const char* tokenFragment = "#shader fragment";
    
    size_t vertexPos = shaderSource.find(tokenVertex);
    size_t fragmentPos = shaderSource.find(tokenFragment);
    
    validateShaderTokens(vertexPos, fragmentPos);
    
    // Extract shader codes
    if (vertexPos < fragmentPos) {
        vertexCode = shaderSource.substr(vertexPos + strlen(tokenVertex),
                                         fragmentPos - vertexPos - strlen(tokenVertex));
        fragmentCode = shaderSource.substr(fragmentPos + strlen(tokenFragment));
    } else {
        fragmentCode = shaderSource.substr(fragmentPos + strlen(tokenFragment),
                                           vertexPos - fragmentPos - strlen(tokenFragment));
        vertexCode = shaderSource.substr(vertexPos + strlen(tokenVertex));
    }
    
    validateShaderCodes(vertexCode, fragmentCode);
}

void ShaderLoader::prependGLSLVersion(std::string& vertexCode, std::string& fragmentCode) {
    std::string glslVersionStr = getGLSLVersionString();
    vertexShaderSource = glslVersionStr + vertexCode;
    fragmentShaderSource = glslVersionStr + fragmentCode;
}

std::string ShaderLoader::getGLSLVersionString() {
#if GLESC_GLSL_CORE_PROFILE == true
    std::string glslCoreStr = "core";
#else
    std::string glslCoreStr = "";
#endif
    // check if minor version occupies 2 digits
#if GLESC_GLSL_MINOR_VERSION < 10
    std::string glslMinorVersionStr = std::to_string(GLESC_GLSL_MINOR_VERSION) + "0";
#else
    std::string glslMinorVersionStr = std::to_string(GLESC_GLSL_MINOR_VERSION);
#endif
    
    return "#version " + std::to_string(GLESC_GLSL_MAJOR_VERSION) +
            glslMinorVersionStr + " " + glslCoreStr + "\n";
}

void ShaderLoader::validateShaderTokens(size_t vertexPos, size_t fragmentPos) {
    if (vertexPos == std::string::npos) {
        D_ASSERT_SHADER_TOKEN_FOUND("vertex");
    }
    
    if (fragmentPos == std::string::npos) {
        D_ASSERT_SHADER_TOKEN_FOUND("fragment");
    }
}

void ShaderLoader::validateShaderCodes(const std::string& vertexCode, const std::string& fragmentCode) {
    if (vertexCode.empty()) {
        D_ASSERT_SHADER_CODE_FOUND("vertex");
    }
    
    if (fragmentCode.empty()) {
        D_ASSERT_SHADER_CODE_FOUND("fragment");
    }
}


std::string ShaderLoader::vertexShaderSource;

std::string ShaderLoader::fragmentShaderSource;

GAPI::UInt ShaderLoader::vertexShader;

GAPI::UInt ShaderLoader::fragmentShader;

GAPI::UInt ShaderLoader::loadVertexShader(const std::string& vertexShaderSourceParam) {
    GAPI::UInt vertShader = gapi
            .loadAndCompileShader(GAPI::ShaderTypes::Vertex, vertexShaderSourceParam);
    shaderNamesMap.emplace(vertShader, "VERTEX");
    D_ASSERT_COMPILATION_OK(vertShader);
    return vertShader;
}

GAPI::UInt ShaderLoader::loadFragmentShader(const std::string& fragmentShaderSourceParam) {
    GAPI::UInt fragShader = gapi
            .loadAndCompileShader(GAPI::ShaderTypes::Fragment, fragmentShaderSourceParam);
    shaderNamesMap.emplace(fragShader, "FRAGMENT");
    D_ASSERT_COMPILATION_OK(fragShader);
    return fragShader;
}


GAPI::UInt ShaderLoader::createShaderProgram() {
    GAPI::UInt shaderProgram = gapi.createShaderProgram(vertexShader, fragmentShader);
    D_ASSERT_LINKING_OK(shaderProgram);
    return shaderProgram;
}

/**
 * @brief Map of names of the shaders and their IDs
 * Once the shader is created, we assign the name to the ID
 * This is used to identify the shader in case of handling an error
 *
 */
/**
 * @brief Clean the shader loader
 * Once the shaders are linked, they can be cleared as they are
 * no longer needed.
 */
void ShaderLoader::clean() {
    std::destroy(shaderNamesMap.begin(), shaderNamesMap.end()); //Delete pointers from map
    gapi.deleteShader(vertexShader);
    gapi.deleteShader(fragmentShader);
}

std::unordered_map<unsigned int, const char *> ShaderLoader::shaderNamesMap;