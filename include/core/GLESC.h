#include <vector>
#include <memory>


#include "core/Window.h"
#include "core/FPS.h"
#include "core/Types.h"

#include "core/entities/Entity.h"

#include "core/systems/System.h"
#include "core/systems/input/InputSystem.h"
#include "core/systems/transform/TransformSystem.h"
#include "core/systems/physics/PhysicsSystem.h"
#include "core/systems/render/RenderSystem.h"
#include "core/systems/camera/CameraSystem.h"

#include "core/components/InputComponent.h"
#include "core/components/RenderComponent.h"
#include "core/components/CameraComponent.h"
#include "core/components/PhysicsComponent.h"
#include "core/components/TransformComponent.h"


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

	//---------Systems---------
	InputSystem inputSystem;
	TransformSystem transformSystem;
	PhysicsSystem physicsSystem;
	RenderSystem renderSystem;
	CameraSystem cameraSystem;
	//-------------------------

	/**
	 * @brief Handles the window of the game
	 */
	Window window;
	/**
	 * @brief Stores the window name, shown in the upper bar
	 * ________________________________________________
	 * |"windowTitle"·····················|·_·|·D·|·X·|
	 * |______________________________________________|
	 * |··············································|
	 */
	const char *windowTitle;
public:
	void init();

	void loop();
};

