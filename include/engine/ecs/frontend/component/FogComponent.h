/**************************************************************************************************
 * @file   FogComponent.h
 * @author Valentin Dumitru
 * @date   05/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/subsystems/renderer/Fog.h"

namespace GLESC::ECS {
    class FogComponent : IComponent {
    public:
        [[nodiscard]] std::string toString() const override {
            return fog.toString();
        }

        [[nodiscard]] std::string getName() const override {
            return "FogComponent";
        }

        void setDebuggingValues() override {
            for (auto& value : fog.getDebuggingValues()) {
                values.push_back(value);
            }
        }

        Fog fog;
    }; // class FogComponent
} // namespace GLESC::ECS
