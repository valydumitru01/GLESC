/**************************************************************************************************
 * @file   GapiEnums.h
 * @author Valentin Dumitru
 * @date   2023-11-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/Config.h"
/**
 * @brief This class is used to define the different texture filters that can be used
 * @details It contains the different types of filters that can be used for the textures.
 * All the filters are defined as enums, each enum starts with a different number to avoid
 * overlapping between the different enums.
 * @TODO: Implement the value of each enum as the value of the OpenGL flag if OpenGL is used
 *   and do the same for other APIs.
 */
enum class GAPIValues {
    // TODO: Set these as OPENGL flags, using ifdef like the ones below this enum
    // Texture Filters
    MinFilterNearest [[maybe_unused]] = 0,
    MinFilterLinear [[maybe_unused]],
    MinFilterNearestMipmapNearest [[maybe_unused]],
    MinFilterLinearMipmapNearest [[maybe_unused]],
    MinFilterNearestMipmapLinear [[maybe_unused]],
    MinFilterLinearMipmapLinear [[maybe_unused]],
    MagFilterNearest [[maybe_unused]],
    MagFilterLinear [[maybe_unused]],
    WrapModeRepeat [[maybe_unused]],
    WrapModeMirroredRepeat [[maybe_unused]],
    WrapModeClampToEdge [[maybe_unused]],
    WrapModeClampToBorder [[maybe_unused]],
    // Buffers
    BufferTypeVertex [[maybe_unused]],
    BufferTypeElement [[maybe_unused]],
    BufferTypeIndex [[maybe_unused]],
    // Buffer Usage
    BufferUsageStaticDraw [[maybe_unused]],
    BufferUsageDynamicDraw [[maybe_unused]],
    BufferUsageStreamDraw [[maybe_unused]],
    BufferUsageStaticRead [[maybe_unused]],
    BufferUsageDynamicRead [[maybe_unused]],
    BufferUsageStreamRead [[maybe_unused]],
    // Clear Bits
    ClearBitsColor [[maybe_unused]],
    ClearBitsDepth [[maybe_unused]],
    ClearBitsStencil [[maybe_unused]],
    // Shader Type
    ShaderTypeVertex [[maybe_unused]],
    ShaderTypeFragment [[maybe_unused]],
    
    // Stencil
    StencilTest [[maybe_unused]],
    StencilTestAlways [[maybe_unused]],
    StencilTestNever [[maybe_unused]],
    StencilTestLess [[maybe_unused]],
    StencilTestLessEqual [[maybe_unused]],
    StencilTestGreater [[maybe_unused]],
    StencilTestGreaterEqual [[maybe_unused]],
    StencilTestEqual [[maybe_unused]],
    StencilTestNotEqual [[maybe_unused]],
    StencilFail [[maybe_unused]],
    StencilFunc [[maybe_unused]],
    StencilRef [[maybe_unused]],
    
    // Depth
    DepthTest [[maybe_unused]],
    DepthTestAlways [[maybe_unused]],
    DepthTestNever [[maybe_unused]],
    DepthTestLess [[maybe_unused]],
    DepthTestLessEqual [[maybe_unused]],
    DepthTestGreater [[maybe_unused]],
    DepthTestGreaterEqual [[maybe_unused]],
    DepthTestEqual [[maybe_unused]],
    DepthTestNotEqual [[maybe_unused]],
    StencilPassDepthFail [[maybe_unused]],
    StencilPassDepthPass [[maybe_unused]],
    StencilValueMask [[maybe_unused]],
    StencilWriteMask [[maybe_unused]],
    StencilBackFunc [[maybe_unused]],
    StencilBackFail [[maybe_unused]],
    StencilBackPassDepthFail [[maybe_unused]],
    StencilBackPassDepthPass [[maybe_unused]],
    StencilBackRef [[maybe_unused]],
    StencilBackValueMask [[maybe_unused]],
    StencilBackWriteMask [[maybe_unused]],
    
    
    // Blending
    Blending [[maybe_unused]],
    BlendingOneMinusSrcAlpha [[maybe_unused]],
    BlendingSrcAlpha [[maybe_unused]],
    BlendingDstAlpha [[maybe_unused]],
    BlendingOne [[maybe_unused]],
    BlendingZero [[maybe_unused]],
    BlendingDstColor [[maybe_unused]],
    BlendingSrcColor [[maybe_unused]],
    BlendingOneMinusDstColor [[maybe_unused]],
    BlendingOneMinusSrcColor [[maybe_unused]],
    BlendingOneMinusConstantAlpha [[maybe_unused]],
    BlendingConstantAlpha [[maybe_unused]],
    BlendingConstantColor [[maybe_unused]],
    
    // Culling
    Culling [[maybe_unused]],
    CullingFront [[maybe_unused]],
    CullingBack [[maybe_unused]],
    CullingFrontBack [[maybe_unused]],
    
    // Polygon mode
    PolygonModeLine [[maybe_unused]],
    PolygonModeFill [[maybe_unused]],
    
