/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"
#include "engine/core/math/Matrix.h"

struct CameraComponent : IComponent {
public:
    Matrix4D view{};
    float fov{};
    float viewWidth{};
    float viewHeight{};
    float nearPlane{};
    float farPlane{};
    
    std::string toString() override{
        return  "CameraComponent:"
                + std::string("\n\tview: ")
                + view.toString()
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


