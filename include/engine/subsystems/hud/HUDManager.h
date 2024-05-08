/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <SDL2/SDL.h>

#include "engine/subsystems/hud/InGameWindow.h"


class HUDManager {
public:
    HUDManager(SDL_Window& window);
    ~HUDManager();

    void processInput(SDL_Event& event);

    void addWindow(GLESC::InGameWindow& window);

    void update();

    void render() const;


private:
    void updateNewFrame();

    void updateEndFrame();

    void initImGUI();

    SDL_Window& window;
    std::vector<GLESC::InGameWindow*> windows;
};
