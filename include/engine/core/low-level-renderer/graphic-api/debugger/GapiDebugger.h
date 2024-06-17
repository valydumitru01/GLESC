/**************************************************************************************************
 * @file   GapiDebugger.h
 * @author Valentin Dumitru
 * @date   04/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <string>
#include "engine/core/low-level-renderer/graphic-api/GapiEnums.h"

namespace GLESC::GAPI::Enums{


inline std::string toString(TypeCount typeCount) {
    return std::to_string(static_cast<unsigned>(typeCount));
}

inline std::string toString(Texture::GPUBufferFormat internalFormat){
        switch (internalFormat) {
            case Texture::GPUBufferFormat::R8:return "R8";
            case Texture::GPUBufferFormat::R8_SNORM:return "R8_SNORM";
            case Texture::GPUBufferFormat::R16:return "R16";
            case Texture::GPUBufferFormat::R16_SNORM:return "R16_SNORM";
            case Texture::GPUBufferFormat::RG8:return "RG8";
            case Texture::GPUBufferFormat::RG8_SNORM:return "RG8_SNORM";
            case Texture::GPUBufferFormat::RG16:return "RG16";
            case Texture::GPUBufferFormat::RG16_SNORM:return "RG16_SNORM";
            case Texture::GPUBufferFormat::R3_G3_B2:return "R3_G3_B2";
            case Texture::GPUBufferFormat::RGB:return "RGB";
            case Texture::GPUBufferFormat::RGBA:return "RGBA";
            case Texture::GPUBufferFormat::RGB4:return "RGB4";
            case Texture::GPUBufferFormat::RGB5:return "RGB5";
            case Texture::GPUBufferFormat::RGB8:return "RGB8";
            case Texture::GPUBufferFormat::RGB8_SNORM:return "RGB8_SNORM";
            case Texture::GPUBufferFormat::RGB10:return "RGB10";
            case Texture::GPUBufferFormat::RGB12:return "RGB12";
            case Texture::GPUBufferFormat::RGB16_SNORM:return "RGB16_SNORM";
            case Texture::GPUBufferFormat::RGBA2:return "RGBA2";
            case Texture::GPUBufferFormat::RGBA4:return "RGBA4";
            case Texture::GPUBufferFormat::RGB5_A1:return "RGB5_A1";
            case Texture::GPUBufferFormat::RGBA8:return "RGBA8";
            case Texture::GPUBufferFormat::RGBA8_SNORM:return "RGBA8_SNORM";
            case Texture::GPUBufferFormat::RGB10_A2:return "RGB10_A2";
            case Texture::GPUBufferFormat::RGB10_A2UI:return "RGB10_A2UI";
            case Texture::GPUBufferFormat::RGBA12:return "RGBA12";
            case Texture::GPUBufferFormat::RGBA16:return "RGBA16";
            case Texture::GPUBufferFormat::SRGB8:return "SRGB8";
            case Texture::GPUBufferFormat::SRGB8_ALPHA8:return "SRGB8_ALPHA8";
            case Texture::GPUBufferFormat::R16F:return "R16F";
            case Texture::GPUBufferFormat::RG16F:return "RG16F";
            case Texture::GPUBufferFormat::RGB16F:return "RGB16F";
            case Texture::GPUBufferFormat::RGBA16F:return "RGBA16F";
            case Texture::GPUBufferFormat::R32F:return "R32F";
            case Texture::GPUBufferFormat::RG32F:return "RG32F";
            case Texture::GPUBufferFormat::RGB32F:return "RGB32F";
            case Texture::GPUBufferFormat::RGBA32F:return "RGBA32F";
            case Texture::GPUBufferFormat::R11F_G11F_B10F:return "R11F_G11F_B10F";
            case Texture::GPUBufferFormat::RGB9_E5:return "RGB9_E5";
            case Texture::GPUBufferFormat::R8I:return "R8I";
            case Texture::GPUBufferFormat::R8UI:return "R8UI";
            case Texture::GPUBufferFormat::R16I:return "R16I";
            case Texture::GPUBufferFormat::R16UI:return "R16UI";
            case Texture::GPUBufferFormat::R32I:return "R32I";
            case Texture::GPUBufferFormat::R32UI:return "R32UI";
            case Texture::GPUBufferFormat::RG8I:return "RG8I";
            case Texture::GPUBufferFormat::RG8UI:return "RG8UI";
            case Texture::GPUBufferFormat::RG16I:return "RG16I";
            case Texture::GPUBufferFormat::RG16UI:return "RG16UI";
            case Texture::GPUBufferFormat::RG32I:return "RG32I";
            case Texture::GPUBufferFormat::RG32UI:return "RG32UI";
            case Texture::GPUBufferFormat::RGB8I:return "RGB8I";
            case Texture::GPUBufferFormat::RGB8UI:return "RGB8UI";
            case Texture::GPUBufferFormat::RGB16I:return "RGB16I";
            case Texture::GPUBufferFormat::RGB16UI:return "RGB16UI";
            case Texture::GPUBufferFormat::RGB32I:return "RGB32I";
            case Texture::GPUBufferFormat::RGB32UI:return "RGB32UI";
            case Texture::GPUBufferFormat::RGBA8I:return "RGBA8I";
            case Texture::GPUBufferFormat::RGBA8UI:return "RGBA8UI";
            case Texture::GPUBufferFormat::RGBA16I:return "RGBA16I";
            case Texture::GPUBufferFormat::RGBA16UI:return "RGBA16UI";
            case Texture::GPUBufferFormat::RGBA32I:return "RGBA32I";
            case Texture::GPUBufferFormat::RGBA32UI:return "RGBA32UI";
            case Texture::GPUBufferFormat::DEPTH_COMPONENT16:return "DEPTH_COMPONENT16";
            case Texture::GPUBufferFormat::DEPTH_COMPONENT24:return "DEPTH_COMPONENT24";
            case Texture::GPUBufferFormat::DEPTH_COMPONENT32F:return "DEPTH_COMPONENT32F";
            case Texture::GPUBufferFormat::DEPTH24_STENCIL8:return "DEPTH24_STENCIL8";
            case Texture::GPUBufferFormat::DEPTH32F_STENCIL8:return "DEPTH32F_STENCIL8";
            case Texture::GPUBufferFormat::STENCIL_INDEX8:return "STENCIL_INDEX8";
            default: return "Invalid type";
            
        }
}
inline std::string  toString(Texture::CPUBufferFormat format){
    switch (format) {
        case Texture::CPUBufferFormat::R:return "R";
        case Texture::CPUBufferFormat::RG:return "RG";
        case Texture::CPUBufferFormat::RGB:return "RGB";
        case Texture::CPUBufferFormat::RGBA:return "RGBA";
        case Texture::CPUBufferFormat::BGR:return "BGR";
        case Texture::CPUBufferFormat::BGRA:return "BGRA";
        case Texture::CPUBufferFormat::DepthComponent:return "DepthComponent";
        case Texture::CPUBufferFormat::DepthStencil:return "DepthStencil";
        default: return "Invalid type";
    }
}

inline std::string toString(Types type) {
    switch (type) {
        case Types::Float: return "Float";
        case Types::Int: return "Int";
        case Types::UInt:return "UInt";
        case Types::Bool:return "Bool";
        case Types::UByte:return "UByte";
        case Types::Byte:return "Byte";
        case Types::Short:return "Short";
        case Types::UShort:return "UShort";
        case Types::Vec2F:return "Vec2F";
        case Types::Vec3F:return "Vec3F";
        case Types::Vec4F:return "Vec4F";
        case Types::Vec2I:return "Vec2I";
        case Types::Vec3I:return "Vec3I";
        case Types::Vec4I:return "Vec4I";
        case Types::Vec2UI:return "Vec2UI";
        case Types::Vec3UI:return "Vec3UI";
        case Types::Vec4UI:return "Vec4UI";
        case Types::Vec2B:return "Vec2B";
        case Types::Vec3B:return "Vec3B";
        case Types::Vec4B:return "Vec4B";
        case Types::Mat2F:return "Mat2F";
        case Types::Mat3F:return "Mat3F";
        case Types::Mat4F:return "Mat4F";
        default: return "Invalid type";
    }
}

inline std::string toString(BufferTypes type) {
    switch (type) {
        case BufferTypes::Vertex:return "Vertex";
        case BufferTypes::Index:return "Index";
        default: return "Invalid type";
    }
}

inline std::string toString(BufferUsages type) {
    switch (type) {
        case BufferUsages::StaticDraw:return "StaticDraw";
        case BufferUsages::DynamicDraw:return "DynamicDraw";
        case BufferUsages::StreamDraw:return "StreamDraw";
        case BufferUsages::StaticRead:return "StaticRead";
        case BufferUsages::DynamicRead:return "DynamicRead";
        case BufferUsages::StreamRead:return "StreamRead";
        default: return "Invalid type";
    }
}

inline std::string toString(ClearBits type) {
    switch (type) {
        case ClearBits::Color:return "Color";
        case ClearBits::Depth:return "Depth";
        case ClearBits::Stencil:return "Stencil";
        default: return "Invalid type";
    }
}

inline std::string toString(ShaderTypes type) {
    switch (type) {
        case ShaderTypes::Vertex:return "Vertex";
        case ShaderTypes::Fragment:return "Fragment";
        default: return "Invalid type";
    }
}

inline std::string toString(StencilParameters type) {
    switch (type) {
        case StencilParameters::StencilTest:return "StencilTest";
        case StencilParameters::StencilFail:return "StencilFail";
        case StencilParameters::StencilFunc:return "StencilFunc";
        case StencilParameters::StencilRef:return "StencilRef";
        case StencilParameters::StencilValueMask:return "StencilValueMask";
        case StencilParameters::StencilWriteMask:return "StencilWriteMask";
        case StencilParameters::StencilClearValue:return "StencilClearValue";
        case StencilParameters::StencilPassDepthFail:return "StencilPassDepthFail";
        case StencilParameters::StencilPassDepthPass:return "StencilPassDepthPass";
        case StencilParameters::StencilBackFunc:return "StencilBackFunc";
        case StencilParameters::StencilBackFail:return "StencilBackFail";
        case StencilParameters::StencilBackPassDepthFail:return "StencilBackPassDepthFail";
        case StencilParameters::StencilBackPassDepthPass:return "StencilBackPassDepthPass";
        case StencilParameters::StencilBackRef:return "StencilBackRef";
        case StencilParameters::StencilBackValueMask:return "StencilBackValueMask";
        case StencilParameters::StencilBackWriteMask:return "StencilBackWriteMask";
        default: return "Invalid type";
    }
}

inline std::string toString(DepthParameters type) {
    switch (type) {
        case DepthParameters::DepthTest:return "DepthTest";
        case DepthParameters::DepthFunc:return "DepthFunc";
        default: return "Invalid type";
    }
}

inline std::string toString(BlendingParameters type) {
    switch (type) {
        case BlendingParameters::Blending:return "Blending";
        case BlendingParameters::BlendEquationRGB:return "BlendEquationRGB";
        case BlendingParameters::BlendEquationAlpha:return "BlendEquationAlpha";
        case BlendingParameters::BlendDstRGB:return "BlendDstRGB";
        case BlendingParameters::BlendSrcRGB:return "BlendSrcRGB";
        case BlendingParameters::BlendDstAlpha:return "BlendDstAlpha";
        case BlendingParameters::BlendSrcAlpha:return "BlendSrcAlpha";
        case BlendingParameters::BlendColor:return "BlendColor";
        default: return "Invalid type";
    }
}

inline std::string toString(CullingParameters type) {
    switch (type) {
        case CullingParameters::Culling:return "Culling";
        case CullingParameters::CullFaceMode:return "CullFaceMode";
        case CullingParameters::FrontFace:return "FrontFace";
        default: return "Invalid type";
    }
}

inline std::string toString(PolygonModeParameters type) {
    switch (type) {
        case PolygonModeParameters::PolygonMode:return "PolygonMode";
        default: return "Invalid type";
    }
}

inline std::string toString(PrimitiveTypes type) {
    switch (type) {
        case PrimitiveTypes::Triangles:return "Triangles";
        case PrimitiveTypes::Lines:return "Lines";
        case PrimitiveTypes::Points:return "Points";
        default: return "Invalid type";
    }
}

inline std::string toString(Capabilities type) {
    switch (type) {
        case Capabilities::DepthTest:return "DepthTest";
        case Capabilities::StencilTest:return "StencilTest";
        case Capabilities::Blending:return "Blending";
        case Capabilities::Culling:return "Culling";
        default: return "Invalid type";
    }
}

inline std::string toString(Texture::Types type) {
    switch (type) {
        case Texture::Types::Texture2D:return "Texture2D";
        case Texture::Types::Texture3D:return "Texture3D";
        case Texture::Types::TextureCubeMap:return "TextureCubeMap";
        case Texture::Types::Texture2DArray:return "Texture2DArray";
        case Texture::Types::TextureCubeMapArray:return "TextureCubeMapArray";
        case Texture::Types::Texture2DMultisample:return "Texture2DMultisample";
        case Texture::Types::Texture2DMultisampleArray:return "Texture2DMultisampleArray";
        default: return "Invalid type";
    }
}

}