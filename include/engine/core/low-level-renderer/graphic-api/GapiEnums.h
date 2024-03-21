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

namespace GAPI {
    enum class TypeCount {
        Value [[maybe_unused]] = 1,
        Vec2 [[maybe_unused]] = 2,
        Vec3 [[maybe_unused]] = 3,
        Vec4 [[maybe_unused]] = 4,
        Mat2 [[maybe_unused]] = 4,
        Mat3 [[maybe_unused]] = 9,
        Mat4 [[maybe_unused]] = 16,
    };
}
#ifdef GLESC_OPENGL

#include <GL/glew.h>

namespace GAPI {
    namespace Texture {
        namespace Filters {
            enum class Min {
                Nearest [[maybe_unused]] = GL_NEAREST,
                Linear [[maybe_unused]] = GL_LINEAR,
                NearestMipmapNearest [[maybe_unused]] = GL_NEAREST_MIPMAP_NEAREST,
                LinearMipmapNearest [[maybe_unused]] = GL_LINEAR_MIPMAP_NEAREST,
                NearestMipmapLinear [[maybe_unused]] = GL_NEAREST_MIPMAP_LINEAR,
                LinearMipmapLinear [[maybe_unused]] = GL_LINEAR_MIPMAP_LINEAR
            };

            enum class Mag {
                Nearest [[maybe_unused]] = GL_NEAREST,
                Linear [[maybe_unused]] = GL_LINEAR,
            };

            enum class WrapMode {
                Repeat [[maybe_unused]] = GL_REPEAT,
                MirroredRepeat [[maybe_unused]] = GL_MIRRORED_REPEAT,
                ClampToEdge [[maybe_unused]] = GL_CLAMP_TO_EDGE,
                ClampToBorder [[maybe_unused]] = GL_CLAMP_TO_BORDER
            };
        };

