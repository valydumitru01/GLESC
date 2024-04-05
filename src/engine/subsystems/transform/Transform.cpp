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
    if (dirtyRotation)
        return calculateForward();
    return forwardDirection;
}

GLESC::Math::Direction Transform::right() const {
    if (dirtyRotation)
        return calculateRight();
    return rightDirection;
}

GLESC::Math::Direction Transform::up() const {
    if (dirtyRotation)
        return calculateUp();
    return forwardDirection;
}

GLESC::Math::Direction Transform::calculateForward() const {
    RotComp pitch = Math::radians(rotation.getX()); // Rotation around X-axis (pitch)
    RotComp yaw = Math::radians(rotation.getY()); // Rotation around Y-axis (yaw)

    // TODO: Find why adding 90 degrees to yaw is necessary, it shouldn't be
    //       but if not done, the forward vector is incorrect (is to the left)
    PosComp x = Math::cos(pitch) * Math::cos(yaw + Math::radians(90.0f));
    PosComp y = Math::sin(pitch);
    PosComp z = Math::cos(pitch) * Math::sin(yaw + Math::radians(90.0f));

    return {x, y, z};
}

GLESC::Math::Direction Transform::calculateRight() const {
    return calculateForward().cross(worldUp).normalize();
}

GLESC::Math::Direction Transform::calculateUp() const {
    return calculateRight().cross(calculateForward()).normalize();
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
    model.makeModelMatrix(transform.getPosition(), transform.getRotation(), transform.getScale());

    for (auto &vertex : mesh.getVertices()) {
        Render::getVertexPositionAttr(vertex) = model * Render::getVertexPositionAttr(vertex);
    }

    transformBoundingVolume(mesh.getBoundingVolumeMutable(), transform);
}

void Transformer::transformBoundingVolume(Render::BoundingVolume &boundingVolume, const Transform &transform) {
    Render::Model model;
    model.makeModelMatrix(transform.getPosition(), transform.getRotation(), transform.getScale());

    for (Math::Point &vertex : boundingVolume.getTopologyMutable().getVerticesMutable()) {
        vertex = model * vertex;
    }
}
