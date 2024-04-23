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
        Render::CameraPerspective perspective;

        float sensitivity{3.f};


        [[nodiscard]] std::string toString() const override {
            return std::string("\n\tview: \n")
                + perspective.toString();
        }

        [[nodiscard]] std::string getName() const override {
            return "CameraComponent";
        }



        void setDebuggingValues() override {

            EntityStatsManager::Value perspectiveValue;
            perspectiveValue.name = "Far plane";
            perspectiveValue.data = reinterpret_cast<void*>(&perspective.farPlane);
            perspectiveValue.type = EntityStatsManager::ValueType::FLOAT;
            perspectiveValue.isModifiable = true;
            perspectiveValue.usesSlider = true;
            perspectiveValue.min = 100.1f;
            perspectiveValue.max = 1000.0f;
            values.push_back(perspectiveValue);

            EntityStatsManager::Value nearPlane;
            nearPlane.name = "Near plane";
            nearPlane.data = reinterpret_cast<void*>(&perspective.nearPlane);
            nearPlane.type = EntityStatsManager::ValueType::FLOAT;
            nearPlane.isModifiable = true;
            nearPlane.usesSlider = true;
            nearPlane.min = 0.1f;
            nearPlane.max = 100.0f;
            values.push_back(nearPlane);

            EntityStatsManager::Value fov;
            fov.name = "Field of view";
            fov.data = reinterpret_cast<void*>(&perspective.fovDegrees);
            fov.type = EntityStatsManager::ValueType::FLOAT;
            fov.isModifiable = true;
            fov.usesSlider = true;
            fov.min = 0.1f;
            fov.max = 180.0f;
            values.push_back(fov);

            EntityStatsManager::Value viewWidth;
            viewWidth.name = "View width";
            viewWidth.data = reinterpret_cast<void*>(&perspective.viewWidth);
            viewWidth.type = EntityStatsManager::ValueType::FLOAT;
            viewWidth.isModifiable = true;
            viewWidth.usesSlider = true;
            viewWidth.min = 0.1f;
            viewWidth.max = 10000.0f;
            values.push_back(viewWidth);

            EntityStatsManager::Value viewHeight;
            viewHeight.name = "View height";
            viewHeight.data = reinterpret_cast<void*>(&perspective.viewHeight);
            viewHeight.type = EntityStatsManager::ValueType::FLOAT;
            viewHeight.isModifiable = true;
            viewHeight.usesSlider = true;
            viewHeight.min = 0.1f;
            viewHeight.max = 10000.0f;
            values.push_back(viewHeight);

            EntityStatsManager::Value sensitivityValue;
            sensitivityValue.name = "Sensitivity";
            sensitivityValue.data = reinterpret_cast<void*>(&sensitivity);
            sensitivityValue.type = EntityStatsManager::ValueType::FLOAT;
            sensitivityValue.isModifiable = true;
            sensitivityValue.usesSlider = true;
            sensitivityValue.min = 0.01f;
            sensitivityValue.max = 10.0f;
            values.push_back(sensitivityValue);
        }
    };
} // namespace GLESC::ECS
