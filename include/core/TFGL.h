#include "Types.h"


#include <vector>
#include <memory>


#include "core/Window.h"
#include "core/FPS.h"

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

class TFGL {
	friend int main();
private:
	TFGL(){
	
	}
	~TFGL();
	void update(){
        loop();
		transformSystem.update();
		physicsSystem.update();
	}
	void processInput(){
		inputSystem.update();
	}
	void render(double timeOfFrame){
		cameraSystem.update(timeOfFrame);
		renderSystem.update(timeOfFrame);
	}
	
	bool running;
	unique_ptr<EntityContainer> entityContainer;
	
	InputSystem inputSystem;
	TransformSystem transformSystem;
	PhysicsSystem physicsSystem;
	RenderSystem renderSystem;
	CameraSystem cameraSystem;
public:
	inline void init();
	inline void loop();
};

