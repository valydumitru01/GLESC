#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Util/Console.h"

/**
 * @brief 1.77 is the standard ratio (16:9)
 *
 */
#define WINDOW_RATIO 1.77
#define WINDOW_MIN_WIDTH 100
#define WINDOW_MIN_HEIGHT 177

class Window {
public:
	explicit Window(const char *title);

	~Window();

	/**
	 * @brief Callback function when window size is modified
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
	 * @return SDL_Window*
	 */
	SDL_Window &getWindow();

	/**
	 * @brief Get the Context object
	 *
	 * @return SDL_GLContext
	 */
	SDL_GLContext &getContext();

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
private:
	/**
	 * @brief Sets GL_SDL attributes, such as the stencil size or GL version
	 * Must be called before creating the windows
	 *
	 */
	void setGlAttributes();

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
	static int setFlags();

	/**
	 * @brief Initialize SDL, checks if there is any error while doing it
	 * Must be called before creating window
	 */
	void initSDL();

	/**
	 * @brief Initialize the window, setting its flags
	 * Checks if there is any error while doing it.
	 */
	void createWindow();

	/**
	 * @brief Initialize OpenGL
	 * Sets the viewport
	 * Creates the context
	 * Checks errors
	 */
	void initGL();

	static void initGLEW();

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