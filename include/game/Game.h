#pragma once
#include "core/Window.h"
#include "core/renderer/Renderer.h"
#include "util/MyPath.h"
#include "util/Console.h"
#include "core/renderer/ShaderManager.h"
#include "core/Camera.h"
#include "game/GUI.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Game
{

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
    void init(const char *title, int width, int height, bool fullscreen);




private:
};
