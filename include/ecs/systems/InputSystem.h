
#include <vector>
#include "glm/glm.hpp"
#include "SDL2/SDL.h"
#include <map>

#include "ecs/components/InputComponent.h"
#include "ecs/systems/System.h"

class InputSystem : public System {
public:
    InputSystem() {
        addComponentRequirement<InputComponent>();
    }

    void update() {
        SDL_Event event;
        auto entities = getAssociatedEntities();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    // Handle quit event
                    break;
                }
                case SDL_MOUSEMOTION: {
                    for (auto &entity: entities) {
                        auto &inputComponent = getComponent<InputComponent>(entity);
                        inputComponent.mousePosition.x = event.motion.x;
                        inputComponent.mousePosition.y = event.motion.y;
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    for (auto &entity: entities) {
                        auto &inputComponent = getComponent<InputComponent>(entity);
                        inputComponent.keyMap[event.button.button] = true;
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    for (auto &entity: entities) {
                        auto &inputComponent = getComponent<InputComponent>(entity);
                        inputComponent.keyMap[event.key.keysym.sym] = true;
                    }
                    break;
                }
            }
        }
    }
};


