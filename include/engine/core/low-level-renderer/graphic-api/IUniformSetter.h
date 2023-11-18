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

#include "engine/core/math/Matrix.h"
#include "engine/core/math/Vec.h"
#include "GapiTypes.h"

class IUniformSetter {
public:
    // Single values
    virtual void u1F(GAPIfloat v0) = 0;
    virtual void u1I(GAPIint v0) = 0;
    virtual void u1Ui(GAPIuint v0) = 0;
    virtual void u1B(GAPIbool v0) = 0;
    
    // Single vectors
    // Floats
    virtual void u2F(Vec2F vec2) = 0;
    virtual void u3F(Vec3F vec3) = 0;
    virtual void u4F(Vec4F vec4) = 0;
    virtual void u2F(GAPIfloat vec2[2]) = 0;
    virtual void u3F(GAPIfloat vec3[3]) = 0;
    virtual void u4F(GAPIfloat vec4[4]) = 0;
    virtual void u2F(GAPIfloat v0, GAPIfloat v1) = 0;
    virtual void u3F(GAPIfloat v0, GAPIfloat v1, GAPIfloat v2) = 0;
    virtual void u4F(GAPIfloat v0, GAPIfloat v1, GAPIfloat v2, GAPIfloat v3) = 0;
    // Ints
    virtual void u2I(Vec2I vec2) = 0;
    virtual void u3I(Vec3I vec3) = 0;
    virtual void u4I(Vec4I vec4) = 0;
    virtual void u2I(GAPIint vec2[2]) = 0;
    virtual void u3I(GAPIint vec3[3]) = 0;
    virtual void u4I(GAPIint vec4[4]) = 0;
    virtual void u2I(GAPIint v0, GAPIint v1) = 0;
    virtual void u3I(GAPIint v0, GAPIint v1, GAPIint v2) = 0;
    virtual void u4I(GAPIint v0, GAPIint v1, GAPIint v2, GAPIint v3) = 0;
    // Unsigned ints
    virtual void u2Ui(Vec2Ui vec2) = 0;
    virtual void u3Ui(Vec3Ui vec3) = 0;
    virtual void u4Ui(Vec4Ui vec4) = 0;
    virtual void u2Ui(GAPIuint vec2[2]) = 0;
    virtual void u3Ui(GAPIuint vec3[3]) = 0;
    virtual void u4Ui(GAPIuint vec4[4]) = 0;
    virtual void u2Ui(GAPIuint v0, GAPIuint v1) = 0;
    virtual void u3Ui(GAPIuint v0, GAPIuint v1, GAPIuint v2) = 0;
    virtual void u4Ui(GAPIuint v0, GAPIuint v1, GAPIuint v2, GAPIuint v3) = 0;
    // Booleans
    virtual void u2B(Vec2B vec2) = 0;
    virtual void u3B(Vec3B vec3) = 0;
    virtual void u4B(Vec4B vec4) = 0;
    virtual void u2B(GAPIbool vec2[2]) = 0;
    virtual void u3B(GAPIbool vec3[3]) = 0;
    virtual void u4B(GAPIbool vec4[4]) = 0;
    virtual void u2B(GAPIbool v0, GAPIbool v1) = 0;
    virtual void u3B(GAPIbool v0, GAPIbool v1, GAPIbool v2) = 0;
    virtual void u4B(GAPIbool v0, GAPIbool v1, GAPIbool v2, GAPIbool v3) = 0;
    
    // Single matrices
    // Floats (Only floats are supported)
    virtual void uMat2F(Mat2F mat) = 0;
    virtual void uMat3F(Mat3F mat) = 0;
    virtual void uMat4F(Mat4F mat) = 0;
    
    // Vectors of vectors
    // Floats
    virtual void u1FVec(const std::vector<GAPIfloat>& values) = 0;
    virtual void u2FVec(const std::vector<Vec2F>& values) = 0;
    virtual void u3FVec(const std::vector<Vec3F>& values) = 0;
    virtual void u4FVec(const std::vector<Vec4F>& values) = 0;
    // Ints
    virtual void u1IVec(const std::vector<GAPIint>& values) = 0;
    virtual void u2IVec(const std::vector<Vec2I>& values) = 0;
    virtual void u3IVec(const std::vector<Vec3I>& values) = 0;
    virtual void u4IVec(const std::vector<Vec4I>& values) = 0;
    // Unsigned ints
    virtual void u1UiVec(const std::vector<GAPIuint>& values) = 0;
    virtual void u2UiVec(const std::vector<Vec2Ui>& values) = 0;
    virtual void u3UiVec(const std::vector<Vec3Ui>& values) = 0;
    virtual void u4UiVec(const std::vector<Vec4Ui>& values) = 0;
    // Booleans
    virtual void u1BVec(const std::vector<GAPIbool>& values) = 0;
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
