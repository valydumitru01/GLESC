/***************************************************************************************************
 * @file   Shader.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <string>
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/subsystems/renderer/RendererConfig.h"
#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/algebra/vector/Vector.h"
#define getFunc get
#define CONCAT(a, b) a ## b
namespace GLESC {
    class Shader {
    public:
        enum ShaderMacros {
            USE_COLOR,
            USE_INSTANCE
        };

        /**
         * @brief Constructor that receives the source code of the vertex and fragment shaders
         * @param vertexShaderSource The source code of the vertex shader
         * @param fragmentShaderSource The source code of the fragment shader
         * @param macros The macros to be used in the shader (default is USE_COLOR)
         */
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource,
               const std::vector<ShaderMacros>& macros = {USE_COLOR});

        /**
         * @brief Constructor that receives the file name of the shader source code (including
         *      vertex and fragment shaders in a single file)
         * @param fileName The file name of the shader source code
         */
        Shader(const std::string& fileName, const std::vector<ShaderMacros>& macros = {USE_COLOR});

        ~Shader();

        void bind() const;

        void unbind() const;

        UniformSetter setUniform(const std::string& name) const;


    private:

        float GLESC_UNIFORM_AMBIENT_INTENSITY= 0.0f;
        /**
         * @brief The shader program
         */
        GAPI::UInt shaderProgram;
    }; // class Shader
}