        // TODO: This is messy, we're copying the messy opengl enums, we should make our own
        //  enums and convert them to opengl enums
        enum class GPUBufferFormat {
            R8 [[maybe_unused]] = GL_R8,
            R8_SNORM [[maybe_unused]] = GL_R8_SNORM,
            R16 [[maybe_unused]] = GL_R16,
            R16_SNORM [[maybe_unused]] = GL_R16_SNORM,
            RG8 [[maybe_unused]] = GL_RG8,
            RG8_SNORM [[maybe_unused]] = GL_RG8_SNORM,
            RG16 [[maybe_unused]] = GL_RG16,
            RG16_SNORM [[maybe_unused]] = GL_RG16_SNORM,
            R3_G3_B2 [[maybe_unused]] = GL_R3_G3_B2,
            RGB [[maybe_unused]] = GL_RGB,
            RGBA [[maybe_unused]] = GL_RGBA,
            RGB4 [[maybe_unused]] = GL_RGB4,
            RGB5 [[maybe_unused]] = GL_RGB5,
            RGB8 [[maybe_unused]] = GL_RGB8,
            RGB8_SNORM [[maybe_unused]] = GL_RGB8_SNORM,
            RGB10 [[maybe_unused]] = GL_RGB10,
            RGB12 [[maybe_unused]] = GL_RGB12,
            RGB16_SNORM [[maybe_unused]] = GL_RGB16_SNORM,
            RGBA2 [[maybe_unused]] = GL_RGBA2,
            RGBA4 [[maybe_unused]] = GL_RGBA4,
            RGB5_A1 [[maybe_unused]] = GL_RGB5_A1,
            RGBA8 [[maybe_unused]] = GL_RGBA8,
            RGBA8_SNORM [[maybe_unused]] = GL_RGBA8_SNORM,
            RGB10_A2 [[maybe_unused]] = GL_RGB10_A2,
            RGB10_A2UI [[maybe_unused]] = GL_RGB10_A2UI,
            RGBA12 [[maybe_unused]] = GL_RGBA12,
            RGBA16 [[maybe_unused]] = GL_RGBA16,
            SRGB8 [[maybe_unused]] = GL_SRGB8,
            SRGB8_ALPHA8 [[maybe_unused]] = GL_SRGB8_ALPHA8,
            R16F [[maybe_unused]] = GL_R16F,
            RG16F [[maybe_unused]] = GL_RG16F,
            RGB16F [[maybe_unused]] = GL_RGB16F,
            RGBA16F [[maybe_unused]] = GL_RGBA16F,
            R32F [[maybe_unused]] = GL_R32F,
            RG32F [[maybe_unused]] = GL_RG32F,
            RGB32F [[maybe_unused]] = GL_RGB32F,
            RGBA32F [[maybe_unused]] = GL_RGBA32F,
            R11F_G11F_B10F [[maybe_unused]] = GL_R11F_G11F_B10F,
            RGB9_E5 [[maybe_unused]] = GL_RGB9_E5,
            R8I [[maybe_unused]] = GL_R8I,
            R8UI [[maybe_unused]] = GL_R8UI,
            R16I [[maybe_unused]] = GL_R16I,
            R16UI [[maybe_unused]] = GL_R16UI,
            R32I [[maybe_unused]] = GL_R32I,
            R32UI [[maybe_unused]] = GL_R32UI,
            RG8I [[maybe_unused]] = GL_RG8I,
            RG8UI [[maybe_unused]] = GL_RG8UI,
            RG16I [[maybe_unused]] = GL_RG16I,
            RG16UI [[maybe_unused]] = GL_RG16UI,
            RG32I [[maybe_unused]] = GL_RG32I,
            RG32UI [[maybe_unused]] = GL_RG32UI,
            RGB8I [[maybe_unused]] = GL_RGB8I,
            RGB8UI [[maybe_unused]] = GL_RGB8UI,
            RGB16I [[maybe_unused]] = GL_RGB16I,
            RGB16UI [[maybe_unused]] = GL_RGB16UI,
            RGB32I [[maybe_unused]] = GL_RGB32I,
            RGB32UI [[maybe_unused]] = GL_RGB32UI,
            RGBA8I [[maybe_unused]] = GL_RGBA8I,
            RGBA8UI [[maybe_unused]] = GL_RGBA8UI,
            RGBA16I [[maybe_unused]] = GL_RGBA16I,
            RGBA16UI [[maybe_unused]] = GL_RGBA16UI,
            RGBA32I [[maybe_unused]] = GL_RGBA32I,
            RGBA32UI [[maybe_unused]] = GL_RGBA32UI,
            DEPTH_COMPONENT16 [[maybe_unused]] = GL_DEPTH_COMPONENT16,
            DEPTH_COMPONENT24 [[maybe_unused]] = GL_DEPTH_COMPONENT24,
            DEPTH_COMPONENT32F [[maybe_unused]] = GL_DEPTH_COMPONENT32F,
            DEPTH24_STENCIL8 [[maybe_unused]] = GL_DEPTH24_STENCIL8,
            DEPTH32F_STENCIL8 [[maybe_unused]] = GL_DEPTH32F_STENCIL8,
            STENCIL_INDEX8 [[maybe_unused]] = GL_STENCIL_INDEX8,
        };

        enum class CPUBufferFormat {
            R [[maybe_unused]] = GL_R,
            RG [[maybe_unused]] = GL_RG,
            RGB [[maybe_unused]] = GL_RGB,
            BGR [[maybe_unused]] = GL_BGR,
            RGBA [[maybe_unused]] = GL_RGBA,
            BGRA [[maybe_unused]] = GL_BGRA,
            DepthComponent [[maybe_unused]] = GL_DEPTH_COMPONENT,
            DepthStencil [[maybe_unused]] = GL_DEPTH_STENCIL
        };

        enum class BitDepth {
            Bit8 [[maybe_unused]] = 8,
            Bit16 [[maybe_unused]] = 16,
            Bit24 [[maybe_unused]] = 24,
            Bit32 [[maybe_unused]] = 32
        };
    }

    enum class BufferTypes {
        Vertex [[maybe_unused]] = GL_ARRAY_BUFFER,
        Index [[maybe_unused]] = GL_ELEMENT_ARRAY_BUFFER
    };

