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


namespace GAPI{
inline std::string toString(GAPI::Texture::InternalFormat::ColorFormat typeCount) {
    switch (typeCount) {
        case GAPI::Texture::InternalFormat::ColorFormat::R:return "R";
        case GAPI::Texture::InternalFormat::ColorFormat::RG:return "RG";
        case GAPI::Texture::InternalFormat::ColorFormat::RGB:return "RGB";
        case GAPI::Texture::InternalFormat::ColorFormat::RGBA:return "RGBA";
    }
}

inline std::string toString(GAPI::Texture::InternalFormat::BitDepth bitDepth) {
    return std::to_string(static_cast<unsigned>(bitDepth));
}

inline std::string toString(GAPI::TypeCount typeCount) {
    return std::to_string(static_cast<unsigned>(typeCount));
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

inline std::string toString(GAPI::Texture::BufferFormat type) {
    switch (type) {
        case GAPI::Texture::BufferFormat::R:return "R";
        case GAPI::Texture::BufferFormat::RG:return "RG";
        case GAPI::Texture::BufferFormat::RGB:return "RGB";
        case GAPI::Texture::BufferFormat::RGBA:return "RGBA";
    }
}
}