/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/subsystems/renderer/shaders/ShaderLoader.h"
#include "engine/core/logger/Logger.h"
#include "engine/res-mng/files/FileManager.h"
#include "engine/core/exceptions/subsystems/ShaderException.h"

template<typename GAPI>
class ShaderLoader {
    template<typename GAPI_> friend
    class ShaderManager;

public:
    GAPIint loadShaders() {
        std::string vertexPath = VERT_SHADER;
        vertexShaderSource = FileManager::readFile(vertexPath);
        Logger::get().success("Shader file read successfully: " + vertexPath);
        
        std::string fragmentPath = FRAG_SHADER;
        fragmentShaderSource = FileManager::readFile(fragmentPath);
        Logger::get().success("Shader file read successfully: " + fragmentPath);
        
        std::string glslCoreStr = graphicInterface.getIsGlslCore() ? "core" : "";
        
        std::string glslVersionStr =
                "#version " + std::to_string(graphicInterface.getGlslMajorVersion()) + "" +
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

private:
    
    explicit ShaderLoader(IGraphicInterface &graphicInterface) :
            vertexShader(0), fragmentShader(0), shaderProgram(0), graphicInterface(
            graphicInterface) {
    }
    
    
    /**
     * @brief Source of the vertex shader
     *
     */
    std::string vertexShaderSource;
    /**
     * @brief Source of the fragment shader
     *
     */
    std::string fragmentShaderSource;
    /**
     * @brief ID reference to the vertex shader
     *
     */
    GAPIuint vertexShader;
    /**
     * @brief ID reference to the fragment shader
     *
     */
    GAPIuint fragmentShader;
    
    /**
     * @brief Loads the vertex shader
     * Sets the actual coordinates of the vertices in the GPU
     */
    void loadVertexShader() {
        vertexShader = graphicInterface
                .loadAndCompileShader(GAPIValues::ShaderTypeVertex, vertexShaderSource);
        shaderNamesMap.emplace(vertexShader, "VERTEX");
        handleErrorsCompilation(vertexShader);
    }
    
    /**
     * @brief Loads the fragment shader
     * Calculates colors of pixels (a fragment is a pixel in OpenGL)
     */
    void loadFragmentShader() {
        fragmentShader = graphicInterface
                .loadAndCompileShader(GAPIValues::ShaderTypeFragment, fragmentShaderSource);
        shaderNamesMap.emplace(fragmentShader, "FRAGMENT");
        handleErrorsCompilation(fragmentShader);
    }
    
    /**
     * @brief Links the loaded shaders into the shader program
     *
     */
    void createShaderProgram() {
        shaderProgram = graphicInterface.createShaderProgram(vertexShader, fragmentShader);
        handleErrorsLinking();
    }
    
    /**
     * @brief ID reference to the shader program
     *
     */
    GAPIint shaderProgram;
    
    /**
     * @brief Handle shader compilation errors
     *
     * @param shaderType ID reference of the shader
     */
    void handleErrorsCompilation(unsigned int shaderType) {
        char *infoLog = new char[512];
        if (!graphicInterface.compilationOK(shaderType, infoLog)) {
            throw ShaderCompilationException(std::string(shaderNamesMap.at(shaderType)), infoLog);
        }
        delete[] infoLog;
    }
    
    /**
     * @brief Handle shader linking into the shader program
     *
     */
    void handleErrorsLinking() {
        char *infoLog = new char[512];
        if (!graphicInterface.linkOK(shaderProgram, infoLog)) {
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
    void clean() const {
        std::destroy(shaderNamesMap.begin(), shaderNamesMap.end()); //Delete pointers from map
        graphicInterface.deleteShader(vertexShader);
        graphicInterface.deleteShader(fragmentShader);
    }
    
    std::unordered_map<unsigned int, const char *> shaderNamesMap;
    GAPI graphicInterface;
    // Uncomment this line and comment the above one to enable code completion and proper syntax highlighting
    // IGraphicInterface &graphicInterface;
    
    
};
















