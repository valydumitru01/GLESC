/**************************************************************************************************
 * @file   Light.h
 * @author Valentin Dumitru
 * @date   2024-03-31
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>

#include "engine/subsystems/renderer/RendererTypes.h"

struct Light {
    float intensity{1.0f};
    GLESC::Render::Rgb color{1.0f, 1.0f, 1.0f};

    Light() = default;

    [[nodiscard]] std::string toString() const {
        return "Intensity:" + std::to_string(intensity) + " Color:" + color.toString();
    }
}; // class Light
