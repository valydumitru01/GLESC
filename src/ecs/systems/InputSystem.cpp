#include "core/systems/input/InputSystem.h"

void InputSystem::update() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                // Handle quit event
                break;
            }
            case SDL_MOUSEMOTION: {
                for (auto &inputComponent: getComponent) {
                    inputComponent.mousePosition.x = event.motion.x;
                    inputComponent.mousePosition.y = event.motion.y;
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                for (auto &entity: getAssociatedEntities()) {

                    if (event.button.button == SDL_BUTTON_LEFT) {
                        inputComponent.keyMap[SDL_BUTTON_LEFT] = true;
                    } else if (event.button.button == SDL_BUTTON_RIGHT) {
                        inputComponent.keyMap[SDL_BUTTON_RIGHT] = true;
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                for (auto &inputComponent: inputComponents) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        inputComponent.keyMap[SDL_BUTTON_LEFT] = false;
                    } else if (event.button.button == SDL_BUTTON_RIGHT) {
                        inputComponent.keyMap[SDL_BUTTON_RIGHT] = false;
                    }
                }
                break;
            }
            case SDL_KEYDOWN: {
                for (auto &inputComponent: inputComponents) {
                    if (keyActionMap.count(event.key.keysym.sym)) {
                        keyActionMap[event.key.keysym.sym](inputComponent);
                    }
                }
                break;
            }
        }
    }
}


void InputSystem::addKeyAction(int key, std::function<void(InputComponent & )> action) {
    keyActionMap[key] = action;
}