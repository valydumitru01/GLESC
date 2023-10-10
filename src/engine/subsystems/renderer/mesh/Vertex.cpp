/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/mesh/Vertex.h"
using namespace GLESC;
Vertex::Vertex(const Vec3D &position,
               const std::optional<Vec4F> &color,
               const std::optional<Vec2F> &uv) :
        position(position), color(color), uv(uv) {}

Vertex::Vertex(const Vec3D &position)  :
        Vertex(position, std::nullopt, std::nullopt) {}

Vertex::Vertex(const Vec3D &position, const Vec4F &color)  :
        Vertex(position, color, std::nullopt) {}

Vertex::Vertex(const Vec3D &position, const Vec2F &uv)  :
        Vertex(position, std::nullopt, uv) {}

bool Vertex::operator==(const Vertex &other) const {
    return position == other.position && color == other.color && uv == other.uv;
}

bool Vertex::operator<(const Vertex &other) const {
    return position < other.position && color < other.color && uv < other.uv;
}


Vec3D Vertex::getPosition() const {
    return position;
}

std::optional<Vec4F> Vertex::getColor() const {
    return color;
}

std::optional<Vec2F> Vertex::getUv() const {
    return uv;
}

void Vertex::setPosition(const Vec3D &positionParam) {
    Vertex::position = positionParam;
}

void Vertex::setColor(const Vec4F &colorParam) {
    Vertex::color = colorParam;
}

void Vertex::setUv(const Vec2F &uvParam) {
    Vertex::uv = uvParam;
}

std::string Vertex::toString() const{
    std::string result = "Vertex: \n";
    result += "Position: " + position.toString() + "\n";
    if (color.has_value()) {
        result += "Color: " + color.value().toString() + "\n";
    }
    if (uv.has_value()) {
        result += "UV: " + uv.value().toString() + "\n";
    }
    return result;
}