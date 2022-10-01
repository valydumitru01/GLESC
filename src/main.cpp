#include "Game.h"
#include "FPS.h"
#include <chrono>
#include <thread>




int SDL_main(int argc, char *argv[])
{

    Console::init();
    FPS fps(60);
    Game* game=new Game();
    game->init("Game", 800, 600, false);
    while (game->running())
    {
        fps.timeBeginningOfFrame();
        fps.delay();
        game->handleEvents();
        game->update(fps.getElapsed());
        game->render(fps.getElapsed());
        
        fps.timeEndOfFrame();
        //fps.printFPS();
    }

    game->clean();
    delete game;
    return 0;
}