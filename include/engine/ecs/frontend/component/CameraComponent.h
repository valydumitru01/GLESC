/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "../../backend/component/IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"
#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/camera/CameraPerspective.h"

namespace GLESC::ECS {
    struct CameraComponent : IComponent {
        CameraComponent() = default;
        Render::CameraPerspective perspective;

        [[nodiscard]] std::string toString() const override {
            return std::string("\n\tview: \n")
                + perspective.toString();
        }

        [[nodiscard]] std::string getName() const override {
            return "CameraComponent";
        }


        void setDebuggingValues() override {
            for (auto& value : perspective.getDebuggingValues()) {
                values.push_back(value);
            }
        }
    };
} // namespace GLESC::ECS
