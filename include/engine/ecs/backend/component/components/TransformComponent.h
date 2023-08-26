/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/component/IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"

struct TransformComponent : public IComponent {
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};
    std::string toString() override {
        return "TransformComponent:"
               + std::string("\n\tposition: ")
               + GLESC::glmToString(position)
               + std::string("\n\trotation: ")
               + GLESC::glmToString(rotation)
               + std::string("\n\tscale: ")
               + GLESC::glmToString(scale);
    }
};