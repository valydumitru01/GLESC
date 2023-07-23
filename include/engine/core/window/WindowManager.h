#pragma once

#include <memory>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "engine/core/exceptions/EngineException.h"
#include "engine/core/graphics-device-interface/GraphicsInterface.h"

/**
 * @brief 1.77 is the standard ratio (16:9)
 *
 */
#define WINDOW_RATIO 1.77
#define WINDOW_MIN_WIDTH 100
#define WINDOW_MIN_HEIGHT 177

class WindowManager {
public:
    explicit WindowManager(const char *title, GraphicsInterface &graphicApi);
    
    /**
     * @brief Callback function when windowManager size is modified
     * This will call glViewport with the new resolution
     *
     */
    void setSize(int windowWidth, int windowHeight);
    
    /**
     * @brief Turn fullscreen on or off
     * This will change the flags of the windowManager object
     *
     */
    void setFullscreen(SDL_bool isFullScreen);
    
    /**
     * @brief Enables mouse
     * If enabled mouse is visible and position is absolute (allows moving it across the windowManager)
     * If disabled mouse is hidden and position is relative (stays in center)
     *
     * @param enabled
     */
    static void setMouseRelative(bool enabled);
    
    /**
     * @brief Get the Window object
     *
     * @return SDL_Window* the windowManager object
     */
    SDL_Window *getWindow();
    
    /**
     * @brief Get the width of the windowManager
     * The renderer will use this to set the viewport
     * @return int the width
     */
    [[nodiscard]] int getWidth() const;
    
    /**
     * @brief Get the height of the windowManager
     * The renderer will use this to set the viewport
     * @return int the height
     */
    [[nodiscard]] int getHeight() const;

private:
    
    /**
     * @brief Initialize SDL_Window flags
     *
     * @return int the flags
     */
    [[nodiscard]] static int getRaisedFlags();
    
    /**
     * @brief Initialize SDL, checks if there is any error while doing it
     * Must be called before creating windowManager
     */
    static void initSDL();
    
    /**
     * @brief Initialize the windowManager with its title, setting its flags
     * Checks if there is any error while doing it.
     */
    void createWindow(const char *title);
    
    /**
     * @brief The graphics API used by the windowManager
     *
     */
    GraphicsInterface &graphicApi;
    
    /**
     * @brief The SDL windowManager object
     *
     */
    std::shared_ptr <SDL_Window> window;
    /**
     * @brief True if is fullscreen and false if it is not
     *
     */
    SDL_bool fullscreen;
    
    /**
     * @brief Variable where the windowManager height is stored
     *
     */
    int height;
    /**
     * @brief Variable where the windowManager width is stored
     *
     */
    int width;
};