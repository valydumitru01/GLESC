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
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/core/math/Matrix.h"

namespace GLESC {
    class Shader {
    public:
        Shader(std::string fileName);
        
        ~Shader();
        
        void bind() const;
        
        void unbind() const;
        
        /**
         * @brief Change boolean value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param value The new boolean value
         */
        void setBool(const std::string &name, bool value);
        
        /**
         * @brief Change int value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param value The new int value
         */
        void setInt(const std::string &name, int value);
        
        /**
         * @brief Change float value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param value The new float value
         */
        void setFloat(const std::string &name, float value);
        
        /**
         * @brief Change vec2 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param value The new glm::vec2 value
         */
        void setVec2(const std::string &name, const Vec2 &value);
        
        /**
         * @brief Change vec2 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param x The new x value of vec2
         * @param y The new y value of vec2
         */
        void setVec2(const std::string &name, float x, float y);
        
        /**
         * @brief Change vec3 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param value The new glm::vec3 value
         */
        void setVec3(const std::string &name, const Vec3 &value);
        
        /**
         * @brief Change vec3 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param x The new x value of vec3
         * @param y The new y value of vec3
         * @param z The new z value of vec3
         */
        void setVec3(const std::string &name, float x, float y, float z);
        
        /**
         * @brief Change vec4 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param value The new Vec4 value
         */
        void setVec4(const std::string &name, const Vec4 &value);
        
        /**
         * @brief Change vec4 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param x The new x value of vec4
         * @param y The new y value of vec4
         * @param z The new z value of vec4
         * @param w The new w value of vec4
         */
        void setVec4(const std::string &name, float x, float y, float z, float w);
        
        /**
         * @brief Change mat2 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param mat The new Matrix2 value
         */
        void setMat2(const std::string &name, const Matrix2 &mat);
        
        /**
         * @brief Change mat3 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param mat The new Matrix3 value
         */
        void setMat3(const std::string &name, const Matrix3 &mat);
        
        /**
         * @brief Change mat4 value of Uniform by name
         *
         * @param name Name of the Uniform
         * @param mat The new Matrix4 value
         */
        void setMat4(const std::string &name, const Matrix4 &mat);
    
    private:
        /**
         * @brief The shader program
         */
        GAPIuint shaderProgram;
    }; // class Shader
}