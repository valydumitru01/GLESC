#include "Game.h"
#include "FPS.h"
Game *game = nullptr;



int SDL_main(int argc, char *argv[])
{
    

    
    FPS fps(60);
    game = new Game();
    game->init("Game", 800, 600, false);
    while (game->running())
    {
        fps.timeBeginningOfFrame();
        game->handleEvents();
        game->update(fps.getElapsed());
        game->render(fps.getElapsed());
        fps.timeEndOfFrame();
        fps.printFPS();
    }

    game->clean();
    return 0;
}