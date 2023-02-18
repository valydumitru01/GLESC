#include "Types.h"

#include "core/Window.h"
#include "game/Game.h"
#include "core/FPS.h"

#include <vector>
#include <memory>


class TFGL
{
private:



public:
    TFGL();
    ~TFGL();
    
    void update();
    void processInput();
    void render(double const timeOfFrame);

    void loop();

    
    std::unique_ptr<Window> window;

    FPS fps;
    Renderer renderer;
    InputHandler inputHandler;
    

    bool running;

};

