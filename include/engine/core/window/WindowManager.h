/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <memory>
#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "engine/core/math/algebra/vector/Vector.h"
#include "WindowStructs.h"


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
         * @brief Get the Window object
         *
         * @return SDL_Window* the windowManager object
         */
        SDL_Window &getWindow();

        /**
         * @brief Get the width and height of the window
         * @return WindowDimensions -> width: width of the window,
         *                             height: height of the window
         */
        [[nodiscard]] WindowDimensions getSize() const;

        /**
         * @brief Get the center of the window
         */
        [[nodiscard]] Vec2UI getWindowCenter() const;

        /**
         * @brief Callback function when window size is modified
         * This will change the viewport with the new resolution
         *
         */
        void setSize(uint16_t windowWidth, uint16_t windowHeight);

        /**
         * @brief Set the position of the window.
         * Changes the location of the window on the screen.
         *
         * @param windowX New X position.
         * @param windowY New Y position.
         */
        void setPosition(unsigned int windowX, unsigned int windowY);

        /**
         * @brief Get the position of the window.
         * @return Vec2I -> x: position on X axis, y: position on Y axis
         */
        [[nodiscard]] Vec2I getPosition();


        /**
         * @brief Set the window icon.
         * Updates the icon displayed in the window's title bar.
         *
         * @param iconFile Path to the icon file.
         */
        void setIcon(const std::string &iconFile);


        /**
         * @brief Gets whether the windowManager is fullscreen or not
         * @return true if windowManager is fullscreen, false otherwise
         */
        [[nodiscard]] bool isFullscreen();

        /**
         * @brief Turn fullscreen on or off
         * This will change the flags of the windowManager object
         *
         */
        void setFullscreen(bool isFullScreen);


        /**
         * @brief Sets the window borderless, meaning no title bar with close button
         * @param isBorderless true to enable, false to disable
         */
        void setBorderlessWindow(bool isBorderless);

        /**
         * @brief Gets whether the window is borderless or not
         * @return true if window is borderless, false otherwise
         */
        [[nodiscard]] bool isBorderlessWindow();


        /**
         * @brief Sets the window resizable. If enabled, the window can be resized by the user.
         * If disabled, the window cannot be resized, when trying to resize it, nothing will happen.
         * @param isResizable true to enable, false to disable
         */
        void setResizable(bool isResizable);

        /**
         * @brief Gets whether the window is resizable or not
         * @return true if window is resizable, false otherwise
         */
        [[nodiscard]] bool isResizable();


        /**
         * @brief Sets the window fullscreen borderless or "fake fullscreen".
         * @details This will make the window fullscreen but also facilitates changing to different
         * apps and windows. This won't change the resolution of the screen, like true fullscreen.
         * But also is less efficient than true fullscreen, costing more resources.
         * @param isFullScreen true to enable, false to disable
         */
        void setFullscreenBorderless(bool isFullScreen);

        /**
         * @brief Gets whether the window is fullscreen borderless or not
         * @return true if window is fullscreen borderless, false otherwise
         */
        [[nodiscard]] bool isFullscreenBorderless();

        /**
         * @brief Destroy window and release resources.
         */
        void destroyWindow();

    private:
        /**
         * @brief Initialize SDL_Window flags
         *
         * @return int the flags
         */
        [[nodiscard]] static uint32_t getRaisedFlags();

        /**
         * @brief Initialize SDL, checks if there is any error while doing it
         * Must be called before creating windowManager
         */
        static void initSDL();

        /**
         * @brief Initialize the windowManager with its title, setting its flags
         * Checks if there is any error while doing it.
         */
        [[nodiscard]] SDL_Window *createWindow(const char *title);


        /**
         * @brief The SDL window struct pointer
         *
         */
        SDL_Window *window;
    }; // class WindowManager
} // namespace GLESC
