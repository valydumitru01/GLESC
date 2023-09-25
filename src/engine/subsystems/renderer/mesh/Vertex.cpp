/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/subsystems/renderer/mesh/Vertex.h"

Vertex::Vertex(const Vector3D &position,
               const Vector4F &color,
               const Vector2F &uv) :
        position(position), color(color), uv(uv) {}

Vertex::Vertex(const Vector3D &position) :
        Vertex(position, defaultVertexColor, std::nullopt) {}

Vertex::Vertex(const Vector3D &position, const Vector4F &color) :
        Vertex(position, color, std::nullopt) {}

Vertex::Vertex(const Vector3D &position, const Vector2F &uv) :
        Vertex(position, defaultVertexColor, uv) {}

bool Vertex::operator==(const Vertex &other) const {
    return position == other.position && color == other.color && uv == other.uv;
}