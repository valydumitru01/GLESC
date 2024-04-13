/**************************************************************************************************
 * @file   Camera.h
 * @author Valentin Dumitru
 * @date   2024-04-10
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::Render {
    class CameraPerspective {
    public:
        CameraPerspective() = default;

        CameraPerspective(const Math::Distance& fovDegrees, const Math::Distance& nearPlane,
                          const Math::Distance& farPlane, const Math::Distance& viewWidth,
                          const Math::Distance& viewHeight)
            : fovDegrees(fovDegrees), viewWidth(viewWidth), viewHeight(viewHeight), nearPlane(nearPlane),
              farPlane(farPlane) {
        }

        Math::Distance fovDegrees{0};
        Math::Distance viewWidth{0};
        Math::Distance viewHeight{0};
        Math::Distance nearPlane{0};
        Math::Distance farPlane{0};

        [[nodiscard]] std::string toString() const {
            return std::string("\n\tfov: ")
                + std::to_string(fovDegrees)
                + std::string("\n\tviewWidth: ")
                + std::to_string(viewWidth)
                + std::string("\n\tviewHeight: ")
                + std::to_string(viewHeight)
                + std::string("\n\tnearPlane: ")
                + std::to_string(nearPlane)
                + std::string("\n\tfarPlane: ")
                + std::to_string(farPlane);
        }

    protected:

    private:
    }; // class CameraPerspective
} // namespace GLESC::Render
