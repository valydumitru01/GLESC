/**************************************************************************************************
 * @file   SunComponent.h
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "../../backend/component/IComponent.h"
#include "engine/subsystems/renderer/lighting/GlobalAmbienLight.h"
#include "engine/subsystems/renderer/lighting/GlobalSun.h"

namespace GLESC::ECS {
    class SunComponent : public IComponent {
    public:
        Render::GlobalAmbienLight globalAmbienLight;
        Render::GlobalSun sun;

        std::string toString() const override {
            return sun.toString();
        }

        std::string getName() const override {
            return "SunComponent";
        }

        void setDebuggingValues() override {
            for (auto& value : sun.getDebuggingValues()) {
                values.push_back(value);
            }
            for (auto& value : globalAmbienLight.getDebuggingValues()) {
                values.push_back(value);
            }
        }
    }; // class SunComponent
} // namespace GLESC::ECS
