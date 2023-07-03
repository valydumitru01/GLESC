
#include <vector>
#include "glm/glm.hpp"
#include "SDL2/SDL.h"
#include <map>

#include "engine/ecs/components/InputComponent.h"
#include "System.h"

class InputSystem : public System {
public:
    InputSystem(bool &running);
    void init() override;
    void update();
    bool &running;
};


