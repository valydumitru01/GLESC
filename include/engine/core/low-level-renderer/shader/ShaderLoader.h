/***************************************************************************************************
* @file   Shader.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Class for handling shader loading.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once
#include <string>
#include <unordered_map>

#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

namespace GLESC::GAPI {
    class ShaderLoader {
    public:
        /**
         * @brief Load the shader from a file
         * @param fileName The name of the file containing the shader
         * @param macros The macros to be used in the shader
         * @return The ID of the shader program
         */
        static UInt loadShader(const std::string& fileName, const std::vector<std::string>& macros = {});
        /**
         * @brief Load the shader from the source code
         * @param vertexShaderSourceParam The source code of the vertex shader
         * @param fragmentShaderSourceParam The source code of the fragment shader
         * @param macros The macros to be used in the shader
         * @return The ID of the shader program
         */
        static UInt loadShader(const std::string& vertexShaderSourceParam,
                               const std::string& fragmentShaderSourceParam,
                               const std::vector<std::string>& macros = {});

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
        static UInt vertexShader;
        /**
         * @brief ID reference to the fragment shader
         *
         */
        static UInt fragmentShader;

        /**
         * @brief Loads the vertex shader
         * Sets the actual coordinates of the vertices in the GPU
         */
        static UInt loadVertexShader(const std::string& vertexShaderSourceParam);

        /**
         * @brief Loads the fragment shader
         * Calculates colors of pixels (a fragment is a pixel in OpenGL)
         */
        static UInt loadFragmentShader(const std::string& fragmentShaderSourceParam);

        /**
         * @brief Links the loaded shaders into the shader program
         *
         */
        static UInt createShaderProgram();
        /**
         * @brief Extracts the shader code from the source
         * @details The shader source is split into the vertex and fragment shader code.
         * They are separated by the tokens defined in tokenVertex and tokenFragment.
         * @see tokenVertex
         * @see tokenFragment
         * @param shaderSource The source of the shader
         * @param vertexCode The extracted vertex shader code
         * @param fragmentCode The extracted fragment shader code
         */
        static void extractShaderCode(const std::string& shaderSource,
                                      std::string& vertexCode,
                                      std::string& fragmentCode);
        /**
         * @brief Prepends the GLSL version to the shader code
         * @details The GLSL version is prepended to the shader code.
         * The version is obtained in getGLSLVersionString().
         * @see getGLSLVersionString()
         * @param vertexCode The vertex shader code
         * @param fragmentCode The fragment shader code
         */
        static void prependGLSLVersion(std::string& vertexCode, std::string& fragmentCode);
        /**
         * @brief Inserts the shader macros into the shader code
         * @details This function append the macros to the shader code.
         * @param vertexCode The vertex shader code
         * @param fragmentCode The fragment shader code
         * @param macros The macros to be inserted
         */
        static void insertShaderMacros(std::string& vertexCode, std::string& fragmentCode,
                                       const std::vector<std::string>& macros);
        /**
         * @brief Gets the GLSL version string
         * @details This obtains the GLSL version string based on the OpenGL version defined in the Config.h
         * @see Config.h
         * @return The GLSL version string
         */
        static std::string getGLSLVersionString();
        /**
         * @brief Validates the shader tokens
         * @details The shader tokens are validated to ensure that they are present in the shader source.
         * @param vertexPos The position of the vertex token
         * @param fragmentPos The position of the fragment token
         */
        static void validateShaderTokens(size_t vertexPos, size_t fragmentPos);
        /**
         * @brief Validates the shader codes
         * @details The shader codes are validated to ensure that they are not empty.
         * @param vertexCode The vertex shader code
         * @param fragmentCode The fragment shader code
         */
        static void validateShaderCodes(const std::string& vertexCode, const std::string& fragmentCode);
        /**
         * @brief Tokens used to separate the vertex and fragment shaders
         */
        static constexpr const char* tokenVertex = "#shader vertex";
        /**
         * @brief Tokens used to separate the vertex and fragment shaders
         */
        static constexpr const char* tokenFragment = "#shader fragment";
        /**
         * @brief Clean the shader loader
         * @details Once the shaders are linked, they can be cleared as they are
         * no longer needed.
         */
        static void clean();
        /**
         * @brief Map of names of the shaders and their IDs
         * @details Once the shader is created, we assign the name to the ID
         * This is used to identify the shader in case of handling an error
         *
         */
        static std::unordered_map<unsigned int, const char*> shaderNamesMap;
    };
}
