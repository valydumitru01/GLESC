/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"
#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/camera/CameraPerspective.h"

namespace GLESC::ECS {
    struct CameraComponent : IComponent {
        CameraComponent() {
            perspective.fovDegrees = 45;
            perspective.nearPlane = 0.1;
            perspective.farPlane = 1000;
        }

        Render::View view{};
        Render::CameraPerspective perspective;

        float sensitivity{3.f};


        std::string toString() const override {
            return std::string("\n\tview: \n")
                + view.toString()
                + perspective.toString();
        }

        std::string getName() const override {
            return "CameraComponent";
        }
    };
} // namespace GLESC::ECS
