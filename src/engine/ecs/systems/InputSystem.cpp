/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/ecs/frontend/system/systems/InputSystem.h"
#include "engine/ecs/frontend/component/InputComponent.h"


InputSystem::InputSystem(InputManager &inputManager, GLESC::ECS &ecs) :
        System(ecs, "InputSystem"), inputManager(inputManager) {
    addComponentRequirement<InputComponent>();
}

void InputSystem::update() {
    for (auto &entity : getAssociatedEntities()) {
        auto &input = getComponent<InputComponent>(entity);
        for (auto &keyPressedPair : input.subscribedKeys) {
            keyPressedPair.second = inputManager.isKeyPressed(keyPressedPair.first);
        }
        
        input.mousePosition = inputManager.getMousePosition();
    }
}

