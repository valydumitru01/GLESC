#ifndef Game_h
#define Game_h

#include "SDL2/SDL.h"
#include <iostream>

class Game {

public:

    /**
     * @brief Construct a new Game object
     * 
     */
    Game();

    /**
     * @brief Destroy the Game object
     * 
     */
    ~Game();

    /**
     * @brief Initialize the game
     * 
     * @param title     Title of the window
     * @param xpos      Position x of the window
     * @param ypos      Position y of the window
     * @param width     Width of the window
     * @param height    Height of the window
     * @param fullscreen Indicates if fullscreen is active or not
     */
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    /**
     * @brief Handle the events
     * 
     */
    void handleEvents();

    /**
     * @brief Update the screen updating the content
     * 
     */
    void update();

    /**
     * @brief Render the game content
     * 
     */
    void render();

    /**
     * @brief Clean window and quit the game
     * 
     */
    void clean();

    /**
     * @brief Return if the game is running or not
     * 
     * @return true     if the game is runnint
     * @return false    if the game is not running
     */
    bool running(){ return isRunning; }


private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

};

#endif