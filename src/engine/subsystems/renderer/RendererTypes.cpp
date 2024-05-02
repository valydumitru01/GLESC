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

GLESC::Render::ColorRgb::ColorRgb(const ColorRgba& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
}
GLESC::Render::ColorRgb::ColorRgb(ColorRgba& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
}
GLESC::Render::ColorRgba::ColorRgba(ColorRgb& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
    this->setA(1.0f);
}

GLESC::Render::ColorRgba::ColorRgba(const ColorRgb& other) noexcept {
    this->setR(other.getR());
    this->setG(other.getG());
    this->setB(other.getB());
    this->setA(1.0f);
}