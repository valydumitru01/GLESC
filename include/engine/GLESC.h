#include <vector>
#include <memory>


#include "plat-independence/window/WindowManager.h"
#include "engine/foundation/FPS.h"
#include "ecs/ECSTypes.h"

#include "ecs/entities/Entity.h"
#include "ecs/ECSContainer.h"

#include "ecs/systems/System.h"
#include "ecs/systems/InputSystem.h"
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
    
    Entity& getEntity(std::string const &name);
    
    /**
     * @brief If true, the game is running. If false, the game is stopped.
     */
    bool running = true;
    /**
     * @brief Handles the window of the game
     */
    std::shared_ptr <WindowManager> windowManager;

    
    /**
     * @brief The systems of the game
     * @note The order of the systems is important, as the systems are updated in the order they are declared
     */
    InputSystem inputSystem;
    PhysicsSystem physicsSystem;
    RenderSystem renderSystem;
    CameraSystem cameraSystem;

    /**
     * @brief The entities of the game
     */
    unordered_map <std::string, Entity> entities;
public:
    void initGame();
    
    void loop();
};

