/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <optional>
#include <string>
#include "engine/core/math/Vector.h"

namespace GLESC {
/**
 * @brief The vertex data of the mesh
 * @details This struct contains all the data of the vertex.
 * This can be modified to add all the data that is needed for the vertex.
 */
    struct Vertex {
        /**
         * @brief The default color of the vertex
         */
        inline static const Vector4D defaultVertexColor = Vector4D(0, 0, 0, 1);
        
        Vertex() = default;
        
        /**
         * @brief Constructor for all the data
         * @details This constructor is useful to refactor the constructor.
         * This constructor will be called by the other constructors.
         * And when a parameter is empty, it will receive nullopt for
         * that parameter or the default value.
         * @param position
         * @param color
         * @param uv
         */
        explicit Vertex(const Vector3D &position,
                        const std::optional<Vector4F> &color,
                        const std::optional<Vector2F> &uv);
        
        /**
         * @brief Constructor for just the position,
         * it will use the default color and there
         * will be no uvs and therefore no textures.
         * @param position
         */
        Vertex(const Vector3D &position);
        
        Vertex(const double x, const double y, const double z) :
                Vertex(Vector3D(x, y, z)) {}
        
        /**
         * @brief Constructor for position and color, if there are colors,
         * there are no uvs and no textures
         * @param position The position of the vertex
         * @param color The color of the vertex
         */
        explicit Vertex(const Vector3D &position, const Vector4F &color);
        
        Vertex(const double x, const double y, const double z, const float r,
               const float g, const float b, const float a) :
                Vertex(Vector3D(x, y, z), Vector4F(r, g, b, a)) {}
        
        /**
         * @brief Constructor for position and uv, if there are uvs,
         * there must be a texture and no colors are needed
         * @param position
         * @param uv
         */
        explicit Vertex(const Vector3D &position, const Vector2F &uv);
        
        Vertex(const double x, const double y, const double z, const float u,
               const float v) :
                Vertex(Vector3D(x, y, z), Vector2F(u, v)) {}
        
        /**
         * @brief Compares two vertices
         * @details Compares all the data in the vertex, if all the data is the same
         * then the vertices are the same.
         * For vertices this operator is very important.
         * @param other
         * @return true if the vertices are the same, false otherwise
         */
        bool operator==(const Vertex &other) const;
        
        bool operator<(const Vertex &other) const;
        
        [[nodiscard]] Vector3D getPosition() const;
        
        [[nodiscard]] std::optional<Vector4F> getColor() const;
        
        [[nodiscard]] std::optional<Vector2F> getUv() const;
        
        void setPosition(const Vector3D &positionParam);
        
        void setColor(const Vector4F &colorParam);
        
        void setUv(const Vector2F &uvParam);
        
        
        [[nodiscard]] std::string toString() const;
    
    private:
        /**
         * @brief The position of the vertex
         * @details The position of the vertex in the 3D space, we
         * are using doubles because we want to be as precise as possible.
         * For multiplayer games this is more optimal (but uses
         * more memory and is slower), but for single player
         * can be changed to floats and use floating origin so that
         * the world moves around the player instead of vice versa.
         */
        Vector3D position;
        /**
         * @brief The color of the vertex
         * @details The color of the vertex, it is optional because
         * if there are colors, there are no uvs and no textures.
         * It should be values between 0.0 and 1.0, and RGBA
         * (red, green, blue, alpha)
         */
        std::optional<Vector4F> color;
        /**
         * @brief The uv of the vertex, UVs are used for textures
         * @details The uv of the vertex, it is optional because
         * if there are uvs, there must be a texture and no colors are needed.
         * Uvs are used to map textures to the mesh.
         * It should be values between 0.0 and 1.0.
         */
        std::optional<Vector2F> uv;
    };
    
    
}

namespace std {
    template<>
    struct hash<GLESC::Vertex> {
        std::size_t operator()(const GLESC::Vertex &v) const {
            // We must take into consideration the optional values
            auto hash1 = std::hash<Vector3D>()(v.getPosition());
            
            if (v.getColor().has_value()) {
                auto hash2 = std::hash<Vector4F>()(v.getColor().value());
                return hash1 ^ hash2;
            }
            
            if (v.getUv().has_value()) {
                auto hash2 = std::hash<Vector2F>()(v.getUv().value());
                return hash1 ^ hash2;
            }
            
            return hash1;
        }
    };
}