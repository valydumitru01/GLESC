/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <string>


#include <GL/glew.h>
#include "engine/core/math/Matrix.h"
#include "ShaderLoader.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"



class UniformHandler {
public:
    UniformHandler() = delete;
    
    /**
     * @brief Change boolean value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new boolean value
     */
    static void setBool(GLuint shaderProgram, const std::string &name, bool value) {
        gapi.setUniform1Int(gapi.getUniformLocation(shaderProgram, name), (int) value);
    }
    
    /**
     * @brief Change int value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new int value
     */
    static void setInt(GLuint shaderProgram, const std::string &name, int value) {
        gapi.setUniform1Int(gapi.getUniformLocation(shaderProgram, name), value);
    }
    
    /**
     * @brief Change float value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new float value
     */
    static void setFloat(GLuint shaderProgram, const std::string &name, float value) {
        gapi.setUniform1Float(gapi.getUniformLocation(shaderProgram, name), value);
    }
    
    /**
     * @brief Change vec2 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new Vec2 value
     */
    static void setVec2(GLuint shaderProgram, const std::string &name, const Vec2 &value) {
        gapi.setUniform2FloatVector(gapi.getUniformLocation(shaderProgram, name), 1, &value[0]);
    }
    
    /**
     * @brief Change vec2 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param x The new x value of vec2
     * @param y The new y value of vec2
     */
    static void setVec2(GLuint shaderProgram, const std::string &name, float x, float y) {
        gapi.setUniform2Float(gapi.getUniformLocation(shaderProgram, name), x, y);
    }
    
    /**
     * @brief Change vec3 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new Vec3 value
     */
    static void setVec3(GLuint shaderProgram, const std::string &name, const Vec3 &value) {
        gapi.setUniform3FloatVector(gapi.getUniformLocation(shaderProgram, name), 1, &value[0]);
    }
    
    /**
     * @brief Change vec3 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param x The new x value of vec3
     * @param y The new y value of vec3
     * @param z The new z value of vec3
     */
    static void setVec3(GLuint shaderProgram, const std::string &name, float x, float y, float z) {
        gapi.setUniform3Float(gapi.getUniformLocation(shaderProgram, name), x, y, z);
    }
    
    /**
     * @brief Change vec4 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param value The new Vec4 value
     */
    static void setVec4(GLuint shaderProgram, const std::string &name, const Vec4 &value) {
        gapi.setUniform4FloatVector(gapi.getUniformLocation(shaderProgram, name), 1, &value[0]);
    }
    
    /**
     * @brief Change vec4 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param x The new x value of vec4
     * @param y The new y value of vec4
     * @param z The new z value of vec4
     * @param w The new w value of vec4
     */
    void
    static setVec4(GLuint shaderProgram, const std::string &name, float x, float y, float z, float w) {
        gapi.setUniform4Float(gapi.getUniformLocation(shaderProgram, name), x, y, z, w);
    }
    
    /**
     * @brief Change mat2 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param mat The new Matrix2 value
     */
    static void setMat2(GLuint shaderProgram, const std::string &name, const Matrix2 &mat) {
        gapi.setUniformMatrix2FloatVector(gapi.getUniformLocation(shaderProgram, name), 1,
                                          GAPI_FALSE, &mat[0][0]);
    }
    
    /**
     * @brief Change mat3 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param mat The new Matrix3 value
     */
    static void setMat3(GLuint shaderProgram, const std::string &name, const Matrix3 &mat) {
        gapi.setUniformMatrix3FloatVector(gapi.getUniformLocation(shaderProgram, name), 1,
                                          GAPI_FALSE, &mat[0][0]);
    }
    
    /**
     * @brief Change mat4 value of Uniform by name
     *
     * @param name Name of the Uniform
     * @param mat The new glm::mat4 value
     */
    static void setMat4(GLuint shaderProgram, const std::string &name, const Matrix4 &mat) {
        gapi.setUniformMatrix4FloatVector(gapi.getUniformLocation(shaderProgram, name), 1,
                                          GAPI_FALSE, &mat[0][0]);
    }
};