    enum class BufferUsages {
        StaticDraw [[maybe_unused]] = GL_STATIC_DRAW,
        DynamicDraw [[maybe_unused]] = GL_DYNAMIC_DRAW,
        StreamDraw [[maybe_unused]] = GL_STREAM_DRAW,
        StaticRead [[maybe_unused]] = GL_STATIC_READ,
        DynamicRead [[maybe_unused]] = GL_DYNAMIC_READ,
        StreamRead [[maybe_unused]] = GL_STREAM_READ
    };

    enum class ClearBits {
        Color [[maybe_unused]] = GL_COLOR_BUFFER_BIT,
        Depth [[maybe_unused]] = GL_DEPTH_BUFFER_BIT,
        Stencil [[maybe_unused]] = GL_STENCIL_BUFFER_BIT
    };

    enum class ShaderTypes {
        Vertex [[maybe_unused]] = GL_VERTEX_SHADER,
        Fragment [[maybe_unused]] = GL_FRAGMENT_SHADER
    };

    enum class StencilParameters {
        StencilTest [[maybe_unused]] = GL_STENCIL_TEST,
        StencilFail [[maybe_unused]] = GL_STENCIL_FAIL,
        StencilFunc [[maybe_unused]] = GL_STENCIL_FUNC,
        StencilRef [[maybe_unused]] = GL_STENCIL_REF,
        StencilValueMask [[maybe_unused]] = GL_STENCIL_VALUE_MASK,
        StencilWriteMask [[maybe_unused]] = GL_STENCIL_WRITEMASK,
        StencilClearValue [[maybe_unused]] = GL_STENCIL_CLEAR_VALUE,
        StencilPassDepthFail [[maybe_unused]] = GL_STENCIL_PASS_DEPTH_FAIL,
        StencilPassDepthPass [[maybe_unused]] = GL_STENCIL_PASS_DEPTH_PASS,
        StencilBackFunc [[maybe_unused]] = GL_STENCIL_BACK_FUNC,
        StencilBackFail [[maybe_unused]] = GL_STENCIL_BACK_FAIL,
        StencilBackPassDepthFail [[maybe_unused]] = GL_STENCIL_BACK_PASS_DEPTH_FAIL,
        StencilBackPassDepthPass [[maybe_unused]] = GL_STENCIL_BACK_PASS_DEPTH_PASS,
        StencilBackRef [[maybe_unused]] = GL_STENCIL_BACK_REF,
        StencilBackValueMask [[maybe_unused]] = GL_STENCIL_BACK_VALUE_MASK,
        StencilBackWriteMask [[maybe_unused]] = GL_STENCIL_BACK_WRITEMASK
    };

    enum class DepthParameters {
        DepthTest [[maybe_unused]] = GL_DEPTH_TEST,
        DepthFunc [[maybe_unused]] = GL_DEPTH_FUNC
    };

    enum class BlendingParameters {
        Blending [[maybe_unused]] = GL_BLEND,
        BlendEquationRGB [[maybe_unused]] = GL_BLEND_EQUATION_RGB,
        BlendEquationAlpha [[maybe_unused]] = GL_BLEND_EQUATION_ALPHA,
        BlendDstRGB [[maybe_unused]] = GL_BLEND_DST_RGB,
        BlendSrcRGB [[maybe_unused]] = GL_BLEND_SRC_RGB,
        BlendDstAlpha [[maybe_unused]] = GL_BLEND_DST_ALPHA,
        BlendSrcAlpha [[maybe_unused]] = GL_BLEND_SRC_ALPHA,
        BlendColor [[maybe_unused]] = GL_BLEND_COLOR
    };

    enum class CullingParameters {
        Culling [[maybe_unused]] = GL_CULL_FACE,
        CullFaceMode [[maybe_unused]] = GL_CULL_FACE_MODE,
        FrontFace [[maybe_unused]] = GL_FRONT_FACE
    };

    enum class PolygonModeParameters {
        PolygonMode [[maybe_unused]] = GL_POLYGON_MODE
    };

