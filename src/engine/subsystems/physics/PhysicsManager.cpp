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
        Transform::Transform hypNextTransformX = hypotheticalNextTransform;
        Transform::Transform hypNextTransformY = hypotheticalNextTransform;
        Transform::Transform hypNextTransformZ = hypotheticalNextTransform;
        hypNextTransformX.setPosition({
            hypotheticalNextTransform.getPosition().getX(),
            transform.getPosition().getY(),
            transform.getPosition().getZ()
        });
        hypNextTransformY.setPosition({
            transform.getPosition().getX(),
            hypotheticalNextTransform.getPosition().getY(),
            transform.getPosition().getZ()
        });
        hypNextTransformZ.setPosition({
            transform.getPosition().getX(),
            transform.getPosition().getY(),
            hypotheticalNextTransform.getPosition().getZ()
        });

        // Get the next collider based on the hypothetical next transform
        Collider hypothethicalNextCollider = getNextCollider(collider, hypotheticalNextTransform);

        Collider hypotheticalNextColliderX = getNextCollider(collider, hypNextTransformX);
        Collider hypotheticalNextColliderY = getNextCollider(collider, hypNextTransformY);
        Collider hypotheticalNextColliderZ = getNextCollider(collider, hypNextTransformZ);

        // Cancel the component that causes the collision
        CollisionInformation information = collidesOnNextFrame(collider,
                                                               hypothethicalNextCollider,
                                                               hypotheticalNextColliderX,
                                                               hypotheticalNextColliderY,
                                                               hypotheticalNextColliderZ);

        if (information.collided)
            handleCollisions(information, collider, physics);
        else
            collider.setColliding({false, false, false});


        // We need to update the transform with the updated physics
        transform = getNextTransform(transform, physics);
    }


    void PhysicsManager::handleCollisions(CollisionInformation& info, Collider& collider, Physics& physics) {
        if (collider.getGeneralCollisionCallback())
            collider.getGeneralCollisionCallback()(*info.colliders[0]);
        for (auto& otherCollider : info.colliders) {
            // Check if there is a specific callback for this collider
            auto it = collider.getSpecificCollisionCallbacks().find(otherCollider);
            if (it != collider.getSpecificCollisionCallbacks().end()) {
                it->second(*otherCollider);
            }
        }
        bool collidesX = false, collidesY = false, collidesZ = false;
        for (const auto& penetration : info.collisionPenetrationsForAxis) {
            if (!Math::eq(penetration.getX(), 0)) collidesX = true;
            if (!Math::eq(penetration.getY(), 0)) collidesY = true;
            if (!Math::eq(penetration.getZ(), 0)) collidesZ = true;
        }

        Vec3F totalVelocity = physics.getVelocity();
        for (Physics* otherPhysics : info.physicsOfCollided) {
            if (otherPhysics) {
                // Calculate the average friction coefficient between the two objects
                float frictionCoefficient = otherPhysics->getFriction() + physics.getFriction();

                // Calculate the relative velocity between the two objects
                Vec3F relativeVelocity = otherPhysics->getVelocity() - physics.getVelocity();

                // Calculate the friction force based on the relative velocity and friction coefficient
                Vec3F frictionForce = relativeVelocity * frictionCoefficient;

                // Apply the friction force to the total velocity
                //totalVelocity -= frictionForce;
            }
        }

        collider.setColliding({collidesX, collidesY, collidesZ});
        // Cancel the components that cause the collision
        physics.setVelocity({
            collidesX ? 0.0f : totalVelocity.getX(),
            collidesY ? 0.0f : totalVelocity.getY(),
            collidesZ ? 0.0f : totalVelocity.getZ()
        });


        bool isOnAnyFloor = false;
        for (const Vec3F& collisionPenetration : info.collisionPenetrationsForAxis) {
            if (collisionPenetration.getY() < 0) {
                isOnAnyFloor = true;
                break;
            }
        }
        collider.setIsOnAir(!isOnAnyFloor);
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
        nextCollider.setBoundingVolume(
            Transform::Transformer::transformBoundingVolume(oldCollider.getBoundingVolume(),
                                                            nextTransform.getTranslationMatrix()));
        return nextCollider;
    }


    CollisionInformation PhysicsManager::collidesOnNextFrame(const Collider& originalCollider,
                                                             const Collider& nextCollider,
                                                             const Collider& nextColliderX,
                                                             const Collider& nextColliderY,
                                                             const Collider& nextColliderZ) {
        CollisionInformation information;
        information.collided = false;

        for (int i = 0; i < colliders.size(); i++) {
            Collider* otherCollider = colliders[i];
            if (&originalCollider == otherCollider) continue;
            if (nextCollider.getBoundingVolume().intersects(otherCollider->getBoundingVolume())) {
                information.collided = true;
                information.physicsOfCollided.push_back(physics[i]);
                information.colliders.push_back(otherCollider);
                Vec3F collisionVolumes = getCollisionDepth(nextColliderX, nextColliderY, nextColliderZ, *otherCollider);
                information.collisionPenetrationsForAxis.push_back(collisionVolumes);
            }
        }
        return information;
    }

    Vec3F PhysicsManager::getCollisionDepth(const Collider& nextColliderX, const Collider& nextColliderY,
                                            const Collider& nextColliderZ, const Collider& otherCollider) {
        // Assumes that collision occured, therefore depth will be non-zero
        Vec3F depthX = nextColliderX.getBoundingVolume().intersectsVolume(otherCollider.getBoundingVolume());
        Vec3F depthY = nextColliderY.getBoundingVolume().intersectsVolume(otherCollider.getBoundingVolume());
        Vec3F depthZ = nextColliderZ.getBoundingVolume().intersectsVolume(otherCollider.getBoundingVolume());

        return {depthX.getX(), depthY.getY(), depthZ.getZ()};
    }
} // namespace GLESC
