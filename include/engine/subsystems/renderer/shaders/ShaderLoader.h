/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>
#include "engine/core/low-level-renderer/graphic-device-interface/GraphicInterface.h"

class ShaderLoader {
    friend class ShaderManager;

public:
    GDIint loadShaders();

private:
    
    explicit ShaderLoader(GraphicInterface &graphicInterface);
    
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
    GDIuint vertexShader;
    /**
     * @brief ID reference to the fragment shader
     *
     */
    GDIuint fragmentShader;
    
    /**
     * @brief Loads the vertex shader
     * Sets the actual coordinates of the vertices in the GPU
     */
    void loadVertexShader();
    
    /**
     * @brief Loads the fragment shader
     * Calculates colors of pixels (a fragment is a pixel in OpenGL)
     */
    void loadFragmentShader();
    
    /**
     * @brief Links the loaded shaders into the shader program
     *
     */
    void createShaderProgram();
    
    /**
     * @brief ID reference to the shader program
     *
     */
    GDIint shaderProgram;
    
    /**
     * @brief Handle shader compilation errors
     *
     * @param shaderType ID reference of the shader
     */
    void handleErrorsCompilation(unsigned int shaderType);
    
    /**
     * @brief Handle shader linking into the shader program
     *
     */
    void handleErrorsLinking();
    
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
    void clean() const;
    
    std::unordered_map<unsigned int, const char *> shaderNamesMap;
    
    GraphicInterface &graphicInterface;
    
    
};
