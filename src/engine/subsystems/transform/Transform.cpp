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
    rotationDegrees(std::move(rotation)),
    scale(std::move(scale)) {
}


GLESC::Math::Direction Transform::forward() const {
    if (dirty)
        return calculateForward();
    return forwardDirection;
}

GLESC::Math::Direction Transform::right() const {
    if (dirty)
        return calculateRight();
    return rightDirection;
}

GLESC::Math::Direction Transform::up() const {
    if (dirty)
        return calculateUp();
    return forwardDirection;
}

GLESC::Math::Direction Transform::calculateForward() const {
    return GLESC::Math::Direction().makeForward(rotationDegrees.toRads());
}

GLESC::Math::Direction Transform::calculateRight() const {
    return GLESC::Math::Direction().makeRight(rotationDegrees.toRads());
}

GLESC::Math::Direction Transform::calculateUp() const {
    return GLESC::Math::Direction().makeUp(rotationDegrees.toRads());
}


bool Transform::operator==(const Transform& other) const {
    return position == other.position && rotationDegrees == other.rotationDegrees && scale == other.scale;
}

std::string Transform::toString() const {
    return "Position: " + position.toString() + "\n" +
        "Rotation: " + rotationDegrees.toString() + "\n" +
        "Scale: " + scale.toString();
}


GLESC::Math::Direction Transform::worldUp{Math::Direction(0.0f, 1.0f, 0.0f)};
GLESC::Math::Direction Transform::worldRight{Math::Direction(1.0f, 0.0f, 0.0f)};
GLESC::Math::Direction Transform::worldForward{Math::Direction(0.0f, 0.0f, 1.0f)};


void Transformer::transformMesh(Render::ColorMesh& mesh, const Mat4F& matrix) {
    for (auto& vertex : mesh.getModifiableVertices()) {
        vertex.setPosition(transformPosition(vertex.getPosition(), matrix));
    }

    transformBoundingVolume(mesh.getBoundingVolumeMutable(), matrix);
}

void Transformer::translateMesh(Render::ColorMesh& mesh, const Position& translation) {
    for (auto& vertex : mesh.getModifiableVertices()) {
        vertex.setPosition({
            vertex.getPosition().getX() + translation.getX(),
            vertex.getPosition().getY() + translation.getY(),
            vertex.getPosition().getZ() + translation.getZ()
        });
    }
}


void Transformer::transformMesh(Render::ColorMesh& mesh, const Transform& transform) {
    Render::Model modelMat = transform.getModelMatrix();
    transformMesh(mesh, modelMat);
}

GLESC::Math::BoundingVolume Transformer::transformBoundingVolume(const Math::BoundingVolume& boundingVolume,
                                                                 const Render::Model& matrix) {
    return {
        transformPosition(boundingVolume.getVolume().min, matrix),
        transformPosition(boundingVolume.getVolume().max, matrix)
    };
}

GLESC::Math::BoundingVolume Transformer::transformBoundingVolume(const Math::BoundingVolume& boundingVolume,
                                                                 const Transform& transform) {
    Render::Model modelMat = transform.getModelMatrix();
    return transformBoundingVolume(boundingVolume, modelMat);
}

Position Transformer::transformPosition(const Position& position, const Render::Model& matrix) {
    // IMPORTANT! We use row major matrices but the data distribution is prepared to be column major for in GPU
    // operations. So for the CPU we need to transpose the matrices.

    Vec4F transformedToWorldVertex = matrix * position.homogenize();
    return transformedToWorldVertex.dehomogenize();
}

Position Transformer::clipToNDC(const HomogeneousPosition& clipPos) {
    return clipPos.dehomogenize();
}


Position Transformer::NDCToViewport(const Position& ndcPos, float vpWidth, float vpHeight) {
    // Map NDC to screen coordinates for x and y
    float screenX = (ndcPos.getX() + 1.0f) * vpWidth / 2.0f;
    float screenY = (1.0f - ndcPos.getY()) * vpHeight / 2.0f;
    float screenZ = (1.0f - ndcPos.getZ()) / 2;

    return {screenX, screenY, screenZ};
}


Position Transformer::worldToViewport(const Position& worldPos, const Render::VP& viewProj, float vpWidth,
                                      float vpHeight) {
    // IMPORTANT! We use row major matrices but the data distribution is prepared to be column major for in GPU
    // operations. So for the CPU we need to transpose the matrices.
    HomogeneousPosition clipPos = viewProj * worldPos.homogenize();
    Position ndcPos = clipToNDC(clipPos);
    return NDCToViewport(ndcPos, vpWidth, vpHeight);
}


void Interpolator::pushTransform(const Transform& transform) {
    previousOfLastTransform = lastTransform;
    lastTransform = transform;
}

Transform Interpolator::interpolate(double alpha) const {
    Transform interpolatedTransform;
    interpolatedTransform.setPosition(
        previousOfLastTransform.getPosition().lerp(lastTransform.getPosition(), alpha));
    interpolatedTransform.setRotation(
        previousOfLastTransform.getRotation().lerp(lastTransform.getRotation(), alpha));
    interpolatedTransform.setScale(
        previousOfLastTransform.getScale().lerp(lastTransform.getScale(), alpha));
    return interpolatedTransform;
}
