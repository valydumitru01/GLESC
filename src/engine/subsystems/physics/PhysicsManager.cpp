/******************************************************************************
 * @file   PhysicsManager.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/subsystems/physics/PhysicsManager.h"


namespace GLESC::Physics {
    void PhysicsManager::updatePhysics(Physics& physics) {
        // Update the physics (reset acceleration, update velocity, etc)
        physics = getNextPhysics(physics);
    }

    void PhysicsManager::checkCollisions(Collider& collider, Transform::Transform& transform, Physics& physics) {
        // Get the hypothetical next transform if no collision occurs
        Transform::Transform hypotheticalNextTransform = getNextTransform(transform, physics);
        // If it's not solid, go ahead and update the transform, nothing else to do
        if (!collider.isSolid()) {
            transform = hypotheticalNextTransform;
            return;
        }
        // Storing the old transform for clarity in the code
        Transform::Transform& oldTransform = transform;

        // Check if the X translation in the next frame will cause a collision
        Transform::Transform nextHypTransformX = hypotheticalNextTransform;
        nextHypTransformX.setPosition({
            nextHypTransformX.getPosition().getX(),
            oldTransform.getPosition().getY(),
            oldTransform.getPosition().getZ()
        });
        Collider nextColliderX = getNextCollider(collider, nextHypTransformX);


        // Check if the Y translation in the next frame will cause a collision
        Transform::Transform nextHypTransformY = hypotheticalNextTransform;
        nextHypTransformY.setPosition({
            oldTransform.getPosition().getX(),
            nextHypTransformY.getPosition().getY(),
            oldTransform.getPosition().getZ()
        });
        Collider nextColliderY = getNextCollider(collider, nextHypTransformY);


        // Check if the Z translation in the next frame will cause a collision
        Transform::Transform nextHypTransformZ = hypotheticalNextTransform;
        nextHypTransformZ.setPosition({
            oldTransform.getPosition().getX(),
            oldTransform.getPosition().getY(),
            nextHypTransformZ.getPosition().getZ()
        });
        Collider nextColliderZ = getNextCollider(collider, nextHypTransformZ);

        // Cancel the component that causes the collision
        CollisionInformation information = collidesOnNextFrame(
            collider, nextColliderX, nextColliderY, nextColliderZ);

        handleCollisions(information, collider, physics);

        // We need to update the transform with the updated physics
        hypotheticalNextTransform = getNextTransform(transform, physics);
        transform = hypotheticalNextTransform;
    }


    void PhysicsManager::handleCollisions(CollisionInformation& info, Collider& collider, Physics& physics) {
        if (info.collided) {
            if (collider.collisionCallback)
                collider.collisionCallback(*info.colliders[0]);
            for (auto& otherCollider : info.colliders) {
                // Check if there is a specific callback for this collider
                auto it = collider.collisionCallbacksForSpecificColliders.find(otherCollider);
                if (it != collider.collisionCallbacksForSpecificColliders.end()) {
                    it->second(*otherCollider);
                }
            }
        }
        bool collidesX = info.collisionPenetrationsForAxis[0].getX() != 0;
        bool collidesY = info.collisionPenetrationsForAxis[0].getY() != 0;
        bool collidesZ = info.collisionPenetrationsForAxis[0].getZ() != 0;
        Velocity appliedFriction;
        for (Physics* otherPhysics : info.physicsOfCollided) {
            appliedFriction +=
                otherPhysics->getVelocity() * otherPhysics->getFriction() +
                physics.getVelocity() * physics.getFriction();
        }
        float frictionX = appliedFriction.getX();
        float frictionY = appliedFriction.getY();
        float frictionZ = appliedFriction.getZ();
        // Cancel the components that cause the collision
        if (collidesX) {
            physics.addVelocity({
                -physics.getVelocity().getX(),
                -frictionY,
                -frictionZ
            });
        }
        if (collidesY) {
            physics.addVelocity({
                -frictionX,
                -physics.getVelocity().getY(),
                -frictionZ
            });
        }
        if (info.collisionPenetrationsForAxis.getY() < 0)
            collider.setIsOnAir(false);
        else
            collider.setIsOnAir(true);


        if (collidesZ) {
            physics.setVelocity({
                physics.getVelocity().getX() - frictionX,
                physics.getVelocity().getY() - frictionY,
                0.0F
            });
        }
    }


    Transform::Transform PhysicsManager::getNextTransform(const Transform::Transform& transformParam,
                                                          const Physics& nextPhysics) {
        Transform::Transform nextTransform = transformParam;
        // Calculate position
        nextTransform.addPosition(nextPhysics.getVelocity() * velocityScalar);
        return nextTransform;
    }

    Physics PhysicsManager::getNextPhysics(const Physics& oldPhysics) {
        Physics physics = oldPhysics;
        // Calculate acceleration
        physics.addAcceleration(physics.getForce() / physics.getMass());
        if (physics.isAffectedByGravity())
            physics.addAcceleration(gravity);

        // Calculate velocity
        physics.addVelocity(physics.getAcceleration());

        // Apply friction
        physics.addVelocity(-physics.getVelocity() * airFriction);

        // Clear forces
        physics.setForce(Force(0.0F, 0.0F, 0.0F));

        // Clear acceleration
        physics.setAcceleration(Acceleration(0.0F, 0.0F, 0.0F));

        return physics;
    }

    Collider PhysicsManager::getNextCollider(const Collider& oldCollider,
                                             const Transform::Transform& nextTransform) {
        Collider nextCollider = oldCollider;
        nextCollider.boundingVolume =
            Transform::Transformer::transformBoundingVolume(oldCollider.boundingVolume,
                                                            nextTransform.getTranslationMatrix());
        return nextCollider;
    }


    CollisionInformation PhysicsManager::collidesOnNextFrame(const Collider& originalCollider,
                                                             const Collider& nextColliderX,
                                                             const Collider& nextColliderY,
                                                             const Collider& nextColliderZ) {
        CollisionInformation information;
        for (int i = 0; i < colliders.size(); i++) {
            Collider* otherCollider = colliders[i];
            if (otherCollider == &originalCollider) continue;
            Vec3F collisionVolumes{
                collidesWithCollider(nextColliderX, *otherCollider),
                collidesWithCollider(nextColliderY, *otherCollider),
                collidesWithCollider(nextColliderZ, *otherCollider)
            };
            information.collided =
                !Math::eq(collisionVolumes.getX(), 0) ||
                !Math::eq(collisionVolumes.getY(), 0) ||
                !Math::eq(collisionVolumes.getZ(), 0);

            if (information.collided) {
                information.physicsOfCollided.push_back(physics[i]);
                information.colliders.push_back(otherCollider);
                information.collisionPenetrationsForAxis.emplace_back(
                    collisionVolumes.getX(),
                    collisionVolumes.getY(),
                    collisionVolumes.getZ()
                );
            }
        }
        return information;
    }

    float intersectionDepthForAxis(float minA, float maxA, float minB, float maxB) {
        if (minA < minB) {
            if (maxA < minB) return 0; // No collision
            return maxA - minB; // Positive side collision
        }
        if (maxB < minA) return 0; // No collision
        return minA - maxB; // Negative side collision
    }

    Vec3F PhysicsManager::collidesWithCollider(const Collider& collider, const Collider& otherCollider) {
        const auto& colliderVolume = collider.getBoundingVolume();
        const auto& otherColliderVolume = otherCollider.getBoundingVolume();

        // Assuming the bounding volume has methods to get min and max for each axis
        float minAX = colliderVolume.getMin().getX();
        float maxAX = colliderVolume.getMax().getX();
        float minAY = colliderVolume.getMin().getY();
        float maxAY = colliderVolume.getMax().getY();
        float minAZ = colliderVolume.getMin().getZ();
        float maxAZ = colliderVolume.getMax().getZ();

        float minBX = otherColliderVolume.getMin().getX();
        float maxBX = otherColliderVolume.getMax().getX();
        float minBY = otherColliderVolume.getMin().getY();
        float maxBY = otherColliderVolume.getMax().getY();
        float minBZ = otherColliderVolume.getMin().getZ();
        float maxBZ = otherColliderVolume.getMax().getZ();

        float depthX = intersectionDepthForAxis(minAX, maxAX, minBX, maxBX);
        float depthY = intersectionDepthForAxis(minAY, maxAY, minBY, maxBY);
        float depthZ = intersectionDepthForAxis(minAZ, maxAZ, minBZ, maxBZ);

        if (depthX != 0 && depthY != 0 && depthZ != 0) {
            return {depthX, depthY, depthZ};
        }
        return {0, 0, 0};
    }
} // namespace GLESC