    // Primitive type
    PrimitiveTypeTriangles [[maybe_unused]],
    PrimitiveTypeLines [[maybe_unused]],
    PrimitiveTypePoints [[maybe_unused]],
    PrimitiveTypeTriangleStrip [[maybe_unused]],
    PrimitiveTypeTriangleFan [[maybe_unused]],
    PrimitiveTypeLinesAdjacency [[maybe_unused]],
    PrimitiveTypeLineStripAdjacency [[maybe_unused]],
    PrimitiveTypeTrianglesAdjacency [[maybe_unused]],
    PrimitiveTypeTriangleStripAdjacency [[maybe_unused]],
    PrimitiveTypePatches [[maybe_unused]],
    PrimitiveTypeLineStrip [[maybe_unused]],
    PrimitiveTypeLineLoop [[maybe_unused]],
    
    // Winding order
    WindingOrderClockwise [[maybe_unused]],
    WindingOrderCounterClockwise [[maybe_unused]],
    
    // Face
    FaceFront [[maybe_unused]],
    FaceBack [[maybe_unused]],
    FaceFrontBack [[maybe_unused]],
    
    // Capabilities
    CapabilitiesDepthTest [[maybe_unused]],
    CapabilitiesStencilTest [[maybe_unused]],
    CapabilitiesBlending [[maybe_unused]],
    CapabilitiesCulling [[maybe_unused]],
    CapabilitiesPolygonMode [[maybe_unused]],
    
    // Texture Unit
    TextureUnit0 [[maybe_unused]],
    TextureUnit1 [[maybe_unused]]
};
enum class GAPITypeCount {
    Value [[maybe_unused]] = 1,
    Vec2 [[maybe_unused]] = 2,
    Vec3 [[maybe_unused]] = 3,
    Vec4 [[maybe_unused]] = 4,
    Mat2 [[maybe_unused]] = 4,
    Mat3 [[maybe_unused]] = 9,
    Mat4 [[maybe_unused]] = 16,
};
#ifdef GLESC_OPENGL
#include <GL/glew.h>

enum class GAPIType {
    Float [[maybe_unused]] = GL_FLOAT,
    Int [[maybe_unused]] = GL_INT,
    UnsignedInt [[maybe_unused]] = GL_UNSIGNED_INT,
    Bool [[maybe_unused]] = GL_BOOL,
    UnsignedByte [[maybe_unused]] = GL_UNSIGNED_BYTE,
    Byte [[maybe_unused]] = GL_BYTE,
    Short [[maybe_unused]] = GL_SHORT,
    UnsignedShort [[maybe_unused]] = GL_UNSIGNED_SHORT,
    Vec2F [[maybe_unused]] = GL_FLOAT_VEC2,
    Vec3F [[maybe_unused]] = GL_FLOAT_VEC3,
    Vec4F [[maybe_unused]] = GL_FLOAT_VEC4,
    Vec2I [[maybe_unused]] = GL_INT_VEC2,
    Vec3I [[maybe_unused]] = GL_INT_VEC3,
    Vec4I [[maybe_unused]] = GL_INT_VEC4,
    Vec2UI [[maybe_unused]] = GL_UNSIGNED_INT_VEC2,
    Vec3UI [[maybe_unused]] = GL_UNSIGNED_INT_VEC3,
    Vec4UI [[maybe_unused]] = GL_UNSIGNED_INT_VEC4,
    Vec2B [[maybe_unused]] = GL_BOOL_VEC2,
    Vec3B [[maybe_unused]] = GL_BOOL_VEC3,
    Vec4B [[maybe_unused]] = GL_BOOL_VEC4,
    Mat2F [[maybe_unused]] = GL_FLOAT_MAT2,
    Mat3F [[maybe_unused]] = GL_FLOAT_MAT3,
    Mat4F [[maybe_unused]] = GL_FLOAT_MAT4,
};
enum class GAPITypeSize {
    None [[maybe_unused]] = 0,
    Float [[maybe_unused]] = sizeof(GLfloat),
    Int [[maybe_unused]] = sizeof(GLint),
    Bool [[maybe_unused]] = sizeof(GLboolean),
    UnsignedInt [[maybe_unused]] = sizeof(GLuint),
    UnsignedByte [[maybe_unused]] = sizeof(GLubyte),
    Byte [[maybe_unused]] = sizeof(GLbyte),
    Short [[maybe_unused]] = sizeof(GLshort),
    UnsignedShort [[maybe_unused]] = sizeof(GLushort),
    Vec2F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(GAPITypeCount::Vec2),
    Vec3F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(GAPITypeCount::Vec3),
    Vec4F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(GAPITypeCount::Vec4),
    Vec2I [[maybe_unused]] = sizeof(GLint) * static_cast<GLsizei>(GAPITypeCount::Vec2),
    Vec3I [[maybe_unused]] = sizeof(GLint) * static_cast<GLsizei>(GAPITypeCount::Vec3),
    Vec4I [[maybe_unused]] = sizeof(GLint) * static_cast<GLsizei>(GAPITypeCount::Vec4),
    Vec2UI [[maybe_unused]] = sizeof(GLuint) * static_cast<GLsizei>(GAPITypeCount::Vec2),
    Vec3UI [[maybe_unused]] = sizeof(GLuint) * static_cast<GLsizei>(GAPITypeCount::Vec3),
    Vec4UI [[maybe_unused]] = sizeof(GLuint) * static_cast<GLsizei>(GAPITypeCount::Vec4),
    Vec2B [[maybe_unused]] = sizeof(GLboolean) * static_cast<GLsizei>(GAPITypeCount::Vec2),
    Vec3B [[maybe_unused]] = sizeof(GLboolean) * static_cast<GLsizei>(GAPITypeCount::Vec3),
    Vec4B [[maybe_unused]] = sizeof(GLboolean) * static_cast<GLsizei>(GAPITypeCount::Vec4),
    Mat2F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(GAPITypeCount::Mat2),
    Mat3F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(GAPITypeCount::Mat3),
    Mat4F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(GAPITypeCount::Mat4),
};

