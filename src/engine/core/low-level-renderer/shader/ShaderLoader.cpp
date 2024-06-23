/**************************************************************************************************
 * @file   ShaderLoader.cpp
 * @author Valentin Dumitru
 * @date   2023-11-08
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/core/logger/Logger.h"
#include "engine/core/low-level-renderer/asserts/ShaderAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/res-mng/files/FileManager.h"
#include "engine/core/low-level-renderer/shader/ShaderLoader.h"

#include "engine/core/debugger/Stringer.h"
using namespace GLESC::GAPI;
UInt ShaderLoader::loadShader(const std::string& fileName, const std::vector<std::string>& macros) {
    std::string shaderPath = std::string(SHADER_PATH) + "/" + fileName;
    std::string shaderSource = FileManager::readFile(shaderPath);
    Logger::get().success("Shader file read successfully: " + shaderPath);

    std::string vertexShaderSourceTemp;
    std::string fragmentShaderSourceTemp;

    extractShaderCode(shaderSource, vertexShaderSourceTemp, fragmentShaderSourceTemp);

    return loadShader(vertexShaderSourceTemp, fragmentShaderSourceTemp, macros);
}

UInt ShaderLoader::loadShader(const std::string& vertexShaderSourceParam,
                                    const std::string& fragmentShaderSourceParam,
                                    const std::vector<std::string>& macros) {
    vertexShaderSource = vertexShaderSourceParam;
    fragmentShaderSource = fragmentShaderSourceParam;
    insertShaderMacros(vertexShaderSource, fragmentShaderSource, macros);
    prependGLSLVersion(vertexShaderSource, fragmentShaderSource);

    Logger::get().nonImportantInfo(
        "Vertex Shader:\n\t" + GLESC::Stringer::replace(vertexShaderSource, "\n", "\n\t"));
    Logger::get().nonImportantInfo(
        "Fragment Shader:\n\t" + GLESC::Stringer::replace(fragmentShaderSource, "\n", "\n\t"));

    vertexShader = loadVertexShader(vertexShaderSource);
    Logger::get().success("Vertex shader loaded successfully");
    fragmentShader = loadFragmentShader(fragmentShaderSource);
    Logger::get().success("Fragment shader loaded successfully");
    UInt shaderProgram = createShaderProgram();
    Logger::get().success("Shader program created successfully");

    clean();
    return shaderProgram;
}


void ShaderLoader::insertShaderMacros(std::string& vertexCode, std::string& fragmentCode,
                                      const std::vector<std::string>& macros) {
    std::string macrosString;
    for (const auto& macro : macros) {
        macrosString += "#define " + macro + "\n";
    }

    vertexCode = macrosString + vertexCode;
    fragmentCode = macrosString + fragmentCode;
}

void ShaderLoader::extractShaderCode(const std::string& shaderSource,
                                     std::string& vertexCode,
                                     std::string& fragmentCode) {

    size_t vertexPos = shaderSource.find(tokenVertex);
    size_t fragmentPos = shaderSource.find(tokenFragment);

    validateShaderTokens(vertexPos, fragmentPos);

    // Extract shader codes
    if (vertexPos < fragmentPos) {
        vertexCode = shaderSource.substr(vertexPos + strlen(tokenVertex),
                                         fragmentPos - vertexPos - strlen(tokenVertex));
        fragmentCode = shaderSource.substr(fragmentPos + strlen(tokenFragment));
    }
    else {
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

UInt ShaderLoader::vertexShader;

UInt ShaderLoader::fragmentShader;

UInt ShaderLoader::loadVertexShader(const std::string& vertexShaderSourceParam) {
    UInt vertShader = getGAPI()
        .loadAndCompileShader(Enums::ShaderTypes::Vertex, vertexShaderSourceParam);
    shaderNamesMap.emplace(vertShader, "VERTEX");
    D_ASSERT_COMPILATION_OK(vertShader);
    return vertShader;
}

UInt ShaderLoader::loadFragmentShader(const std::string& fragmentShaderSourceParam) {
    UInt fragShader = getGAPI()
        .loadAndCompileShader(Enums::ShaderTypes::Fragment, fragmentShaderSourceParam);
    shaderNamesMap.emplace(fragShader, "FRAGMENT");
    D_ASSERT_COMPILATION_OK(fragShader);
    return fragShader;
}


UInt ShaderLoader::createShaderProgram() {
    UInt shaderProgram = getGAPI().createShaderProgram(vertexShader, fragmentShader);
    D_ASSERT_LINKING_OK(shaderProgram);
    return shaderProgram;
}


/**
 * @brief Clean the shader loader
 * Once the shaders are linked, they can be cleared as they are
 * no longer needed.
 */
void ShaderLoader::clean() {
    std::destroy(shaderNamesMap.begin(), shaderNamesMap.end()); //Delete pointers from map
    getGAPI().deleteShader(vertexShader);
    getGAPI().deleteShader(fragmentShader);
}

std::unordered_map<unsigned int, const char*> ShaderLoader::shaderNamesMap;
