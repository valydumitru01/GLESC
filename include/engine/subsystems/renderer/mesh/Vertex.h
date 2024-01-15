#pragma once

#include "engine/core/math/algebra/vector/Vector.h"
#include "engine/core/low-level-renderer/graphic-api/GapiStructs.h"
#include <string>

namespace GLESC {
    
    class Vertex {
    public:
        Vertex(const Vec3D& position, const Vec2F& uv, int textureIndex);
        
        
        Vertex(const Vec3D& position, const RGBA& color);
        
        // Position and normal setters and getters
        [[nodiscard]] Vec3D getPosition() const;
        void setPosition(const Vec3D& position);
        
        [[nodiscard]] Vec3D getNormal() const;
        void setNormal(const Vec3D& normal);
        
        // Color setters and getters
        [[nodiscard]] RGBA getColor() const;
        void setColor(const RGBA& color);
        
        // Texture setters and getters
        [[nodiscard]] Vec2F getUv() const;
        void setUv(const Vec2F& uv);
        
        [[nodiscard]] int getTextureIndex() const;
        void setTextureIndex(int textureIndex);
        
        // ToString method for debugging
        [[nodiscard]] std::string toString() const;
        
        // Operators
        bool operator==(const Vertex& other) const;
        bool operator<(const Vertex& other) const;
    
    private:
        Vertex(Vec3D position, Vec3D normal, RGBA color, Vec2F uv, int textureIndex);
        
        Vec3D position;
        Vec3D normal;
        RGBA color;
        Vec2F uv;
        int textureIndex{-1};
    };
    
} // namespace GLESC

namespace std {
    template<>
    struct hash<GLESC::Vertex> {
        std::size_t operator()(const GLESC::Vertex& v) const;
    };
} // namespace std