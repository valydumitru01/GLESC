/**************************************************************************************************
 * @file   CollisionManager.cpp
 * @author Valentin Dumitru
 * @date   06/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include "engine/subsystems/physics/CollisionManager.h"

using namespace GLESC::Physics;

GLESC::Math::BoundingVolume translateBV(const Collider& colliderWithBV,
                                        const GLESC::Transform::Transform& transform) {
    return GLESC::Transform::Transformer::transformBoundingVolume(colliderWithBV.getBoundingVolume(),
                                                                  transform.getTranslationMatrix());
}


void CollisionManager::checkAndUpdateColliderInformation(Collider& collider,
                                               const Transform::Transform& originalTransform,
                                               const Transform::Transform& hypNextFrameTransform) {
    // Clear the information before using it (so we don't accumulate information)
    collider.getCollisionInformation().clearInformation();

    // If it's not solid, go ahead and update the transform, nothing else to do
    if (!collider.isSolid()) {
        return;
    }
    Transform::Transform hypNextTransformX{};
    Transform::Transform hypNextTransformY{};
    Transform::Transform hypNextTransformZ{};
    hypNextTransformX.setPosition({
        hypNextFrameTransform.getPosition().getX(),
        originalTransform.getPosition().getY(),
        originalTransform.getPosition().getZ()
    });
    hypNextTransformY.setPosition({
        originalTransform.getPosition().getX(),
        hypNextFrameTransform.getPosition().getY(),
        originalTransform.getPosition().getZ()
    });
    hypNextTransformZ.setPosition({
        originalTransform.getPosition().getX(),
        originalTransform.getPosition().getY(),
        hypNextFrameTransform.getPosition().getZ()
    });

    const Math::BoundingVolume hypotheticalNextBVX = translateBV(collider, hypNextTransformX);
    const Math::BoundingVolume hypotheticalNextBVY = translateBV(collider, hypNextTransformY);
    const Math::BoundingVolume hypotheticalNextBVZ = translateBV(collider, hypNextTransformZ);

    // Cancel the component that causes the collision
    updateCollider(collider,
                   hypNextFrameTransform,
                   hypotheticalNextBVX,
                   hypotheticalNextBVY,
                   hypotheticalNextBVZ);
}


void CollisionManager::updateCollider(Collider& originalCollider,
                                      const Transform::Transform& originalTransform,
                                      const Math::BoundingVolume& nextColliderBVX,
                                      const Math::BoundingVolume& nextColliderBVY,
                                      const Math::BoundingVolume& nextColliderBVZ) {
    Collider& ogColl = originalCollider;
    const Transform::Transform& ogTrans = originalTransform;

    ogColl.getCollisionInformation().setColliding(false);
    bool collidesX = false;
    bool collidesY = false;
    bool collidesZ = false;
    for (int i = 0; i < colliders.size(); i++) {
        if (&ogColl == colliders[i]) continue;
        Collider& otherCollider = *colliders[i];
        Physics& otherPhysics = *physicsOfColliders[i];
        Transform::Transform& otherTransform = *transformsOfColliders[i];

        Math::BoundingVolume transformedOriginalBV = translateBV(ogColl, ogTrans);
        Math::BoundingVolume transformedOtherBV = translateBV(otherCollider, otherTransform);
        if (transformedOriginalBV.intersects(transformedOtherBV)) {
            ogColl.getCollisionInformation().setColliding(true);
            Vec3F collisionDepths = getCollisionDepth(nextColliderBVX, nextColliderBVY, nextColliderBVZ,
                                                      transformedOtherBV);
            ogColl.getCollisionInformation().addCollidingWith(&otherCollider, &otherPhysics, collisionDepths);

            collidesX = collidesX || !Math::eq(collisionDepths.getX(), 0);
            collidesY = collidesY || !Math::eq(collisionDepths.getY(), 0);
            collidesZ = collidesZ || !Math::eq(collisionDepths.getZ(), 0);
        }
    }
    ogColl.getCollisionInformation().setCollidesAxis({collidesX, collidesY, collidesZ});
    bool isOnGround = ogColl.getCollisionInformation().getCollidingAxis().getY();
    ogColl.getCollisionInformation().setOnGround(isOnGround);
}

Vec3F CollisionManager::getCollisionDepth(const Math::BoundingVolume& nextColliderBVX,
                                          const Math::BoundingVolume& nextColliderBVY,
                                          const Math::BoundingVolume& nextColliderBVZ,
                                          const Math::BoundingVolume& otherBV) {
    // Assumes that collision occured, therefore depth will be non-zero
    float depthX = nextColliderBVX.intersectionVolume(otherBV);
    float depthY = nextColliderBVY.intersectionVolume(otherBV);
    float depthZ = nextColliderBVZ.intersectionVolume(otherBV);

    // Negate volume if collision occurred on the negative side of the axis
    if (otherBV.getMin().getX() < nextColliderBVX.getMin().getX()) {
        depthX = -depthX;
    }
    if (otherBV.getMin().getY() < nextColliderBVY.getMin().getY()) {
        depthY = -depthY;
    }
    if (otherBV.getMin().getZ() < nextColliderBVZ.getMin().getZ()) {
        depthZ = -depthZ;
    }

    return {depthX, depthY, depthZ};
}
