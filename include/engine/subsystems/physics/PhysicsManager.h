/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include "Physics.h"
#include "PhysicsTypes.h"
#include "Collider.h"
#include "engine/subsystems/transform/Transform.h"

namespace GLESC::Physics {
    class PhysicsManager {
    public:
        void updatePhysics(Physics& physics, Collider& collider, Transform::Transform& transform) {
            addCollider(collider);

            physics = getNextPhysics(physics, transform);
            Transform::Transform nextTransform = getNextTransform(transform, physics);
            Collider nextCollider = getNextCollider(collider, nextTransform);

            // If the new bounding volume intersects with another bounding volume that is solid, we must stop the object
            if (collidesOnNextFrame(nextCollider) && nextCollider.isSolid()) {
                physics.setVelocity({0.0f, 0.0f, 0.0f});
                return;
            }
            transform = nextTransform;
        }

        Transform::Transform getNextTransform(const Transform::Transform& transformParam,
                                              const Physics& nextPhysics) const {
            Transform::Transform nextTransform = transformParam;

            // Calculate position
            nextTransform.addPosition(nextPhysics.getVelocity() * velocityScalar);
            nextTransform.addPosition(nextTransform.forward() * nextPhysics.getForwardVelocity() * velocityScalar);

            return nextTransform;
        }

        Physics getNextPhysics(const Physics& oldPhysics, const Transform::Transform& transform) const {
            Physics physics = oldPhysics;
            // Calculate acceleration
            physics.addAcceleration(physics.getForce() / physics.getMass());
            physics.addAcceleration(transform.forward() * physics.getForwardForce() / physics.getMass());
            if (physics.isAffectedByGravity())
                physics.addAcceleration(gravity);

            // Calculate velocity
            physics.addVelocity(physics.getAcceleration());
            physics.addVelocity(transform.forward() * physics.getForwardAcceleration());

            // Apply friction
            physics.addVelocity(-physics.getVelocity() * airFriction);

            // Clear forces
            physics.giveForce(Force(0.0F, 0.0F, 0.0F));
            physics.giveForwardForce(0.0F);

            // Clear acceleration
            physics.setAcceleration(Acceleration(0.0F, 0.0F, 0.0F));

            return physics;
        }

        Collider getNextCollider(const Collider& oldCollider, const Transform::Transform& nextTransform) const {
            Collider nextCollider = oldCollider;
            nextCollider.boundingVolume = Transform::Transformer::transformBoundingVolume(oldCollider.boundingVolume,
                                                                                           nextTransform);
            return nextCollider;
        }


        bool collidesOnNextFrame(const Collider& nextCollider) const {

            for (const auto& otherCollider : colliders) {
                if (otherCollider == &nextCollider) continue;
                if (nextCollider.boundingVolume.intersects(otherCollider->boundingVolume)) {
                    nextCollider.collisionCallback();
                    auto it = nextCollider.collisionCallbacksForSpecificColliders.find(otherCollider);
                    if (it != nextCollider.collisionCallbacksForSpecificColliders.end()) {
                        it->second();
                    }
                    return true;
                }
            }
            return false;
        }

        void addCollider(const Collider& collider) {
            // Check if it is in the vector, if not add it
            if (std::find(colliders.begin(), colliders.end(), &collider) == colliders.end()) {
                colliders.push_back(&collider);
            }
        }
    private:
        std::vector<const Collider*> colliders;

        Acceleration gravity{0.f, -8.91f, 0.f};
        Friction airFriction{0.1f};
        /**
         * @brief This scalar is used to scale the velocity of the object
         * @details We need this because using fixed update time steps makes normal values too bit,
         * and the object would move too fast. Using a scalar makes the used be able to handle
         * more realistic numbers.
         */
        Scalar velocityScalar{0.01f};
    };
} // namespace GLESC
