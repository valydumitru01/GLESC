/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"
#include "engine/core/math/Vec.h"

struct TransformComponent : public IComponent {
    Vec3D position{0.0};
    Vec3D rotation{0.0};
    Vec3D scale{1.0};
    
    std::string toString() override {
        return "TransformComponent:"
               + std::string("\n\tposition: ")
               + position.toString()
               + std::string("\n\trotation: ")
               + rotation.toString()
               + std::string("\n\tscale: ")
               + scale.toString();
    }
};