/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/subsystems/renderer/shaders/ShaderLoader.h"
#include "engine/core/logger/Logger.h"
#include "engine/res-mng/files/FileManager.h"
#include "engine/core/exceptions/subsystems/ShaderException.h"

class ShaderLoader {

public:
    static GAPIint loadShader(std::string fileName){
        std::string shaderPath = std::string(SHADER_PATH) + "/" + fileName;
        std::string shaderSource = FileManager::readFile(shaderPath);
        GLESC::Logger::get().success("Shader file read successfully: " + shaderPath);
        
        std::string vertexCode;
        std::string fragmentCode;
        const char* tokenVertex = "#shader vertex";
        const char* tokenFragment = "#shader fragment";
        size_t vertexPos = shaderSource.find(tokenVertex);
        size_t fragmentPos = shaderSource.find(tokenFragment);
        
        // Extract vertex shader code
        if(vertexPos != std::string::npos){
            vertexPos += strlen(tokenVertex); // Move past the token
            fragmentPos = shaderSource.find(tokenFragment, vertexPos);
            vertexCode = shaderSource.substr(vertexPos, fragmentPos - vertexPos);
        }
        
        // Extract fragment shader code
        if(fragmentPos != std::string::npos){
            fragmentPos += strlen(tokenFragment); // Move past the token
            fragmentCode = shaderSource.substr(fragmentPos);
        }
        
        std::string glslCoreStr = GLESC_GLSL_CORE_PROFILE ? "core" : "";
        std::string glslVersionStr =
                "#version " + std::to_string(GLESC_GLSL_MAJOR_VERSION) + "" +
                std::to_string(GLESC_GLSL_MINOR_VERSION) + " " + glslCoreStr + "\n";
        
        // Prepend the GLSL version to shader sources
        vertexShaderSource = glslVersionStr + vertexCode;
        fragmentShaderSource = glslVersionStr + fragmentCode;
        
        GLESC::Logger::get().info("Vertex Shader:\n" + vertexShaderSource);
        GLESC::Logger::get().info("Fragment Shader:\n" + fragmentShaderSource);
        
        loadVertexShader();
        GLESC::Logger::get().success("Vertex shader loaded successfully");
        loadFragmentShader();
        GLESC::Logger::get().success("Fragment shader loaded successfully");
        GAPIuint shaderProgram = createShaderProgram();
        GLESC::Logger::get().success("Shader program created successfully");
        
        clean();
        return shaderProgram;
    }
private:
    
    /**
     * @brief Source of the vertex shader
     *
     */
    static std::string vertexShaderSource;
    /**
     * @brief Source of the fragment shader
     *
     */
    static std::string fragmentShaderSource;
    /**
     * @brief ID reference to the vertex shader
     *
     */
    static GAPIuint vertexShader;
    /**
     * @brief ID reference to the fragment shader
     *
     */
    static GAPIuint fragmentShader;
    
    /**
     * @brief Loads the vertex shader
     * Sets the actual coordinates of the vertices in the GPU
     */
    static void loadVertexShader() {
        vertexShader = gapi
                .loadAndCompileShader(GAPIValues::ShaderTypeVertex, vertexShaderSource);
        shaderNamesMap.emplace(vertexShader, "VERTEX");
        handleErrorsCompilation(vertexShader);
    }
    
    /**
     * @brief Loads the fragment shader
     * Calculates colors of pixels (a fragment is a pixel in OpenGL)
     */
    static void loadFragmentShader() {
        fragmentShader = gapi
                .loadAndCompileShader(GAPIValues::ShaderTypeFragment, fragmentShaderSource);
        shaderNamesMap.emplace(fragmentShader, "FRAGMENT");
        handleErrorsCompilation(fragmentShader);
    }
    
    /**
     * @brief Links the loaded shaders into the shader program
     *
     */
    static GAPIint createShaderProgram() {
        GAPIint shaderProgram = gapi.createShaderProgram(vertexShader, fragmentShader);
        handleErrorsLinking(shaderProgram);
        return shaderProgram;
    }
    

    
    /**
     * @brief Handle shader compilation errors
     *
     * @param shaderType ID reference of the shader
     */
    static void handleErrorsCompilation(unsigned int shaderType) {
        char *infoLog = new char[512];
        if (!gapi.compilationOK(shaderType, infoLog)) {
            throw ShaderCompilationException(std::string(shaderNamesMap.at(shaderType)), infoLog);
        }
        delete[] infoLog;
    }
    
    /**
     * @brief Handle shader linking into the shader program
     *
     */
    static void handleErrorsLinking(GAPIint shaderProgram) {
        char *infoLog = new char[512];
        if (!gapi.linkOK(shaderProgram, infoLog)) {
            throw ShaderLinkingException(std::string(infoLog));
        }
        delete[] infoLog;
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
    static void clean() {
        std::destroy(shaderNamesMap.begin(), shaderNamesMap.end()); //Delete pointers from map
        gapi.deleteShader(vertexShader);
        gapi.deleteShader(fragmentShader);
    }
    
    static std::unordered_map<unsigned int, const char *> shaderNamesMap;
    
    
};
















