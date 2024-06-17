/**************************************************************************************************
 * @file   TextureAdapter.h
 * @author Valentin Dumitru
 * @date   28/04/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/asserts/Asserts.h"
#include "engine/core/low-level-renderer/graphic-api/GapiEnums.h"
#include "engine/res-mng/textures/TextureEnums.h"
using namespace GLESC::GAPI;
[[nodisacrd]] static Enums::Texture::CPUBufferFormat getTextureInputFormat( const
    GLESC::ResMng::Texture::ColorFormat format) {
    switch (format) {
    case GLESC::ResMng::Texture::ColorFormat::RGB:
        return Enums::Texture::CPUBufferFormat::RGB;
    case GLESC::ResMng::Texture::ColorFormat::RGBA:
        return Enums::Texture::CPUBufferFormat::RGBA;
    default:
        D_ASSERT_TRUE(false, "Invalid texture format");
        return Enums::Texture::CPUBufferFormat::RGB;
    }
}

[[nodisacrd]] static Enums::Texture::BitDepth
getTextureBitDepth(const GLESC::ResMng::Texture::BitDepth bitDepth) {
    switch (bitDepth) {
    case GLESC::ResMng::Texture::BitDepth::Bit8:
        return Enums::Texture::BitDepth::Bit8;
    case GLESC::ResMng::Texture::BitDepth::Bit16:
        return Enums::Texture::BitDepth::Bit16;
    case GLESC::ResMng::Texture::BitDepth::Bit24:
        return Enums::Texture::BitDepth::Bit24;
    case GLESC::ResMng::Texture::BitDepth::Bit32:
        return Enums::Texture::BitDepth::Bit32;
    default:
        D_ASSERT_TRUE(false, "Invalid texture bit depth");
        return Enums::Texture::BitDepth::Bit8;
    }
}
