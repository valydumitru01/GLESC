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
#include "engine/core/graphics-device-interface/concrete-gdi/opengl/OpenGLGDI.h"
#include "engine/subsystems/physics/PhysicsManager.h"

class Engine {
    friend int main();


protected:
    Engine();

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
    OpenGLGDI graphicsInterface;
    /**
     * @brief Handles the window of the game
     */
    WindowManager windowManager;
    /**
     * @brief Handles the input of the game
     * @details Handles all the inputs of the game, and stores the state of the inputs.
     */
    InputManager inputManager;
    /**
     * @brief Handles the rendering of the game
     * @details Handles all the rendering of the game, provides a high level interface to the graphics API.
     * Can be used to render 2D and 3D graphics, including generating meshes and textures.
     */
    Renderer renderer;
    
    PhysicsManager physicsManager;
    
    InputSystem inputSystem;
    PhysicsSystem physicsSystem;
    RenderSystem renderSystem;
    CameraSystem cameraSystem;
    
    /**
     * @brief The entities of the game
     */
    std::unordered_map <std::string, Entity> entities;
public:
    void initGame();
    
    void loop();
};
    