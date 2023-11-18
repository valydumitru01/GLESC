/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <string>
#include <unordered_map>

#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

class ShaderLoader {

public:
    static GAPIuint loadShader(const std::string& fileName);
    static GAPIuint loadShader(const std::string& vertexShaderSourceParam,
                              const std::string& fragmentShaderSourceParam);
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
    static GAPIuint loadVertexShader(const std::string& vertexShaderSourceParam);
    
    /**
     * @brief Loads the fragment shader
     * Calculates colors of pixels (a fragment is a pixel in OpenGL)
     */
    static GAPIuint loadFragmentShader(const std::string& fragmentShaderSourceParam);
    
    /**
     * @brief Links the loaded shaders into the shader program
     *
     */
    static GAPIuint createShaderProgram();
    
    static void extractShaderCode(const std::string& shaderSource,
                                  std::string& vertexCode,
                                  std::string& fragmentCode);
    static void prependGLSLVersion(std::string& vertexCode, std::string& fragmentCode);
    static std::string getGLSLVersionString();
    static void validateShaderTokens(size_t vertexPos, size_t fragmentPos);
    static void validateShaderCodes(const std::string& vertexCode, const std::string& fragmentCode);
    
    
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
    static void clean();
    
    static std::unordered_map<unsigned int, const char *> shaderNamesMap;
    
    
};
















