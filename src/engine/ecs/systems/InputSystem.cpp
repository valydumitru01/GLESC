/******************************************************************************
 * @file   InputSystem.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/systems/InputSystem.h"
#include "engine/ecs/frontend/component/InputComponent.h"

using namespace GLESC::ECS;

InputSystem::InputSystem(InputManager &inputManager, ECSCoordinator &ecs) :
    System(ecs, "InputSystem"), inputManager(inputManager) {
    addComponentRequirement<InputComponent>();
}

void InputSystem::update() {
    for (auto &entity : getAssociatedEntities()) {
        auto &input = getComponent<InputComponent>(entity);

        for (std::pair<const KeyInput, KeyCommand> &keyPressedPair : input.subscribedKeys) {
            const KeyInput &key = keyPressedPair.first;
            KeyCommand &command = keyPressedPair.second;

            if (inputManager.checkKeyAction(key)) {
                command.execute();
            }
        }

        input.mouseCommand.execute(inputManager.getMousePosition());
    }
}
