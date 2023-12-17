/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

/******************************************************************************
 * @file   Vertex.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief  Vertex class implementation.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/mesh/Vertex.h"
#include <sstream>
#include <utility>

namespace GLESC {
    Vertex::Vertex(Vec3D position, Vec3D normal, RGBA color, Vec2F uv, int textureIndex) :
            position(std::move(position)), normal(std::move(normal)), color(color), uv(
            std::move(uv)), textureIndex(textureIndex) {}
    
    Vertex::Vertex(const Vec3D &position, const Vec2F &uv, int textureIndex) :
            Vertex(position, Vec3D(0.0f, 0.0f, 0.0f), RGBA(0.0f, 0.0f, 0.0f, 0.0f), uv,
                   textureIndex) {}
    
    
    Vertex::Vertex(const Vec3D &position, const RGBA &color) :
            Vertex(position, Vec3D(0.0f, 0.0f, 0.0f), color, Vec2F(0.0f, 0.0f), 0) {}
    
    
    // Position and normal
    Vec3D Vertex::getPosition() const {
        return position;
    }
    
    void Vertex::setPosition(const Vec3D &positionParam) {
        position = positionParam;
    }
    
    Vec3D Vertex::getNormal() const {
        return normal;
    }
    
    void Vertex::setNormal(const Vec3D &normalParam) {
        normal = normalParam;
    }
    
    // Color
    RGBA Vertex::getColor() const {
        return color;
    }
    
    void Vertex::setColor(const RGBA &colorParam) {
        color = colorParam;
    }
    
    // Texture
    Vec2F Vertex::getUv() const {
        return uv;
    }
    
    void Vertex::setUv(const Vec2F &uvParam) {
        uv = uvParam;
    }
    
    int Vertex::getTextureIndex() const {
        return textureIndex;
    }
    
    void Vertex::setTextureIndex(int textureIndexParam) {
        textureIndex = textureIndexParam;
    }
    
    // ToString
    std::string Vertex::toString() const {
        std::stringstream ss;
        ss << "Vertex\n";
        ss << "Position: " << position.toString() << "\n";
        ss << "Normal: " << normal.toString() << "\n";
        ss << "Color: " << color.toString() << "\n";
        ss << "UV: " << uv.toString() << "\n";
        ss << "Texture Index: " << textureIndex << "\n";
        return ss.str();
    }
    
    // Operators
    bool Vertex::operator==(const Vertex &other) const {
        return position == other.position && normal == other.normal && color == other.color &&
               uv == other.uv && textureIndex == other.textureIndex;
    }
    
    bool Vertex::operator<(const Vertex &other) const {
        return position < other.position && normal < other.normal && color < other.color &&
               uv < other.uv && textureIndex < other.textureIndex;
    }
    
} // namespace GLESC

namespace std {
    std::size_t hash<GLESC::Vertex>::operator()(const GLESC::Vertex &v) const {
        auto hash1 = std::hash<Vec3D>()(v.getPosition());
        auto hash2 = std::hash<Vec3D>()(v.getNormal());
        auto hash3 = std::hash<RGBA>()(v.getColor());
        auto hash4 = std::hash<Vec2F>()(v.getUv());
        auto hash5 = std::hash<int>()(v.getTextureIndex());
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2) ^ (hash4 << 3) ^ (hash5 << 4);
    }
}