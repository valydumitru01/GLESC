/**************************************************************************************************
 * @file   InputComponent.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once

#include "engine/ecs/backend/component/IComponent.h"
#include "engine/subsystems/input/Input.h"

namespace GLESC::ECS {
    struct InputComponent : IComponent {
        Input::Input input;
        std::string toString() const override {
            return input.toString();
        }

        std::string getName() const override {
            return "InputComponent";
        }
#ifndef NDEBUG_GLESC
        void setDebuggingValues() override {
            for (auto& value : input.getDebuggingValues()) {
                values.push_back(value);
            }
        }
#endif
    };
} // namespace GLESC::ECS
