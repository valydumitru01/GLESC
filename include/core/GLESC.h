#include <vector>
#include <memory>


#include "renderer/WindowManager.h"
#include "core/FPS.h"
#include "core/Types.h"

#include "ecs/entities/Entity.h"

#include "ecs/systems/System.h"
#include "ecs/systems/InputSystem.h"
#include "ecs/systems/TransformSystem.h"
#include "ecs/systems/PhysicsSystem.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/systems/CameraSystem.h"

#include "ecs/components/InputComponent.h"
#include "ecs/components/RenderComponent.h"
#include "ecs/components/CameraComponent.h"
#include "ecs/components/PhysicsComponent.h"
#include "ecs/components/TransformComponent.h"


class GLESC {
    friend int main();

private:
    GLESC();
    
    ~GLESC();
    
    /**
     * @brief Is called every frame, must be called at constant intervals of time as it does not use elapsed, more
     * information https://www.gameprogrammingpatterns.com/game-loop.html
     */
    void update();
    
    /**
     * @brief The
     */
    void processInput();
    
    void render(double timeOfFrame);
    
    /**
     * @brief If true, the game is running. If false, the game is stopped.
     */
    bool running = true;
    
    /**
     * @brief The systems of the game
     * @note The order of the systems is important, as the systems are updated in the order they are declared
     */
    InputSystem inputSystem;
    TransformSystem transformSystem;
    PhysicsSystem physicsSystem;
    RenderSystem renderSystem;
    CameraSystem cameraSystem;
    
    /**
     * @brief Handles the window of the game
     */
    shared_ptr <WindowManager> windowManager;
    
    Renderer renderer;

public:
    void init();
    
    void loop();
};

