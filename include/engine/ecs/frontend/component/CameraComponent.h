/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "glm/glm.hpp"
#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"

struct CameraComponent : IComponent {
public:
    glm::mat4 view{};
    float fov{};
    float viewWidth{};
    float viewHeight{};
    float nearPlane{};
    float farPlane{};
    
    std::string toString() override{
        return  "CameraComponent:"
                + std::string("\n\tview: ")
                + GLESC::glmToString(view)
                + std::string("\n\tfov: ")
                + std::to_string(fov)
                + std::string("\n\tviewWidth: ")
                + std::to_string(viewWidth)
                + std::string("\n\tviewHeight: ")
                + std::to_string(viewHeight)
                + std::string("\n\tnearPlane: ")
                + std::to_string(nearPlane)
                + std::string("\n\tfarPlane: ")
                + std::to_string(farPlane);
    }
};


