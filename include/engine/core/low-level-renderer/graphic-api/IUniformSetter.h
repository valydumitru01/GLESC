/**************************************************************************************************
 * @file   IUniformSetter.h
 * @author Valentin Dumitru
 * @date   2023-11-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/algebra/vector/Vector.h"
#include "GapiTypes.h"

class IUniformSetter {
public:
    // Single values
    virtual void u1F(GAPI::Float v0) = 0;
    virtual void u1I(GAPI::Int v0) = 0;
    virtual void u1Ui(GAPI::UInt v0) = 0;
    virtual void u1B(GAPI::Bool v0) = 0;
    
    // Single vectors
    // Floats
    virtual void u2F(Vec2F vec2) = 0;
    virtual void u3F(Vec3F vec3) = 0;
    virtual void u4F(Vec4F vec4) = 0;
    virtual void u2F(GAPI::Float vec2[2]) = 0;
    virtual void u3F(GAPI::Float vec3[3]) = 0;
    virtual void u4F(GAPI::Float vec4[4]) = 0;
    virtual void u2F(GAPI::Float v0, GAPI::Float v1) = 0;
    virtual void u3F(GAPI::Float v0, GAPI::Float v1, GAPI::Float v2) = 0;
    virtual void u4F(GAPI::Float v0, GAPI::Float v1, GAPI::Float v2, GAPI::Float v3) = 0;
    // Ints
    virtual void u2I(Vec2I vec2) = 0;
    virtual void u3I(Vec3I vec3) = 0;
    virtual void u4I(Vec4I vec4) = 0;
    virtual void u2I(GAPI::Int vec2[2]) = 0;
    virtual void u3I(GAPI::Int vec3[3]) = 0;
    virtual void u4I(GAPI::Int vec4[4]) = 0;
    virtual void u2I(GAPI::Int v0, GAPI::Int v1) = 0;
    virtual void u3I(GAPI::Int v0, GAPI::Int v1, GAPI::Int v2) = 0;
    virtual void u4I(GAPI::Int v0, GAPI::Int v1, GAPI::Int v2, GAPI::Int v3) = 0;
    // Unsigned ints
    virtual void u2Ui(Vec2Ui vec2) = 0;
    virtual void u3Ui(Vec3Ui vec3) = 0;
    virtual void u4Ui(Vec4Ui vec4) = 0;
    virtual void u2Ui(GAPI::UInt vec2[2]) = 0;
    virtual void u3Ui(GAPI::UInt vec3[3]) = 0;
    virtual void u4Ui(GAPI::UInt vec4[4]) = 0;
    virtual void u2Ui(GAPI::UInt v0, GAPI::UInt v1) = 0;
    virtual void u3Ui(GAPI::UInt v0, GAPI::UInt v1, GAPI::UInt v2) = 0;
    virtual void u4Ui(GAPI::UInt v0, GAPI::UInt v1, GAPI::UInt v2, GAPI::UInt v3) = 0;
    // Booleans
    virtual void u2B(Vec2B vec2) = 0;
    virtual void u3B(Vec3B vec3) = 0;
    virtual void u4B(Vec4B vec4) = 0;
    virtual void u2B(GAPI::Bool vec2[2]) = 0;
    virtual void u3B(GAPI::Bool vec3[3]) = 0;
    virtual void u4B(GAPI::Bool vec4[4]) = 0;
    virtual void u2B(GAPI::Bool v0, GAPI::Bool v1) = 0;
    virtual void u3B(GAPI::Bool v0, GAPI::Bool v1, GAPI::Bool v2) = 0;
    virtual void u4B(GAPI::Bool v0, GAPI::Bool v1, GAPI::Bool v2, GAPI::Bool v3) = 0;
    
    // Single matrices
    // Floats
    virtual void uMat2F(Mat2F mat) = 0;
    virtual void uMat3F(Mat3F mat) = 0;
    virtual void uMat4F(Mat4F mat) = 0;

    // Single matrices
    // Doubles
    virtual void uMat2D(Mat2D mat) = 0;
    virtual void uMat3D(Mat3D mat) = 0;
    virtual void uMat4D(Mat4D mat) = 0;

    // Vectors of vectors
    // Floats
    virtual void u1FVec(const std::vector<GAPI::Float>& values) = 0;
    virtual void u2FVec(const std::vector<Vec2F>& values) = 0;
    virtual void u3FVec(const std::vector<Vec3F>& values) = 0;
    virtual void u4FVec(const std::vector<Vec4F>& values) = 0;
    // Ints
    virtual void u1IVec(const std::vector<GAPI::Int>& values) = 0;
    virtual void u2IVec(const std::vector<Vec2I>& values) = 0;
    virtual void u3IVec(const std::vector<Vec3I>& values) = 0;
    virtual void u4IVec(const std::vector<Vec4I>& values) = 0;
    // Unsigned ints
    virtual void u1UiVec(const std::vector<GAPI::UInt>& values) = 0;
    virtual void u2UiVec(const std::vector<Vec2Ui>& values) = 0;
    virtual void u3UiVec(const std::vector<Vec3Ui>& values) = 0;
    virtual void u4UiVec(const std::vector<Vec4Ui>& values) = 0;
    // Booleans
    virtual void u1BVec(const std::vector<GAPI::Bool>& values) = 0;
    virtual void u2BVec(const std::vector<Vec2B>& values) = 0;
    virtual void u3BVec(const std::vector<Vec3B>& values) = 0;
    virtual void u4BVec(const std::vector<Vec4B>& values) = 0;
    
    
    // Multiple matrices
    // Floats
    virtual void uMat2FVec(const std::vector<Mat2F>& mats) = 0;
    virtual void uMat3FVec(const std::vector<Mat3F>& mats) = 0;
    virtual void uMat4FVec(const std::vector<Mat4F>& mats) = 0;
    
};
// Forward declaration for the different uniform setters to be able to create pointers
// using conditional compilation
class GLUniformSetter;
class VulkanUniformSetter;
class DirectXUniformSetter;

#ifdef GLESC_OPENGL
using UniformSetter = GLUniformSetter;
#endif

#ifdef GLESC_VULKAN
using UniformSetter = VulkanUniformSetter;
#endif GLESC_DIRECTX

#ifdef GLESC_DIRECTX
using UniformSetter = DirectXUniformSetter;
#endif