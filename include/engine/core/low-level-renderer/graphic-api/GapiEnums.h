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
#ifdef GLESC_OPENGL
#include <GL/glew.h>

enum class GAPITypes {
    Float [[maybe_unused]] = GL_FLOAT,
    Int [[maybe_unused]] = GL_INT,
    UnsignedInt [[maybe_unused]] = GL_UNSIGNED_INT,
    Bool [[maybe_unused]] = GL_BOOL,
    UnsignedByte [[maybe_unused]] = GL_UNSIGNED_BYTE,
    Byte [[maybe_unused]] = GL_BYTE,
    Short [[maybe_unused]] = GL_SHORT,
    UnsignedShort [[maybe_unused]] = GL_UNSIGNED_SHORT,
    HalfFloat [[maybe_unused]] = GL_HALF_FLOAT
};
enum class DataTypeSize {
    SizeNone [[maybe_unused]] = 0,
    SizeFloat [[maybe_unused]] = sizeof(GLfloat),
    SizeInt [[maybe_unused]] = sizeof(GLint),
    SizeBool [[maybe_unused]] = sizeof(GLboolean)
};
#endif
enum class DataDimSize {
    Value [[maybe_unused]] = 0,
    Vec2 [[maybe_unused]] = 2,
    Vec3 [[maybe_unused]] = 3,
    Vec4 [[maybe_unused]] = 4,
    Mat2 [[maybe_unused]] = 4,
    Mat3 [[maybe_unused]] = 9,
    Mat4 [[maybe_unused]] = 16
};