#endif
constexpr static GAPITypeCount getTypeCount(GAPIType type) {
    switch (type) {
        case GAPIType::Float:
        case GAPIType::Int:
        case GAPIType::UnsignedInt:
        case GAPIType::Bool:
        case GAPIType::UnsignedByte:
        case GAPIType::Byte:
        case GAPIType::Short:
        case GAPIType::UnsignedShort:
            return GAPITypeCount::Value;
        case GAPIType::Vec2F:
        case GAPIType::Vec2I:
        case GAPIType::Vec2UI:
        case GAPIType::Vec2B:
            return GAPITypeCount::Vec2;
        case GAPIType::Vec3F:
        case GAPIType::Vec3I:
        case GAPIType::Vec3UI:
        case GAPIType::Vec3B:
            return GAPITypeCount::Vec3;
        case GAPIType::Vec4F:
        case GAPIType::Vec4I:
        case GAPIType::Vec4UI:
        case GAPIType::Vec4B:
            return GAPITypeCount::Vec4;
        case GAPIType::Mat2F:
            return GAPITypeCount::Mat2;
        case GAPIType::Mat3F:
            return GAPITypeCount::Mat3;
        case GAPIType::Mat4F:
            return GAPITypeCount::Mat4;
    }
}
constexpr static GAPITypeSize getTypeSize(GAPIType type) {
    switch (type) {
        case GAPIType::Float:
            return GAPITypeSize::Float;
        case GAPIType::Int:
            return GAPITypeSize::Int;
        case GAPIType::UnsignedInt:
            return GAPITypeSize::UnsignedInt;
        case GAPIType::Bool:
            return GAPITypeSize::Bool;
        case GAPIType::UnsignedByte:
            return GAPITypeSize::UnsignedByte;
        case GAPIType::Byte:
            return GAPITypeSize::Byte;
        case GAPIType::Short:
            return GAPITypeSize::Short;
        case GAPIType::UnsignedShort:
            return GAPITypeSize::UnsignedShort;
        case GAPIType::Vec2F:
            return GAPITypeSize::Vec2F;
        case GAPIType::Vec3F:
            return GAPITypeSize::Vec3F;
        case GAPIType::Vec4F:
            return GAPITypeSize::Vec4F;
        case GAPIType::Vec2I:
            return GAPITypeSize::Vec2I;
        case GAPIType::Vec3I:
            return GAPITypeSize::Vec3I;
        case GAPIType::Vec4I:
            return GAPITypeSize::Vec4I;
        case GAPIType::Vec2UI:
            return GAPITypeSize::Vec2UI;
        case GAPIType::Vec3UI:
            return GAPITypeSize::Vec3UI;
        case GAPIType::Vec4UI:
            return GAPITypeSize::Vec4UI;
        case GAPIType::Vec2B:
            return GAPITypeSize::Vec2B;
        case GAPIType::Vec3B:
            return GAPITypeSize::Vec3B;
        case GAPIType::Vec4B:
            return GAPITypeSize::Vec4B;
        case GAPIType::Mat2F:
            return GAPITypeSize::Mat2F;
        case GAPIType::Mat3F:
            return GAPITypeSize::Mat3F;
        case GAPIType::Mat4F:
            return GAPITypeSize::Mat4F;
    }
}
constexpr static GAPIType getTypePrimitiveType(GAPIType type) {
    if (getTypeCount(type) == GAPITypeCount::Value) {
        return type;
    }
    switch (type) {
        case GAPIType::Vec2F:
        case GAPIType::Vec3F:
        case GAPIType::Vec4F:
        case GAPIType::Mat2F:
        case GAPIType::Mat3F:
        case GAPIType::Mat4F:
            return GAPIType::Float;
        case GAPIType::Vec2I:
        case GAPIType::Vec3I:
        case GAPIType::Vec4I:
            return GAPIType::Int;
        case GAPIType::Vec2UI:
        case GAPIType::Vec3UI:
        case GAPIType::Vec4UI:
            return GAPIType::UnsignedInt;
        case GAPIType::Vec2B:
        case GAPIType::Vec3B:
        case GAPIType::Vec4B:
            return GAPIType::Bool;
        default:
            return GAPIType::Float;
    }
}