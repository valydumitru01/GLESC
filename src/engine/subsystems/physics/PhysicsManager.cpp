#include "engine/subsystems/physics/PhysicsManager.h"


namespace GLESC::Physics {
    PhysicsManager::PhysicsManager(const GLESC::FPSManager& fpsManager) {
        timestep = static_cast<float>(1.0l / fpsManager.getUpdateFPS());
    }

    void PhysicsManager::applyForces(Physics& physics) const {
        if (physics.isStatic()) {
            physics.setVelocity({0, 0, 0});
            physics.setAcceleration({0, 0, 0});
            physics.setForce({0, 0, 0});
            return;
        }


        // Clear acceleration
        physics.setAcceleration(Acceleration(0.0F, 0.0F, 0.0F));

        // TODO: Remove magic numbers (for some reason physics are not realistic even with realistic values)
        // Maybe due to size of objects
        // Calculate acceleration
        physics.addAcceleration(physics.getForce() * 35 / physics.getMass());
        if (physics.isAffectedByGravity())
            physics.addAcceleration(gravity  * 3);

        // Calculate velocity
        physics.addVelocity(physics.getAcceleration() * timestep);

        // Apply friction
        if (physics.getAirFriction() < 0.0f)
            physics.addVelocity(-physics.getVelocity() * airFriction);
        else
            physics.addVelocity(-physics.getVelocity() * physics.getAirFriction());

        // Clear forces
        physics.setForce(Force(0.0F, 0.0F, 0.0F));
    }

    Transform::Transform
    PhysicsManager::updateTransform(const Transform::Transform& transform, const Physics& physics) const {
        Transform::Transform newTransform = transform;
        newTransform.addPosition(physics.getVelocity() * timestep);
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

    Velocity getBouncingVelocity(const Velocity& velocity, const Vec3F& collisionNormal, float bounciness) {
        Velocity bouncingVelocity = velocity * bounciness;
        // Reflect, for bounciness
        bouncingVelocity = bouncingVelocity.reflect(collisionNormal);
        return bouncingVelocity;
    }

    using AxisConstraints = std::array<std::array<bool, 2>, 3>;

    AxisConstraints getAxisFree(const Collider& collider) {
        AxisConstraints isAxisFree = {
            {
                //   +     -    // Axis
                {true, true}, // X
                {true, true}, // Y
                {true, true} // Z
            }
        };

        for (const Vec3F& collisionDepth : collider.getCollisionInformation().getCollisionDepthForAxis()) {
            for (int i = 0; i < 3; ++i) {
                // Check if the collision depth is positive or negative
                isAxisFree[i][0] = isAxisFree[i][0] && !Math::gt(collisionDepth[i], 0.0f);
                isAxisFree[i][1] = isAxisFree[i][1] && !Math::lt(collisionDepth[i], 0.0f);
            }
        }
        return isAxisFree;
    }

    Velocity getVelocityWithFriction(const Physics& physics, const std::vector<Physics*>& physicsOfCollided) {
        Velocity velocityWithFriction = physics.getVelocity();
        for (auto otherPhysics : physicsOfCollided) {
            // Calculate the average friction coefficient between the two objects
            float frictionCoefficient = otherPhysics->getFriction() + physics.getFriction();

            // Calculate the friction force based on the velocity and friction coefficient
            Vec3F frictionVelReduction = physics.getVelocity() * frictionCoefficient;

            // Apply the friction force to the total velocity
            velocityWithFriction -= frictionVelReduction;
        }
        return velocityWithFriction;
    }

    bool isFrictionApplied(const Physics& physics,
                           const AxisConstraints& freeAxis) {
        bool isFrictionApplied = true;

        for (int i = 0; i < 3; ++i) {
            isFrictionApplied = Math::gt(physics.getVelocity()[i], 0) && freeAxis[i][0] && isFrictionApplied;
            isFrictionApplied = Math::lt(physics.getVelocity()[i], 0) && freeAxis[i][1] && isFrictionApplied;
        }
        return isFrictionApplied;
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
            finalVelocity = getBouncingVelocity(physics.getVelocity(), collisionNormal, bounciness);
        }
        else {
            AxisConstraints freeAxis = getAxisFree(collider);
            bool frictionApplied = isFrictionApplied(physics, freeAxis);

            Vec3F velocityWithFriction;
            if (frictionApplied)
                velocityWithFriction = physics.getVelocity();
            else
                velocityWithFriction = getVelocityWithFriction(physics, info.getPhysicsOfCollided());

            for (int i = 0; i < 3; ++i) {
                if (Math::gt(velocityWithFriction[i], 0.0f))
                    velocityWithFriction[i] *= static_cast<float>(freeAxis[i][0]);
                else
                    velocityWithFriction[i] *= static_cast<float>(freeAxis[i][1]);
            }
            finalVelocity = velocityWithFriction;
        }


        physics.setVelocity(finalVelocity);

        //Apply the new velocity to the component
    }
} // namespace GLESC
