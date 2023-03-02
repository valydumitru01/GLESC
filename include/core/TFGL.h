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

class TFGL {
private:
	void update();
	
	void processInput();
	
	void render(double timeOfFrame);
	
	void loop();
	// Declare the game loop function
	extern "C" __declspec(dllexport) void TFGL_loop();
	
	bool running;
	FPS fps;
public:
	TFGL();
	
	~TFGL();
};

