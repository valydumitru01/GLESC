/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <unordered_map>

#include "engine/ecs/backend/component/IComponent.h"
#include "engine/subsystems/input/Input.h"
#include "engine/subsystems/input/KeyCommand.h"
#include "engine/subsystems/input/InputTypes.h"
#include "engine/subsystems/input/MouseCommand.h"

namespace GLESC::ECS {
    struct InputComponent : IComponent {
        Input::Input input;
        std::string toString() const override {
            return input.toString();
        }

        std::string getName() const override {
            return "InputComponent";
        }

        void setDebuggingValues() override {
            for (auto& value : input.getDebuggingValues()) {
                values.push_back(value);
            }
        }
    };
} // namespace GLESC::ECS
