/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/backend/component/IComponent.h"
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

#ifndef NDEBUG_GLESC
        void setDebuggingValues() override {
            for (auto& value : perspective.getDebuggingValues()) {
                values.push_back(value);
            }
        }
#endif
    };
} // namespace GLESC::ECS
