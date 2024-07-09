/***************************************************************************************************
 * @file   Shader.h
 * @author Valentin Dumitru
 * @brief Class for managing and utilizing shader programs in the graphics pipeline.
 * @details This class encapsulates the functionality for creating, binding, and manipulating shader programs.
 * It supports setting and retrieving uniform values and allows the use of shader macros to customize the shader
 * behavior. The class offers constructors for initializing shaders from source code or from files.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <string>
#include <vector>
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

namespace GLESC::GAPI {
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
        /**
         * @brief Destructor, deletes the shader program
         */
        ~Shader();
        /**
         * @brief Binds the shader program of the object
         */
        void bind() const;
        /**
         * @brief Unbinds the shader program
         */
        void unbind() const;

        /**
         * @brief Sets a uniform value in the shader
         * @tparam Type The type of the uniform value
         * @param name The name of the uniform
         * @param value The value to be set
         */
        template <typename Type>
        static void setUniform(const std::string& name, const Type& value) {
            Int location= getGAPI().getUniformLocation(name);
            getGAPI().setUniform(location, value);
            D_ASSERT_EQUAL(getGAPI().getUniformValue<Type>(location), value, "Uniform was not set correctly");
        }
        /**
         * @brief Gets a uniform value from the shader
         * @tparam Type The type of the uniform value
         * @param name The name of the uniform
         * @return The value of the uniform
         */
        template<typename Type>
        auto getUniform(const std::string& name) const {
            return getGAPI().getUniformValue<Type>(getGAPI().getUniformLocation(name));
        }

    private:
        /**
         * @brief The shader program
         */
        UInt shaderProgram;
    }; // class Shader
}
