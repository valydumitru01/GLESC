#include "common.h"
#include "Game.h"

Game *game = nullptr;



int SDL_main(int argc, char *argv[])
{
    /**
     * @brief My max FPS
     * 
     */
    short FPS;
    /**
     * @brief The max time can elapse between frames
     * 
     */
    double FPS_MS;
    /**
     * @brief Time recorded at the beginning of the loop iteration
     * 
     */
    Uint64 start;
    /**
     * @brief Time recorded at the end of the loop iteration
     * 
     */
    Uint64 end;
    /**
     * @brief The actual time it elapses
     * 
     */
    double elapsed;


    elapsed=0;      //Initialised at 0, first frame is immobilized
    FPS=60;         //Initialize max fps at 60
    FPS_MS=1000.0/(double)FPS; //The max milliseconds of the frame is the division between 1000 (ms in a second) and the max fps

    game = new Game();
    game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game->running())
    {
        start = SDL_GetPerformanceCounter(); //Time of the beginning of the loop

        game->handleEvents();
        game->update(elapsed);
        game->render();   
        if(FPS_MS - elapsed > 0)
            SDL_Delay(FPS_MS - elapsed); //Cap the FPS, wait until we get to minumum frame time
        end = SDL_GetPerformanceCounter(); //Time of the end of the loop
        
        elapsed = (end - start) / (double)SDL_GetPerformanceFrequency(); //Calculate elapsed: time of the start of the iteration - time of the end of the iteration
        
        cout << "Current FPS: " << to_string(1.0f / elapsed) << endl;

	    
    }

    game->clean();
    return 0;
}