#include "engine/ecs/systems/InputSystem.h"
#include "engine/ecs/components/InputComponent.h"


InputSystem::InputSystem(InputManager &inputManager) : System("InputSystem"), inputManager(inputManager) {
    addComponentRequirement <InputComponent>();
}

void InputSystem::update() {
    for (auto const &entity: getAssociatedEntities()) {
        auto &input = getComponent <InputComponent>(entity);
        for (auto &keyPressedPair: input.subscribedKeys) {
            keyPressedPair.second = inputManager.isKeyPressed(keyPressedPair.first);
        }
        
        input.mousePositionSubscribed = inputManager.getMousePosition();
    }
}

