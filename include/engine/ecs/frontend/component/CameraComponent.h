/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"
#include "engine/core/math/algebra/matrix/Matrix.h"

struct CameraComponent : IComponent {
    Mat4D view{};
    float fovDegrees{45};
    float viewWidth{800};
    float viewHeight{600};
    float nearPlane{0.1};
    float farPlane{1000};
    // TODO: Introduce dirty flag to avoid unnecessary recalculations of view and projection matrices
    
    std::string toString() override{
        return  "CameraComponent:"
                + std::string("\n\tview: \n")
                + view.toString()
                + std::string("\n\tfov: ")
                + std::to_string(fovDegrees)
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


