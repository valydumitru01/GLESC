/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <optional>
#include "engine/core/math/Vector.h"

struct Vertex {
    /**
     * @brief The default color of the vertex
     */
    inline static const Vector4F defaultVertexColor = Vector4F(0, 0, 0, 1);
    
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
                    const Vector4F &color,
                    const Vector2F &uv);
    
    /**
     * @brief Constructor for just the position,
     * it will use the default color and there
     * will be no uvs and therefore no textures.
     * @param position
     */
    explicit Vertex(const Vector3D &position);
    
    /**
     * @brief Constructor for position and color, if there are colors,
     * there are no uvs and no textures
     * @param position The position of the vertex
     * @param color The color of the vertex
     */
    explicit Vertex(const Vector3D &position, const Vector4F &color);
    
    /**
     * @brief Constructor for position and uv, if there are uvs,
     * there must be a texture and no colors are needed
     * @param position
     * @param uv
     */
    explicit Vertex(const Vector3D &position, const Vector2F &uv);
    
    /**
     * @brief Compares two vertices
     * @details Compares all the data in the vertex, if all the data is the same
     * then the vertices are the same.
     * For vertices this operator is very important.
     * @param other
     * @return true if the vertices are the same, false otherwise
     */
    bool operator==(const Vertex &other) const;
    
    
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
     * It should be values between 0.0 and 1.0, and RGBA (red, green, blue, alpha)
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