    enum class PrimitiveTypes {
        Triangles [[maybe_unused]] = GL_TRIANGLES,
        Lines [[maybe_unused]] = GL_LINES,
        Points [[maybe_unused]] = GL_POINTS
    };

    enum class Capabilities {
        DepthTest [[maybe_unused]] = GL_DEPTH_TEST,
        StencilTest [[maybe_unused]] = GL_STENCIL_TEST,
        Blending [[maybe_unused]] = GL_BLEND,
        Culling [[maybe_unused]] = GL_CULL_FACE
    };

    enum class Types {
        Float [[maybe_unused]] = GL_FLOAT,
        Double [[maybe_unused]] = GL_DOUBLE,
        Int [[maybe_unused]] = GL_INT,
        UInt [[maybe_unused]] = GL_UNSIGNED_INT,
        Bool [[maybe_unused]] = GL_BOOL,
        Byte [[maybe_unused]] = GL_BYTE,
        UByte [[maybe_unused]] = GL_UNSIGNED_BYTE,
        Short [[maybe_unused]] = GL_SHORT,
        UShort [[maybe_unused]] = GL_UNSIGNED_SHORT,

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

        Vec2D [[maybe_unused]] = GL_DOUBLE_VEC2,
        Vec3D [[maybe_unused]] = GL_DOUBLE_VEC3,
        Vec4D [[maybe_unused]] = GL_DOUBLE_VEC4,

        Mat2F [[maybe_unused]] = GL_FLOAT_MAT2,
        Mat3F [[maybe_unused]] = GL_FLOAT_MAT3,
        Mat4F [[maybe_unused]] = GL_FLOAT_MAT4,

        Mat2D [[maybe_unused]] = GL_DOUBLE_MAT2,
        Mat3D [[maybe_unused]] = GL_DOUBLE_MAT3,
        Mat4D [[maybe_unused]] = GL_DOUBLE_MAT4
    };

    enum class TypeSize {
        None [[maybe_unused]] = 0,
        Float [[maybe_unused]] = sizeof(GLfloat),
        Double [[maybe_unused]] = sizeof(GLdouble),
        Int [[maybe_unused]] = sizeof(GLint),
        Bool [[maybe_unused]] = sizeof(GLboolean),
        UnsignedInt [[maybe_unused]] = sizeof(GLuint),
        UnsignedByte [[maybe_unused]] = sizeof(GLubyte),
        Byte [[maybe_unused]] = sizeof(GLbyte),
        Short [[maybe_unused]] = sizeof(GLshort),
        UnsignedShort [[maybe_unused]] = sizeof(GLushort),

        Vec2F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(TypeCount::Vec2),
        Vec3F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(TypeCount::Vec3),
        Vec4F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(TypeCount::Vec4),

        Vec2D [[maybe_unused]] = sizeof(GLdouble) * static_cast<GLsizei>(TypeCount::Vec2),
        Vec3D [[maybe_unused]] = sizeof(GLdouble) * static_cast<GLsizei>(TypeCount::Vec3),
        Vec4D [[maybe_unused]] = sizeof(GLdouble) * static_cast<GLsizei>(TypeCount::Vec4),

        Vec2I [[maybe_unused]] = sizeof(GLint) * static_cast<GLsizei>(TypeCount::Vec2),
        Vec3I [[maybe_unused]] = sizeof(GLint) * static_cast<GLsizei>(TypeCount::Vec3),
        Vec4I [[maybe_unused]] = sizeof(GLint) * static_cast<GLsizei>(TypeCount::Vec4),

        Vec2UI [[maybe_unused]] = sizeof(GLuint) * static_cast<GLsizei>(TypeCount::Vec2),
        Vec3UI [[maybe_unused]] = sizeof(GLuint) * static_cast<GLsizei>(TypeCount::Vec3),
        Vec4UI [[maybe_unused]] = sizeof(GLuint) * static_cast<GLsizei>(TypeCount::Vec4),

