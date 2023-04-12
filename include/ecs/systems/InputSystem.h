
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <map>

#include "ecs/components/InputComponent.h"
#include "ecs/systems/System.h"

class InputSystem : public System {
public:
    InputSystem() : System("Input System") {};
    void init() override;
    
    void update();
};


