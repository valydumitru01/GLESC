#include <vector>
#include <memory>


#include "core/window/WindowManager.h"
#include "engine/core/counter/Counter.h"
// ECS
#include "ecs/ECSTypes.h"
#include "ecs/ECSContainer.h"
// Entity
#include "ecs/entities/Entity.h"
// Systems
#include "ecs/systems/System.h"
#include "ecs/systems/PhysicsSystem.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/systems/CameraSystem.h"
#include "engine/ecs/systems/InputSystem.h"
// Components
#include "ecs/components/RenderComponent.h"
#include "ecs/components/CameraComponent.h"
#include "ecs/components/PhysicsComponent.h"
#include "ecs/components/TransformComponent.h"

#include "engine/subsystems/input/InputManager.h"

class GLESC {
    friend int main();


protected:
    GLESC();

private:
    /**
     * @brief Is called every frame, must be called at constant intervals of time as it does not use elapsed, more
     * information https://www.gameprogrammingpatterns.com/game-loop.html
     */
    void update();
    
    /**
     * @brief The input of the game
     */
    void processInput();
    
    /**
     * @brief The rendering of the game
     * @param timeOfFrame The time of the frame
     */
    void render(double timeOfFrame);
    
    void createEntity(std::string const &name);
    
    Entity &getEntity(std::string const &name);
    
    /**
     * @brief If true, the game is running. If false, the game is stopped.
     */
    bool running = true;
    
    /**
     * @brief This is the graphic interface, it is used as low level interface to the graphics API
     */
    GraphicsInterface &graphicsInterface;
    /**
     * @brief Handles the window of the game
     */
    WindowManager &windowManager;
    /**
     * @brief Handles the input of the game
     * @details Handles all the inputs of the game, and stores the state of the inputs.
     */
    InputManager &inputManager;
    /**
     * @brief The systems of the game
     * @note The order of the systems is important, as the systems are updated in the order they are declared
     */
    InputSystem& inputSystem;
    PhysicsSystem& physicsSystem;
    RenderSystem& renderSystem;
    CameraSystem& cameraSystem;
    
    /**
     * @brief The entities of the game
     */
    std::unordered_map <std::string, Entity> entities;
public:
    void initGame();
    
    void loop();
};

