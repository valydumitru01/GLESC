/******************************************************************************
 * @file   GapiTypes.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once
#include "engine/Config.h"
#include "GapiEnums.h"

#ifdef GLESC_OPENGL
#include <GL/glew.h>

namespace GAPI{
    enum class Bool{
        False = GL_FALSE,
        True = GL_TRUE
    };
    using UInt = GLuint;
    using Float = GLfloat;
    using Int = GLint;
    using Size = GLuint;
    using Short = GLshort;
    using Char = GLchar;
    using UShort = GLushort;
    using UChar = GLubyte;
    using Byte = GLbyte;
    using UByte = GLubyte;
    using Void = GLvoid;
    using Bitfield = GLbitfield;
    using Byte = GLbyte;
    
    using TextureID = UInt;
    using ShaderProgramID = UInt;

} // namespace GAPI

#define GAPI_FALSE GL_FALSE
#define GAPI_TRUE GL_TRUE


#endif

#ifdef GLESC_VULKAN

#endif

#ifdef GLESC_DIRECTX

#endif


template<typename T>
struct isGraphicsType : std::false_type {};

// Specialize for expected types
template<> struct isGraphicsType<GAPI::Float> : std::true_type {};
template<> struct isGraphicsType<GAPI::Int> : std::true_type {};
template<> struct isGraphicsType<GAPI::UInt> : std::true_type {};
template<> struct isGraphicsType<GAPI::UShort> : std::true_type {};
template<> struct isGraphicsType<GAPI::UChar> : std::true_type {};


#include "engine/core/math/Vector.h"

// GLM vector types
template<> struct isGraphicsType<Vec2F> : std::true_type {};
template<> struct isGraphicsType<Vec3F> : std::true_type {};
template<> struct isGraphicsType<Vec4F> : std::true_type {};

#include "engine/core/math/Matrix.h"
// GLM matrix types
template<> struct isGraphicsType<Mat2F> : std::true_type {};
template<> struct isGraphicsType<Mat3F> : std::true_type {};
template<> struct isGraphicsType<Mat4F> : std::true_type {};

// GLM quaternion type
//template<> struct is_graphics_type<QuatF> : std::true_type {};

template<typename T>
bool constexpr isGraphicsType_v = isGraphicsType<T>::value;
