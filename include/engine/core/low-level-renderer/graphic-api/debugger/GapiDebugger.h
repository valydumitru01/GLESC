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
#include "engine/core/asserts/Asserts.h"

namespace GAPI{


inline std::string toString(GAPI::TypeCount typeCount) {
    return std::to_string(static_cast<unsigned>(typeCount));
}

inline std::string toString(GAPI::Texture::GPUBufferFormat internalFormat){
        switch (internalFormat) {
            case GAPI::Texture::GPUBufferFormat::R8:return "R8";
            case GAPI::Texture::GPUBufferFormat::R8_SNORM:return "R8_SNORM";
            case GAPI::Texture::GPUBufferFormat::R16:return "R16";
            case GAPI::Texture::GPUBufferFormat::R16_SNORM:return "R16_SNORM";
            case GAPI::Texture::GPUBufferFormat::RG8:return "RG8";
            case GAPI::Texture::GPUBufferFormat::RG8_SNORM:return "RG8_SNORM";
            case GAPI::Texture::GPUBufferFormat::RG16:return "RG16";
            case GAPI::Texture::GPUBufferFormat::RG16_SNORM:return "RG16_SNORM";
            case GAPI::Texture::GPUBufferFormat::R3_G3_B2:return "R3_G3_B2";
            case GAPI::Texture::GPUBufferFormat::RGB:return "RGB";
            case GAPI::Texture::GPUBufferFormat::RGBA:return "RGBA";
            case GAPI::Texture::GPUBufferFormat::RGB4:return "RGB4";
            case GAPI::Texture::GPUBufferFormat::RGB5:return "RGB5";
            case GAPI::Texture::GPUBufferFormat::RGB8:return "RGB8";
            case GAPI::Texture::GPUBufferFormat::RGB8_SNORM:return "RGB8_SNORM";
            case GAPI::Texture::GPUBufferFormat::RGB10:return "RGB10";
            case GAPI::Texture::GPUBufferFormat::RGB12:return "RGB12";
            case GAPI::Texture::GPUBufferFormat::RGB16_SNORM:return "RGB16_SNORM";
            case GAPI::Texture::GPUBufferFormat::RGBA2:return "RGBA2";
            case GAPI::Texture::GPUBufferFormat::RGBA4:return "RGBA4";
            case GAPI::Texture::GPUBufferFormat::RGB5_A1:return "RGB5_A1";
            case GAPI::Texture::GPUBufferFormat::RGBA8:return "RGBA8";
            case GAPI::Texture::GPUBufferFormat::RGBA8_SNORM:return "RGBA8_SNORM";
            case GAPI::Texture::GPUBufferFormat::RGB10_A2:return "RGB10_A2";
            case GAPI::Texture::GPUBufferFormat::RGB10_A2UI:return "RGB10_A2UI";
            case GAPI::Texture::GPUBufferFormat::RGBA12:return "RGBA12";
            case GAPI::Texture::GPUBufferFormat::RGBA16:return "RGBA16";
            case GAPI::Texture::GPUBufferFormat::SRGB8:return "SRGB8";
            case GAPI::Texture::GPUBufferFormat::SRGB8_ALPHA8:return "SRGB8_ALPHA8";
            case GAPI::Texture::GPUBufferFormat::R16F:return "R16F";
            case GAPI::Texture::GPUBufferFormat::RG16F:return "RG16F";
            case GAPI::Texture::GPUBufferFormat::RGB16F:return "RGB16F";
            case GAPI::Texture::GPUBufferFormat::RGBA16F:return "RGBA16F";
            case GAPI::Texture::GPUBufferFormat::R32F:return "R32F";
            case GAPI::Texture::GPUBufferFormat::RG32F:return "RG32F";
            case GAPI::Texture::GPUBufferFormat::RGB32F:return "RGB32F";
            case GAPI::Texture::GPUBufferFormat::RGBA32F:return "RGBA32F";
            case GAPI::Texture::GPUBufferFormat::R11F_G11F_B10F:return "R11F_G11F_B10F";
            case GAPI::Texture::GPUBufferFormat::RGB9_E5:return "RGB9_E5";
            case GAPI::Texture::GPUBufferFormat::R8I:return "R8I";
            case GAPI::Texture::GPUBufferFormat::R8UI:return "R8UI";
            case GAPI::Texture::GPUBufferFormat::R16I:return "R16I";
            case GAPI::Texture::GPUBufferFormat::R16UI:return "R16UI";
            case GAPI::Texture::GPUBufferFormat::R32I:return "R32I";
            case GAPI::Texture::GPUBufferFormat::R32UI:return "R32UI";
            case GAPI::Texture::GPUBufferFormat::RG8I:return "RG8I";
            case GAPI::Texture::GPUBufferFormat::RG8UI:return "RG8UI";
            case GAPI::Texture::GPUBufferFormat::RG16I:return "RG16I";
            case GAPI::Texture::GPUBufferFormat::RG16UI:return "RG16UI";
            case GAPI::Texture::GPUBufferFormat::RG32I:return "RG32I";
            case GAPI::Texture::GPUBufferFormat::RG32UI:return "RG32UI";
            case GAPI::Texture::GPUBufferFormat::RGB8I:return "RGB8I";
            case GAPI::Texture::GPUBufferFormat::RGB8UI:return "RGB8UI";
            case GAPI::Texture::GPUBufferFormat::RGB16I:return "RGB16I";
            case GAPI::Texture::GPUBufferFormat::RGB16UI:return "RGB16UI";
            case GAPI::Texture::GPUBufferFormat::RGB32I:return "RGB32I";
            case GAPI::Texture::GPUBufferFormat::RGB32UI:return "RGB32UI";
            case GAPI::Texture::GPUBufferFormat::RGBA8I:return "RGBA8I";
            case GAPI::Texture::GPUBufferFormat::RGBA8UI:return "RGBA8UI";
            case GAPI::Texture::GPUBufferFormat::RGBA16I:return "RGBA16I";
            case GAPI::Texture::GPUBufferFormat::RGBA16UI:return "RGBA16UI";
            case GAPI::Texture::GPUBufferFormat::RGBA32I:return "RGBA32I";
            case GAPI::Texture::GPUBufferFormat::RGBA32UI:return "RGBA32UI";
            case GAPI::Texture::GPUBufferFormat::DEPTH_COMPONENT16:return "DEPTH_COMPONENT16";
            case GAPI::Texture::GPUBufferFormat::DEPTH_COMPONENT24:return "DEPTH_COMPONENT24";
            case GAPI::Texture::GPUBufferFormat::DEPTH_COMPONENT32F:return "DEPTH_COMPONENT32F";
            case GAPI::Texture::GPUBufferFormat::DEPTH24_STENCIL8:return "DEPTH24_STENCIL8";
            case GAPI::Texture::GPUBufferFormat::DEPTH32F_STENCIL8:return "DEPTH32F_STENCIL8";
            case GAPI::Texture::GPUBufferFormat::STENCIL_INDEX8:return "STENCIL_INDEX8";
            
        }
}
inline std::string  toString(GAPI::Texture::CPUBufferFormat format){
    switch (format) {
        case GAPI::Texture::CPUBufferFormat::R:return "R";
        case GAPI::Texture::CPUBufferFormat::RG:return "RG";
        case GAPI::Texture::CPUBufferFormat::RGB:return "RGB";
        case GAPI::Texture::CPUBufferFormat::RGBA:return "RGBA";
        case GAPI::Texture::CPUBufferFormat::BGR:return "BGR";
        case GAPI::Texture::CPUBufferFormat::BGRA:return "BGRA";
        case GAPI::Texture::CPUBufferFormat::DepthComponent:return "DepthComponent";
        case GAPI::Texture::CPUBufferFormat::DepthStencil:return "DepthStencil";
        default: "Invalid format";
    }
}

inline std::string toString(GAPI::Types type) {
    switch (type) {
        case GAPI::Types::Float: return "Float";
        case GAPI::Types::Int: return "Int";
        case GAPI::Types::UInt:return "UInt";
        case GAPI::Types::Bool:return "Bool";
        case GAPI::Types::UByte:return "UByte";
        case GAPI::Types::Byte:return "Byte";
        case GAPI::Types::Short:return "Short";
        case GAPI::Types::UShort:return "UShort";
        case GAPI::Types::Vec2F:return "Vec2F";
        case GAPI::Types::Vec3F:return "Vec3F";
        case GAPI::Types::Vec4F:return "Vec4F";
        case GAPI::Types::Vec2I:return "Vec2I";
        case GAPI::Types::Vec3I:return "Vec3I";
        case GAPI::Types::Vec4I:return "Vec4I";
        case GAPI::Types::Vec2UI:return "Vec2UI";
        case GAPI::Types::Vec3UI:return "Vec3UI";
        case GAPI::Types::Vec4UI:return "Vec4UI";
        case GAPI::Types::Vec2B:return "Vec2B";
        case GAPI::Types::Vec3B:return "Vec3B";
        case GAPI::Types::Vec4B:return "Vec4B";
        case GAPI::Types::Mat2F:return "Mat2F";
        case GAPI::Types::Mat3F:return "Mat3F";
        case GAPI::Types::Mat4F:return "Mat4F";
        default: return "Invalid type";
    }
}

inline std::string toString(GAPI::BufferTypes type) {
    switch (type) {
        case GAPI::BufferTypes::Vertex:return "Vertex";
        case GAPI::BufferTypes::Index:return "Index";
    }
}

inline std::string toString(GAPI::BufferUsages type) {
    switch (type) {
        case GAPI::BufferUsages::StaticDraw:return "StaticDraw";
        case GAPI::BufferUsages::DynamicDraw:return "DynamicDraw";
        case GAPI::BufferUsages::StreamDraw:return "StreamDraw";
        case GAPI::BufferUsages::StaticRead:return "StaticRead";
        case GAPI::BufferUsages::DynamicRead:return "DynamicRead";
        case GAPI::BufferUsages::StreamRead:return "StreamRead";
    }
}

inline std::string toString(GAPI::ClearBits type) {
    switch (type) {
        case GAPI::ClearBits::Color:return "Color";
        case GAPI::ClearBits::Depth:return "Depth";
        case GAPI::ClearBits::Stencil:return "Stencil";
    }
}

inline std::string toString(GAPI::ShaderTypes type) {
    switch (type) {
        case GAPI::ShaderTypes::Vertex:return "Vertex";
        case GAPI::ShaderTypes::Fragment:return "Fragment";
    }
}

inline std::string toString(GAPI::StencilParameters type) {
    switch (type) {
        case GAPI::StencilParameters::StencilTest:return "StencilTest";
        case GAPI::StencilParameters::StencilFail:return "StencilFail";
        case GAPI::StencilParameters::StencilFunc:return "StencilFunc";
        case GAPI::StencilParameters::StencilRef:return "StencilRef";
        case GAPI::StencilParameters::StencilValueMask:return "StencilValueMask";
        case GAPI::StencilParameters::StencilWriteMask:return "StencilWriteMask";
        case GAPI::StencilParameters::StencilClearValue:return "StencilClearValue";
        case GAPI::StencilParameters::StencilPassDepthFail:return "StencilPassDepthFail";
        case GAPI::StencilParameters::StencilPassDepthPass:return "StencilPassDepthPass";
        case GAPI::StencilParameters::StencilBackFunc:return "StencilBackFunc";
        case GAPI::StencilParameters::StencilBackFail:return "StencilBackFail";
        case GAPI::StencilParameters::StencilBackPassDepthFail:return "StencilBackPassDepthFail";
        case GAPI::StencilParameters::StencilBackPassDepthPass:return "StencilBackPassDepthPass";
        case GAPI::StencilParameters::StencilBackRef:return "StencilBackRef";
        case GAPI::StencilParameters::StencilBackValueMask:return "StencilBackValueMask";
        case GAPI::StencilParameters::StencilBackWriteMask:return "StencilBackWriteMask";
    }
}

inline std::string toString(GAPI::DepthParameters type) {
    switch (type) {
        case GAPI::DepthParameters::DepthTest:return "DepthTest";
        case GAPI::DepthParameters::DepthFunc:return "DepthFunc";
    }
}

inline std::string toString(GAPI::BlendingParameters type) {
    switch (type) {
        case GAPI::BlendingParameters::Blending:return "Blending";
        case GAPI::BlendingParameters::BlendEquationRGB:return "BlendEquationRGB";
        case GAPI::BlendingParameters::BlendEquationAlpha:return "BlendEquationAlpha";
        case GAPI::BlendingParameters::BlendDstRGB:return "BlendDstRGB";
        case GAPI::BlendingParameters::BlendSrcRGB:return "BlendSrcRGB";
        case GAPI::BlendingParameters::BlendDstAlpha:return "BlendDstAlpha";
        case GAPI::BlendingParameters::BlendSrcAlpha:return "BlendSrcAlpha";
        case GAPI::BlendingParameters::BlendColor:return "BlendColor";
    }
}

inline std::string toString(GAPI::CullingParameters type) {
    switch (type) {
        case GAPI::CullingParameters::Culling:return "Culling";
        case GAPI::CullingParameters::CullFaceMode:return "CullFaceMode";
        case GAPI::CullingParameters::FrontFace:return "FrontFace";
    }
}

inline std::string toString(GAPI::PolygonModeParameters type) {
    switch (type) {
        case GAPI::PolygonModeParameters::PolygonMode:return "PolygonMode";
    }
}

inline std::string toString(GAPI::PrimitiveTypes type) {
    switch (type) {
        case GAPI::PrimitiveTypes::Triangles:return "Triangles";
        case GAPI::PrimitiveTypes::Lines:return "Lines";
        case GAPI::PrimitiveTypes::Points:return "Points";
    }
}

inline std::string toString(GAPI::Capabilities type) {
    switch (type) {
        case GAPI::Capabilities::DepthTest:return "DepthTest";
        case GAPI::Capabilities::StencilTest:return "StencilTest";
        case GAPI::Capabilities::Blending:return "Blending";
        case GAPI::Capabilities::Culling:return "Culling";
    }
}

inline std::string toString(GAPI::Texture::Types type) {
    switch (type) {
        case GAPI::Texture::Types::Texture2D:return "Texture2D";
        case GAPI::Texture::Types::Texture3D:return "Texture3D";
        case GAPI::Texture::Types::TextureCubeMap:return "TextureCubeMap";
        case GAPI::Texture::Types::Texture2DArray:return "Texture2DArray";
        case GAPI::Texture::Types::TextureCubeMapArray:return "TextureCubeMapArray";
        case GAPI::Texture::Types::Texture2DMultisample:return "Texture2DMultisample";
        case GAPI::Texture::Types::Texture2DMultisampleArray:return "Texture2DMultisampleArray";
    }
}

}