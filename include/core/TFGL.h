#include "Types.h"


#include <vector>
#include <memory>


#include "core/Window.h"
#include "game/Game.h"
#include "core/FPS.h"

#include "Entity.h"
#include "EntityContainer.h"
#include "System.h"
#include "SystemContainer.h"

#include "core/systems/input/InputSystem.h"
#include "core/systems/transform/TransformSystem.h"
#include "core/systems/physics/PhysicsSystem.h"
#include "core/systems/render/RenderSystem.h"


#include "core/components/InputComponent.h"
#include "core/components/RenderComponent.h"
#include "core/components/CameraComponent.h"
#include "core/components/PhysicsComponent.h"
#include "core/components/TransformComponent.h"

class TFGL {
	friend int main();
private:
	TFGL();
	~TFGL();
	void update();
	void processInput();
	void render(double timeOfFrame);
	
	bool running;
	unique_ptr<EntityContainer> entityContainer;

public:
	inline void init();
	inline void loop();
};