        Vec2B [[maybe_unused]] = sizeof(GLboolean) * static_cast<GLsizei>(TypeCount::Vec2),
        Vec3B [[maybe_unused]] = sizeof(GLboolean) * static_cast<GLsizei>(TypeCount::Vec3),
        Vec4B [[maybe_unused]] = sizeof(GLboolean) * static_cast<GLsizei>(TypeCount::Vec4),

        Mat2F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(TypeCount::Mat2),
        Mat3F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(TypeCount::Mat3),
        Mat4F [[maybe_unused]] = sizeof(GLfloat) * static_cast<GLsizei>(TypeCount::Mat4),

        Mat2D [[maybe_unused]] = sizeof(GLdouble) * static_cast<GLsizei>(TypeCount::Mat2),
        Mat3D [[maybe_unused]] = sizeof(GLdouble) * static_cast<GLsizei>(TypeCount::Mat3),
        Mat4D [[maybe_unused]] = sizeof(GLdouble) * static_cast<GLsizei>(TypeCount::Mat4)
    };

    namespace Texture {
        enum class Types {
            Texture2D [[maybe_unused]] = GL_TEXTURE_2D,
            Texture3D [[maybe_unused]] = GL_TEXTURE_3D,
            TextureCubeMap [[maybe_unused]] = GL_TEXTURE_CUBE_MAP,
            Texture2DArray [[maybe_unused]] = GL_TEXTURE_2D_ARRAY,
            TextureCubeMapArray [[maybe_unused]] = GL_TEXTURE_CUBE_MAP_ARRAY,
            Texture2DMultisample [[maybe_unused]] = GL_TEXTURE_2D_MULTISAMPLE,
            Texture2DMultisampleArray [[maybe_unused]] = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
        }; // enum class TextureTypes
    } // namespace Texture
}
#else
#error "No graphic API selected!"
#endif


namespace GAPI {
    constexpr static TypeCount getTypeCount(Types type) {
        switch (type) {
            case Types::Float:
            case Types::Double:
            case Types::Int:
            case Types::UInt:
            case Types::Bool:
            case Types::UByte:
            case Types::Byte:
            case Types::Short:
            case Types::UShort: return TypeCount::Value;
            case Types::Vec2F:
            case Types::Vec2D:
            case Types::Vec2I:
            case Types::Vec2UI:
            case Types::Vec2B: return TypeCount::Vec2;
            case Types::Vec3F:
            case Types::Vec3D:
            case Types::Vec3I:
            case Types::Vec3UI:
            case Types::Vec3B: return TypeCount::Vec3;
            case Types::Vec4F:
            case Types::Vec4I:
            case Types::Vec4UI:
            case Types::Vec4B: return TypeCount::Vec4;
            case Types::Mat2D:
            case Types::Mat2F: return TypeCount::Mat2;
            case Types::Mat3D:
            case Types::Mat3F: return TypeCount::Mat3;
            case Types::Mat4D:
            case Types::Mat4F: return TypeCount::Mat4;
        }
    }

    constexpr static TypeSize getTypeSize(Types type) {
        switch (type) {
            case Types::Float: return TypeSize::Float;
            case Types::Double: return TypeSize::Double;
            case Types::Int: return TypeSize::Int;
            case Types::UInt: return TypeSize::UnsignedInt;
            case Types::Bool: return TypeSize::Bool;
            case Types::UByte: return TypeSize::UnsignedByte;
            case Types::Byte: return TypeSize::Byte;
            case Types::Short: return TypeSize::Short;
            case Types::UShort: return TypeSize::UnsignedShort;

            case Types::Vec2F: return TypeSize::Vec2F;
            case Types::Vec3F: return TypeSize::Vec3F;
            case Types::Vec4F: return TypeSize::Vec4F;

            case Types::Vec2D: return TypeSize::Vec2D;
            case Types::Vec3D: return TypeSize::Vec3D;
            case Types::Vec4D: return TypeSize::Vec4D;

            case Types::Vec2I: return TypeSize::Vec2I;
            case Types::Vec3I: return TypeSize::Vec3I;
            case Types::Vec4I: return TypeSize::Vec4I;

            case Types::Vec2UI: return TypeSize::Vec2UI;
            case Types::Vec3UI: return TypeSize::Vec3UI;
            case Types::Vec4UI: return TypeSize::Vec4UI;

            case Types::Vec2B: return TypeSize::Vec2B;
            case Types::Vec3B: return TypeSize::Vec3B;
            case Types::Vec4B: return TypeSize::Vec4B;

            case Types::Mat2F: return TypeSize::Mat2F;
            case Types::Mat3F: return TypeSize::Mat3F;
            case Types::Mat4F: return TypeSize::Mat4F;

            case Types::Mat2D: return TypeSize::Mat2D;
            case Types::Mat3D: return TypeSize::Mat3D;
            case Types::Mat4D: return TypeSize::Mat4D;
        }
    }

