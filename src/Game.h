#pragma once
#include "Window.h"
#include "Renderer.h"
#include "MyPath.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Console.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    void init(const char* title, int width, int height, bool fullscreen);
    
    /**
     * @brief Handle the events
     * 
     */
    void handleEvents();

    /**
     * @brief Update the screen updating the content
     * @param deltaTime Time between fps, so the movement speed remains constant
     */
    void update(double deltaTime);

    /**
     * @brief Render the game content
     * 
     */
    void render(double deltaTime);

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
    /**
     * @brief The main loop is running only if this boolean is true
     * 
     */
    bool isRunning = false;
    /**
     * @brief Counter of how many times the main loop runs
     * 
     */
    int cnt = 0;
    /**
     * @brief Pointer to the window of the game
     * 
     */
    Window *window;
    /**
     * @brief Pointer to the renderer of the game
     * 
     */
    Renderer* renderer;
    Camera* camera;
    ShaderManager* shaderManager;
    CoordinateSystem* coordSystem;

};

