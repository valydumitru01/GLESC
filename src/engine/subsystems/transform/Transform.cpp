/**
 * @file   Transform.cpp
 * @author valyd
 * @date   2024-03-28
 * @brief  Brief description of Transform.
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 */
#include "engine/subsystems/transform/Transform.h"

#include <utility>


using namespace GLESC::Transform;

Transform::Transform(Position position, Rotation rotation, Scale scale) :
    position(std::move(position)),
    rotation(std::move(rotation)),
    scale(std::move(scale)) {
}


GLESC::Math::Direction Transform::forward() const {
    RotComp yaw = Math::radians(rotation.getX()); // Rotation around Y-axis (yaw)
    RotComp pitch = Math::radians(rotation.getY()); // Rotation around X-axis (pitch)

    PosComp x = cosf(yaw) * cosf(pitch);
    PosComp y = sinf(pitch);
    PosComp z = -sinf(yaw) * cosf(pitch);

    return Math::Direction(x, y, z).normalize();
}

GLESC::Math::Direction Transform::right() const {
    return forward().cross(worldUp).normalize();
}

GLESC::Math::Direction Transform::up() const {
    return right().cross(forward()).normalize();
}

bool Transform::operator==(const Transform &other) const {
    return position == other.position && rotation == other.rotation && scale == other.scale;
}

std::string Transform::toString() const {
    return "Position: " + position.toString() + "\n" +
           "Rotation: " + rotation.toString() + "\n" +
           "Scale: " + scale.toString();
}


GLESC::Math::Direction Transform::worldUp = Math::Direction(0.0f, 1.0f, 0.0f);
GLESC::Math::Direction Transform::worldRight = Math::Direction(1.0f, 0.0f, 0.0f);
GLESC::Math::Direction Transform::worldForward = Math::Direction(0.0f, 0.0f, 1.0f);


void Transformer::transformMesh(Render::ColorMesh &mesh, const Transform &transform) {
    Render::Model model;
    model.makeModelMatrix(transform.position, transform.rotation, transform.scale);

    for (auto &vertex : mesh.getVertices()) {
        Render::getVertexPositionAttr(vertex) = model * Render::getVertexPositionAttr(vertex);
    }

    transformBoundingVolume(mesh.getBoundingVolumeMutable(), transform);
}

void Transformer::transformBoundingVolume(Render::BoundingVolume &boundingVolume, const Transform &transform) {
    Render::Model model;
    model.makeModelMatrix(transform.position, transform.rotation, transform.scale);

    for (Math::Point &vertex : boundingVolume.getTopologyMutable().getVerticesMutable()) {
        vertex = model * vertex;
    }
}
