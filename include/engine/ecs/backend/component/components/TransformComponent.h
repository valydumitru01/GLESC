/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/component/Component.h"

struct TransformComponent : public Component {
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
    glm::vec3 scale{1.f};
    
    [[nodiscard]] std::string toString() const override {
        return "TransformComponent:"
        + std::string("\n\tposition: ")
        + GLESC::toString(position)
        + std::string("\n\trotation: ")
        + GLESC::toString(rotation)
        + std::string("\n\tscale: ")
        + GLESC::toString(scale);
    }
};