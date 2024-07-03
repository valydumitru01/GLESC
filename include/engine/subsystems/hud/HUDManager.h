/**************************************************************************************************
 * @file   HUDManager.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#pragma once


#include <SDL2/SDL.h>

#include "engine/core/hash/Hasher.h"
#include "engine/subsystems/hud/InGameWindow.h"

namespace GLESC::HUD {
    class HUDManager {
    public:
        /**
         * The ID of a window
         */
        using WindowID = int;
        /**
         * @brief Constructor for the HUDManager
         * @param window The SDL window to render the HUD on
         */
        explicit HUDManager(SDL_Window& window);
        /**
         * @brief Destructor for the HUDManager
         */
        ~HUDManager();

        /**
         * @brief Process input for the HUD
         * @details Calls the ImGui SDL input processing function
         * @param event The SDL event to process
         */
        void processInput(SDL_Event& event);

        /**
         * @brief Add a new window to the HUD
         * @details Uses the move operator, this manager will take ownership of the window
         * @return the ID of the window
         */
        WindowID addWindow(InGameWindow& window);

        /**
         * @brief Get a window by its ID
         * @param id The ID of the window
         * @return The window
         */
        InGameWindow &getWindow(WindowID id);

        /**
         * Remove a window from the HUD
         * @param id The ID of the window to remove
         */
        void removeWindow(WindowID id);
        /**
         * @brief Update the HUD
         * @details Updates the positions of the windows given their layout configurations
         * and the current window size
         */
        void update();

        /**
         * @brief Render the HUD
         * @details The time of frame is needed to interpolate hud items and allow for smooth rendering
         * @param timeOfFrame The time of the current frame
         */
        void render(double timeOfFrame);

    private:
        void newFrame();

        void endFrame();

        void initImGUI();

        SDL_Window& window;
        WindowID nextWindowID = 0;
        std::vector<GLESC::InGameWindow*> windows;
        std::unordered_map<WindowID, GLESC::InGameWindow*> windowIDs;
    };
} // namespace GLESC::HUD
