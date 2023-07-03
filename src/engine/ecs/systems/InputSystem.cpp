#include "ecs/systems/InputSystem.h"

InputSystem::InputSystem(bool &running) : System("Input System"), running(running) {};

void InputSystem::update() {
    SDL_Event event;
    auto entities = getAssociatedEntities();
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                running = false;
                break;
            }
            case SDL_MOUSEMOTION: {
                for (auto &entity: entities) {
                    auto &inputComponent = getComponent <InputComponent>(entity);
                    inputComponent.mousePosition.x = event.motion.x;
                    inputComponent.mousePosition.y = event.motion.y;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                for (auto &entity: entities) {
                    auto &inputComponent = getComponent <InputComponent>(entity);
                    inputComponent.keyMap[event.button.button] = true;
                }
                break;
            }
            case SDL_KEYDOWN: {
                for (auto &entity: entities) {
                    auto &inputComponent = getComponent <InputComponent>(entity);
                    inputComponent.keyMap[event.key.keysym.sym] = true;
                }
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                break;
            }
        }
    }
}

void InputSystem::init() {
    addComponentRequirement <InputComponent>();
}

