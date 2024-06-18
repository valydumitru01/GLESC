/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <SDL2/SDL.h>

#include "engine/core/hash/Hasher.h"
#include "engine/subsystems/hud/InGameWindow.h"

namespace GLESC::HUD {
    class HUDManager {
    public:
        using WindowID = int;
        HUDManager(SDL_Window& window);
        ~HUDManager();

        void processInput(SDL_Event& event);

        /**
         * Add a new window to the HUD
         * Uses the move operator, this manager will take ownership of the window
         * @return the ID of the window
         */
        WindowID addWindow(GLESC::InGameWindow& window);

        GLESC::InGameWindow &getWindow(WindowID id);

        void removeWindow(WindowID id);

        void update();

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
