#pragma once
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Util/Console.h"

/**
 * @brief 1.77 is the standard ratio (16:9)
 *
 */
#define WINDOW_RATIO 1.77
#define WINDOW_MIN_WIDTH 100
#define WINDOW_MIN_HEIGHT (WINDOW_MIN_WIDTH * WINDOW_RATIO)
class Window
{
public:
    ~Window();
    Window(const char *title);
    /**
     * @brief Function to initialize our window with its corresponding flags
     *
     */
    void init();
    /**
     * @brief Callback fuction when window size is modified
     * This will call glViewport with the new resolution
     *
     */
    void setSize(GLint width, GLint height);
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
    void setMouseRelative(bool enabled);
    /**
     * @brief Swap our buffer to display the current
     * contents of buffer on screen
     *
     */
    void swapBuffers();
    /**
     * @brief Get the Window object
     *
     * @return SDL_Window*
     */
    SDL_Window *getWindow();
    /**
     * @brief Get the Context object
     *
     * @return SDL_GLContext
     */
    SDL_GLContext *getContext();
    /**height
     * @brief Variable where the window height is stored
     *
     */
    int height;
    /**
     * @brief Variable where the window width is stored
     *
     */
    int width;

    bool mouseRelative=false;

private:
    /**
     * @brief Sets GL_SDL attributes, such as the stencil size or GL version
     *
     */
    void setGlAttributes();
    /**
     * @brief Sets one GL_SDL attribute, checks if there was any error while enabling it
     *
     */
    void setGlAttribute(SDL_GLattr attrib, int val);
    /**
     * @brief Initialize SDL_Window flags
     *
     * @return int the flags
     */
    int setFlags();
    /**
     * @brief The window object
     *
     */
    SDL_Window *window;
    /**
     * @brief True if is fullscreen and false if it is not
     *
     */
    SDL_bool fullscreen = SDL_FALSE;
    /**
     * @brief OpenGL context
     *
     */
    SDL_GLContext context;
    /**
     * @brief Variable where the window name is stored
     *
     */
    const char *windowName;
};