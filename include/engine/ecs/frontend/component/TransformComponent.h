/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"
#include "engine/core/math/Vector.h"

struct TransformComponent : public IComponent {
    Vector3D position{0.0};
    Vector3D rotation{0.0};
    Vector3D scale{1.0};
    
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