/**************************************************************************************************
 * @file   SunComponent.h
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "../../backend/component/IComponent.h"
#include "engine/subsystems/renderer/lighting/GlobalAmbientLight.h"
#include "engine/subsystems/renderer/lighting/GlobalSun.h"

namespace GLESC::ECS {
    class SunComponent : public IComponent {
    public:
        Render::GlobalAmbientLight globalAmbientLight;
        Render::GlobalSun sun;

        std::string toString() const override {
            return sun.toString();
        }

        std::string getName() const override {
            return "SunComponent";
        }
#ifndef NDEBUG_GLESC

          void setDebuggingValues() override {
            for (auto& value : sun.getDebuggingValues()) {
                values.push_back(value);
            }
            for (auto& value : globalAmbientLight.getDebuggingValues()) {
                values.push_back(value);
            }
        }
#endif
    }; // class SunComponent
} // namespace GLESC::ECS
