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
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
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
        WindowManager();
        
        /**
         * @brief Callback function when windowManager size is modified
         * This will call glViewport with the new resolution
         *
         */
        void setSize(uint16_t windowWidth, uint16_t windowHeight);
        
        
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
        void setMouseRelative(bool enabled);
        
        /**
         * @brief Get the Window object
         *
         * @return SDL_Window* the windowManager object
         */
        SDL_Window &getWindow();
        
        /**
         * @brief Get the width of the windowManager
         * @return int the width
         */
        [[nodiscard]] uint32_t getWidth() const;
        
        /**
         * @brief Get the height of the windowManager
         * @return int the height
         */
        [[nodiscard]] uint32_t getHeight() const;
    
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
        
        SDL_bool isInitialized{SDL_FALSE};
        
        /**
         * @brief The SDL window struct pointer
         *
         */
        SDL_Window *window;
        /**
         * @brief True if is fullscreen and false if it is not
         *
         */
        SDL_bool fullscreen{GLESC_WINDOW_FULLSCREEN};
        
        /**
         * @brief Height of the window in pixels
         *
         */
        uint32_t height{GLESC_WINDOW_HEIGHT};
        /**
         * @brief Width of the window in pixels
         *
         */
        uint32_t width{GLESC_WINDOW_WIDTH};
        uint32_t x{GLESC_WINDOW_X};
        uint32_t y{GLESC_WINDOW_Y};
    }; // class WindowManager
    
} // namespace GLESC







