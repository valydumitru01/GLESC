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


bool Transform::operator==(const Transform& other) const {
    return position == other.position && rotation == other.rotation && scale == other.scale;
}

std::string Transform::toString() const {
    return "Position: " + position.toString() + "\n" +
        "Rotation: " + rotation.toString() + "\n" +
        "Scale: " + scale.toString();
}


GLESC::Math::Direction Transform::worldUp{Math::Direction(0.0f, 1.0f, 0.0f)};
GLESC::Math::Direction Transform::worldRight{Math::Direction(1.0f, 0.0f, 0.0f)};
GLESC::Math::Direction Transform::worldForward{Math::Direction(0.0f, 0.0f, 1.0f)};


void Transformer::transformMesh(Render::ColorMesh& mesh, const Render::Model& modelMat) {
    // TODO: Implement this function
    D_ASSERT_TRUE(false, "Not implemented");
    Vec3F transformedVertice3D;
    for (auto& vertex : mesh.getVertices()) {
        Render::getVertexPositionAttr(vertex) = modelMat * Render::getVertexPositionAttr(vertex);
    }

    transformBoundingVolume(mesh.getBoundingVolumeMutable(), modelMat);
}

GLESC::Render::BoundingVolume Transformer::transformBoundingVolume(const Render::BoundingVolume& boundingVolume,
                                                                   const Render::Model& modelMat) {
    Render::BoundingVolume transformedBoundingVolume;
    Vec3F transformedVertice3D;
    for (const Math::Point& topologyVertice : boundingVolume.getTopology().getVertices()) {
        transformedVertice3D = modelToWorld(topologyVertice, modelMat);
        transformedBoundingVolume.topology.addVertex(transformedVertice3D);
    }
    return transformedBoundingVolume;
}

Position Transformer::modelToWorld(const Position& modelPos, const Render::Model& modelMat) {
    // IMPORTANT! We use row major matrices but the data distribution is prepared to be column major for in GPU
    // operations. So for the CPU we need to transpose the matrices.
    Vec4F transformedToWorldVertex = modelMat.transpose() * modelPos.homogenize();
    return transformedToWorldVertex.dehomogenize();
}

Position Transformer::worldToCamera(const Position& worldPos, const Render::View& viewMat) {
    // IMPORTANT! We use row major matrices but the data distribution is prepared to be column major for in GPU
    // operations. So for the CPU we need to transpose the matrices.
    Vec4F transformedToCameraVertex = viewMat.transpose() * worldPos.homogenize();
    return transformedToCameraVertex.dehomogenize();
}

Position Transformer::cameraToClip(const Position& cameraPos, const Render::Projection& projMat) {
    // IMPORTANT! We use row major matrices but the data distribution is prepared to be column major for in GPU
    // operations. So for the CPU we need to transpose the matrices.
    Vec4F transformedToClipVertex = projMat.transpose() * cameraPos.homogenize();
    return transformedToClipVertex.dehomogenize();
}

Position Transformer::clipToNDC(const HomogeneousPosition& clipPos) {
    return clipPos.dehomogenize();
}


Position Transformer::NDCToViewport(const Position& ndcPos, float vpWidth, float vpHeight) {
    // Map NDC to screen coordinates for x and y
    float screenX = (ndcPos.getX() + 1.0f) * vpWidth / 2.0f;
    float screenY = (1.0f - ndcPos.getY() ) * vpHeight / 2.0f;
    float screenZ = (1.0f - ndcPos.getZ() ) / 2;

    return {screenX, screenY, screenZ};
}


Position Transformer::worldToViewport(const Position& worldPos, const Render::View& viewMat,
                                      const Render::Projection& projMat, float vpWidth, float vpHeight) {
    Render::VP viewProj = viewMat * projMat;
    // IMPORTANT! We use row major matrices but the data distribution is prepared to be column major for in GPU
    // operations. So for the CPU we need to transpose the matrices.
    HomogeneousPosition clipPos = viewProj.transpose() * worldPos.homogenize();
    Position ndcPos = clipToNDC(clipPos);
    return NDCToViewport(ndcPos, vpWidth, vpHeight);
}


void Interpolator::pushTransform(const Transform& transform) {
    previousOfLastTransform = lastTransform;
    lastTransform = transform;
}

Transform Interpolator::interpolate(double alpha) const  {
    Transform interpolatedTransform;
    interpolatedTransform.setPosition(
        previousOfLastTransform.getPosition().lerp(lastTransform.getPosition(), alpha));
    interpolatedTransform.setRotation(
        previousOfLastTransform.getRotation().lerp(lastTransform.getRotation(), alpha));
    interpolatedTransform.setScale(
        previousOfLastTransform.getScale().lerp(lastTransform.getScale(), alpha));
    return interpolatedTransform;
}