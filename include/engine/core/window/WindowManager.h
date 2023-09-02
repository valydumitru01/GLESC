/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <string>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "engine/core/exceptions/EngineException.h"
#include "engine/core/window/WindowManager.h"
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/logger/Logger.h"
#include "engine/Config.h"

/**
 * @brief 1.77 is the standard ratio (16:9)
 *
 */
constexpr float windowRatio = 1.77f;
constexpr int windowMinWidth = 100;
constexpr int windowMinHeight = 177;
namespace GLESC {
    class WindowManager {
    public:
        explicit
        WindowManager(GLESC_RENDER_API &graphicInterfaceParam);
        
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
        SDL_Window &getWindow() ;
        
        /**
         * @brief Get the width of the windowManager
         * The renderer will use this to set the viewport
         * @return int the width
         */
        [[nodiscard]] int getWidth() const ;
        
        /**
         * @brief Get the height of the windowManager
         * The renderer will use this to set the viewport
         * @return int the height
         */
        [[nodiscard]] int getHeight() const ;
    
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
        SDL_Window *createWindow(const char *title);
        
        
        /**
         * @brief The graphics API used by the windowManager
         *
         */
        GLESC_RENDER_API &graphicInterface;
        
        /**
         * @brief The SDL windowManager object
         *
         */
        SDL_Window *window;
        /**
         * @brief True if is fullscreen and false if it is not
         *
         */
        SDL_bool fullscreen{GLESC_WINDOW_FULLSCREEN};
        
        /**
         * @brief Variable where the windowManager height is stored
         *
         */
        int height{GLESC_WINDOW_HEIGHT};
        /**
         * @brief Variable where the windowManager width is stored
         *
         */
        int width{GLESC_WINDOW_WIDTH};
        int x{GLESC_WINDOW_X};
        int y{GLESC_WINDOW_Y};
    }; // class WindowManager
    
} // namespace GLESC







