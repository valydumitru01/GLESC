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
/**
 * @brief This scalar is used to scale the velocity of the object
 * @details We need this because using fixed update time steps makes normal values too bit,
 * and the object would move too fast. Using a scalar makes the used be able to handle
 * more realistic numbers.
 */
#define VELOCITY_SCALAR 0.01F

namespace GLESC::Physics {
    void PhysicsManager::updatePhysics(Physics& physics, Transform::Transform& transform) {
        Acceleration accelerationFromForce = physics.getForce() / physics.getMass();
        Velocity velocityFromForce = physics.getForce() / physics.getMass();
        // Applying the force (F = m * a) to the acceleration
        physics.setAcceleration(physics.getAcceleration() + physics.getForce() / physics.getMass());
        // Applying the acceleration to the velocity (if affected by gravity, add gravity)
        if (physics.isAffectedByGravity())
            physics.setVelocity(physics.getAcceleration() + gravity);
        else
            physics.setVelocity(physics.getAcceleration());

        // Do the same but with forward forces
        physics.setForwardAcceleration(
            physics.getForwardAcceleration() + physics.getForwardForce() / physics.getMass());
        physics.setForwardVelocity(physics.getForwardAcceleration());


        // Finally, displacing the object by the calculated velocity
        transform.addPosition(
            (physics.getVelocity() + transform.forward() * physics.getForwardVelocity())
                * VELOCITY_SCALAR);

        // Clear forces
        physics.setForce(Force(0.0F, 0.0F, 0.0F));
    }
} // namespace GLESC
