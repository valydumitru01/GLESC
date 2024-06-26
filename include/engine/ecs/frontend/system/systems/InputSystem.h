/******************************************************************************
 * @file   InputSystem.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief System that updates the input manager
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
        explicit InputSystem(Input::InputManager& inputManager, ECSCoordinator& ecs);
        void update() override;

    private:
        Input::InputManager& inputManager;
    };
} // namespace GLESC::ECS