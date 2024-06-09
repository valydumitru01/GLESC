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
    void PhysicsManager::applyForces(Physics& physics) const {
        if (physics.isStatic()) {
            physics.setVelocity({0, 0, 0});
            physics.setAcceleration({0, 0, 0});
            physics.setForce({0, 0, 0});
        }

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
    }

    Transform::Transform
    PhysicsManager::updateTransform(const Transform::Transform& transform, const Physics& physics) {
        Transform::Transform newTransform = transform;
        newTransform.addPosition(physics.getVelocity() * velocityScalar);
        return newTransform;
    }

    void PhysicsManager::executeCallbacks(Collider& collider, const CollisionInformation& info) {
        if (collider.getGeneralCollisionCallback())
            collider.getGeneralCollisionCallback()(*info.getCollidingWithColliders()[0]);
        for (auto& otherCollider : info.getCollidingWithColliders()) {
            // Check if there is a specific callback for this collider
            auto it = collider.getSpecificCollisionCallbacks().find(otherCollider);
            if (it != collider.getSpecificCollisionCallbacks().end()) {
                it->second(*otherCollider);
            }
        }
    }


    void PhysicsManager::handleCollisions(Collider& collider, Physics& physics) const {
        CollisionInformation& info = collider.getCollisionInformation();
        executeCallbacks(collider, info);

        // If the object is static, no new velocity is needed, it will remain 0
        if (physics.isStatic()) return;

        // If the velocity is too small, we consider it as 0 so we don't have jittering
        bool bouncingOccurs = !info.wasOnGroundLastFrame() &&
            physics.getVelocity().length() > bouncinessThreshold;

        Velocity finalVelocity;
        if (bouncingOccurs) {
            // Calculate the collision normal to reflect the velocity
            Vec3F collisionNormal = {
                info.getCollidingAxis().getX(), info.getCollidingAxis().getY(), info.getCollidingAxis().getZ()
            };
            Velocity bouncingVelocity = physics.getVelocity() * bounciness;
            // Reflect, for bounciness
            bouncingVelocity = bouncingVelocity.reflect(collisionNormal);
            finalVelocity = bouncingVelocity;
        }
        else {
            Vec3F velocityWithFriction = physics.getVelocity();
            for (auto otherPhysics : info.getPhysicsOfCollided()) {
                // Calculate the average friction coefficient between the two objects
                float frictionCoefficient = otherPhysics->getFriction() + physics.getFriction();

                // Calculate the friction force based on the velocity and friction coefficient
                Vec3F frictionForce = physics.getVelocity() * frictionCoefficient;

                // Apply the friction force to the total velocity
                velocityWithFriction -= frictionForce;
            }

            float isXFree = !collider.getCollisionInformation().getCollidingAxis().getX();
            float isYFree = !collider.getCollisionInformation().getCollidingAxis().getY();
            float isZFree = !collider.getCollisionInformation().getCollidingAxis().getZ();

            velocityWithFriction.setX(isXFree * velocityWithFriction.getX());

            velocityWithFriction.setY(isYFree * velocityWithFriction.getY());

            velocityWithFriction.setZ(isZFree * velocityWithFriction.getZ());

            finalVelocity = velocityWithFriction;
        }


        physics.setVelocity(finalVelocity);

        //Apply the new velocity to the component
    }
} // namespace GLESC
