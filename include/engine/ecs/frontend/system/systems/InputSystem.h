/******************************************************************************
 * @file   InputSystem.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/input/InputManager.h"

namespace GLESC::ECS {
    class InputSystem : public System {
    public:
        explicit InputSystem(InputManager& inputManager, ECSCoordinator& ecs);
        void update();

    private:
        InputManager& inputManager;
    };
} // namespace GLESC::ECS