#pragma once

#include <memory>
#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "engine/core/debug-profile/Console.h"
#include "engine/foundation/exceptions/EngineException.h"

/**
 * @brief 1.77 is the standard ratio (16:9)
 *
 */
#define WINDOW_RATIO 1.77
#define WINDOW_MIN_WIDTH 100
#define WINDOW_MIN_HEIGHT 177

class WindowManager {
public:
    explicit WindowManager(const char *title);
    
    /**
     * @brief Callback function when window size is modified
     * This will call glViewport with the new resolution
     *
     */
    void setSize(GLint windowWidth, GLint windowHeight);
    
    /**
     * @brief Turn fullscreen on or off
     * This will change the flags of the window object
     *
     */
    void setFullscreen(SDL_bool isFullScreen);
    
    /**
     * @brief Enables mouse
     * If enabled mouse is visible and position is absolute (allows moving it across the window)
     * If disabled mouse is hidden and position is relative (stays in center)
     *
     * @param enabled
     */
    static void setMouseRelative(bool enabled);
    
    /**
     * @brief Swap our buffer to display the current
     * contents of buffer on screen
     *
     */
    void swapBuffers();
    
    /**
     * @brief Get the Window object
     *
     * @return SDL_Window* the window object
     */
    SDL_Window *getWindow();
    
    /**
     * @brief Get the width of the window
     * The renderer will use this to set the viewport
     * @return int the width
     */
    [[nodiscard]] int getWidth() const;
    
    /**
     * @brief Get the height of the window
     * The renderer will use this to set the viewport
     * @return int the height
     */
    [[nodiscard]] int getHeight() const;

private:
    /**
     * @brief Sets GL_SDL attributes, such as the stencil size or GL version
     * Must be called before creating the windows
     *
     */
    static void setGlAttributes();
    
    /**
     * @brief Sets one GL_SDL attribute, checks if there was any error while enabling it
     *
     */
    static void setGlAttribute(SDL_GLattr attrib, int val);
    
    /**
     * @brief Initialize SDL_Window flags
     *
     * @return int the flags
     */
    static int getRaisedFlags();
    
    /**
     * @brief Initialize SDL, checks if there is any error while doing it
     * Must be called before creating window
     */
    static void initSDL();
    
    /**
     * @brief Initialize the window with its title, setting its flags
     * Checks if there is any error while doing it.
     */
    void createWindow(const char *title);
    
    /**
     * @brief The SDL window object
     *
     */
    shared_ptr <SDL_Window> window;
    /**
     * @brief True if is fullscreen and false if it is not
     *
     */
    SDL_bool fullscreen;
    
    /**
     * @brief Variable where the window height is stored
     *
     */
    int height;
    /**
     * @brief Variable where the window width is stored
     *
     */
    int width;
};