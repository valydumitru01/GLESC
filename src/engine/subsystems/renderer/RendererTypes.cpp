/**************************************************************************************************
 * @file   RendererTypes.cpp
 * @author Valentin Dumitru
 * @date   2024-05-02
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/renderer/RendererTypes.h"
using namespace GLESC::Render;
ColorRgb::ColorRgb(const ColorRgba& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
}
ColorRgb::ColorRgb(ColorRgba& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
}
ColorRgba::ColorRgba(ColorRgb& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
    this->setA(1.0f);
}

ColorRgba::ColorRgba(const ColorRgb& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
    this->setA(1.0f);
}

const ColorRgb ColorRgb::RED = ColorRgb(255.0f, 0.0f, 0.0f);
const ColorRgb ColorRgb::GREEN = ColorRgb(0.0f, 255.0f, 0.0f);
const ColorRgb ColorRgb::BLUE = ColorRgb(0.0f, 0.0f, 255.0f);
const ColorRgb ColorRgb::WHITE = ColorRgb(255.0f, 255.0f, 255.0f);
const ColorRgb ColorRgb::BLACK = ColorRgb(0.0f, 0.0f, 0.0f);
const ColorRgb ColorRgb::YELLOW = ColorRgb(255.0f, 255.0f, 0.0f);
const ColorRgb ColorRgb::CYAN = ColorRgb(0.0f, 255.0f, 255.0f);
const ColorRgb ColorRgb::MAGENTA = ColorRgb(255.0f, 0.0f, 255.0f);
const ColorRgb ColorRgb::ORANGE = ColorRgb(255.0f, 165.0f, 0.0f);
const ColorRgb ColorRgb::PURPLE = ColorRgb(128.0f, 0.0f, 128.0f);
const ColorRgb ColorRgb::PINK = ColorRgb(255.0f, 192.0f, 203.0f);
const ColorRgb ColorRgb::BROWN = ColorRgb(165.0f, 64.0f, 0.0f);
const ColorRgb ColorRgb::DARK_BROWN = ColorRgb(110.0f, 44.0f, 0.0f);
const ColorRgb ColorRgb::GREY = ColorRgb(128.0f, 128.0f, 128.0f);
const ColorRgb ColorRgb::LIGHT_GREY = ColorRgb(211.0f, 211.0f, 211.0f);
const ColorRgb ColorRgb::DARK_GREY = ColorRgb(169.0f, 169.0f, 169.0f);