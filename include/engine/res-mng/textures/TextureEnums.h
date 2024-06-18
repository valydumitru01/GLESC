/**************************************************************************************************
 * @file   TextureEnums.h
 * @author Valentin Dumitru
 * @date   28/04/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

namespace GLESC::ResMng::Texture {
    enum class ColorFormat {
        RGB [[maybe_unused]],
        RGBA [[maybe_unused]],
        BGR [[maybe_unused]],
        BGRA [[maybe_unused]],
        Depth [[maybe_unused]],
        Stencil [[maybe_unused]],
        DepthStencil [[maybe_unused]]
    }; // enum class Format

    enum class BitDepth {
        Bit8 [[maybe_unused]] = 8,
        Bit16 [[maybe_unused]] = 16,
        Bit24 [[maybe_unused]] = 24,
        Bit32 [[maybe_unused]] = 32
    }; // enum class BitDepth

    [[nodiscard]] inline std::string toString(const ColorFormat& format) {
        switch (format) {
        case ColorFormat::RGB:
            return "RGB";
        case ColorFormat::RGBA:
            return "RGBA";
        case ColorFormat::BGR:
            return "BGR";
        case ColorFormat::BGRA:
            return "BGRA";
        case ColorFormat::Depth:
            return "Depth";
        case ColorFormat::Stencil:
            return "Stencil";
        case ColorFormat::DepthStencil:
            return "DepthStencil";
        default:
            return "Unknown";
        }
    }

    [[nodiscard]] inline std::string toString(const BitDepth& bitDepth) {
        switch (bitDepth) {
        case BitDepth::Bit8:
            return "8";
        case BitDepth::Bit16:
            return "16";
        case BitDepth::Bit24:
            return "24";
        case BitDepth::Bit32:
            return "32";
        default:
            return "Unknown";
        }
    }
} // namespace GLESC::ResMng::Texture
