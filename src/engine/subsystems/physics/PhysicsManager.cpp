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
    void PhysicsManager::updatePhysics(Physics& physics, Transform::Transform& transform) const {
        // Calculate acceleration
        physics.addAcceleration(physics.getForce() / physics.getMass());
        physics.addAcceleration(transform.forward() * physics.getForwardForce() / physics.getMass());

        // Calculate velocity
        physics.addVelocity(physics.getAcceleration());
        physics.addVelocity(transform.forward() * physics.getForwardAcceleration());

        // Apply friction
        physics.addVelocity(-physics.getVelocity() * airFriction);

        // Calculate position
        transform.addPosition(physics.getVelocity() * velocityScalar);
        transform.addPosition(transform.forward() * physics.getForwardVelocity() * velocityScalar);

        // Clear forces
        physics.giveForce(Force(0.0F, 0.0F, 0.0F));
    }
} // namespace GLESC