    constexpr static Types getTypePrimitiveType(Types type) {
        if (getTypeCount(type) == TypeCount::Value) {
            return type;
        }
        switch (type) {
            case Types::Vec2F:
            case Types::Vec3F:
            case Types::Vec4F:
            case Types::Mat2F:
            case Types::Mat3F:
            case Types::Mat4F: return Types::Float;
            case Types::Vec2I:
            case Types::Vec3I:
            case Types::Vec4I: return Types::Int;
            case Types::Vec2UI:
            case Types::Vec3UI:
            case Types::Vec4UI: return Types::UInt;
            case Types::Vec2B:
            case Types::Vec3B:
            case Types::Vec4B: return Types::Bool;
            case Types::Vec2D:
            case Types::Vec3D:
            case Types::Vec4D:
            case Types::Mat2D:
            case Types::Mat3D:
            case Types::Mat4D: return Types::Double;
            default: return Types::Float;
        }
    }

    template<Types T>
    struct PrimitiveType;

    template<Types T>
    using PrimitiveType_t = typename PrimitiveType<T>::Type;

    template<Types T>
    struct PrimitiveType {
        static_assert(T != T, "Unsupported type specified");
    };

#define MAP_TYPE(EnumValue, MappedType) \
        template<> struct PrimitiveType<EnumValue> { using Type = MappedType; };

    MAP_TYPE(Types::Float, GLfloat);

    MAP_TYPE(Types::Double, GLdouble);

    MAP_TYPE(Types::Int, GLint);

    MAP_TYPE(Types::UInt, GLuint);

    MAP_TYPE(Types::Bool, GLboolean);

    MAP_TYPE(Types::Byte, GLbyte);

    MAP_TYPE(Types::UByte, GLubyte);

    MAP_TYPE(Types::Short, GLshort);

    MAP_TYPE(Types::UShort, GLushort);

    MAP_TYPE(Types::Vec2F, GLfloat);

    MAP_TYPE(Types::Vec3F, GLfloat);

    MAP_TYPE(Types::Vec4F, GLfloat);

    MAP_TYPE(Types::Vec2D, GLdouble);

    MAP_TYPE(Types::Vec3D, GLdouble);

    MAP_TYPE(Types::Vec4D, GLdouble);

    MAP_TYPE(Types::Vec2I, GLint);

    MAP_TYPE(Types::Vec3I, GLint);

    MAP_TYPE(Types::Vec4I, GLint);

    MAP_TYPE(Types::Vec2UI, GLuint);

    MAP_TYPE(Types::Vec3UI, GLuint);

    MAP_TYPE(Types::Vec4UI, GLuint);

    MAP_TYPE(Types::Vec2B, GLboolean);

    MAP_TYPE(Types::Vec3B, GLboolean);

    MAP_TYPE(Types::Vec4B, GLboolean);

    MAP_TYPE(Types::Mat2F, GLfloat);

    MAP_TYPE(Types::Mat3F, GLfloat);

    MAP_TYPE(Types::Mat4F, GLfloat);

    MAP_TYPE(Types::Mat2D, GLdouble);

    MAP_TYPE(Types::Mat3D, GLdouble);

    MAP_TYPE(Types::Mat4D, GLdouble);
} // namespace GAPI
