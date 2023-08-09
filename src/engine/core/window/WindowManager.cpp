/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/window/WindowManager.h"
#include "engine/core/logger/Logger.h"
#include "engine/Config.h"
#include <string>

using namespace GLESC;

WindowManager::WindowManager(GraphicInterface &graphicInterfaceParam) :
        graphicInterface(graphicInterfaceParam), fullscreen(SDL_FALSE), height(800), width(1200), x(0), y(0) {
    initSDL();
    window = createWindow(GLESC_WINDOW_TITLE);
    graphicInterface.createContext(*window, width, height, x, y);
    graphicInterface.postWindowCreationInit();
    
    
    // Enable mouse relative mode
    // This will make the mouse cursor invisible and locked in the middle of the screen
    setMouseRelative(true);
    
}


void WindowManager::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw EngineException("Unable to initialize SDL: " + std::string(SDL_GetError()));
    Logger::get().success("SDL Initialized!");
}

SDL_Window *WindowManager::createWindow(const char *title) {
    int flags = getRaisedFlags();
    SDL_Window *tempWindow = SDL_CreateWindow(title, GLESC_WINDOW_X, GLESC_WINDOW_Y, GLESC_WINDOW_WIDTH, GLESC_WINDOW_HEIGHT, flags);
    if (tempWindow == nullptr)
        throw EngineException("Unable to create windowManager: " + std::string(SDL_GetError()));
    
    Logger::get().success("Window created!");
    SDL_SetWindowMinimumSize(tempWindow, WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    
    return tempWindow;
}


void WindowManager::setSize(int windowWidth, int windowHeight) {
    width = windowWidth;
    height = windowHeight;
    
    graphicInterface.setViewport(0, 0, width, height);
}

void WindowManager::setMouseRelative(bool enabled) {
    SDL_bool isRelative;
    std::string failOutput;
    if (enabled) {
        isRelative = SDL_TRUE;
        failOutput = "disable";
    } else {
        isRelative = SDL_FALSE;
        failOutput = "enable";
    }
    
    // Tells SDL whether we want to set relative mode to our mouse.
    if (SDL_SetRelativeMouseMode(isRelative) == -1)
        throw EngineException("Unable to " + failOutput + " mouse relative mode: " + std::string(SDL_GetError()));
}

int WindowManager::getRaisedFlags() {
    
    // Flags that are needed to be passed to the windowManager * to configure it.
    // To add more flags we need to use the binary OR ( | )
    // More info: https://wiki.libsdl.org/SDL_WindowFlags
    
    int flags = 0;
    #ifdef GLESC_RENDER_OPENGL
    // Flag to allow SDL windowManager work with OpenGL
    flags |= SDL_WINDOW_OPENGL;
    #elif defined RENDER_VULKAN
    flags |= SDL_WINDOW_VULKAN;
    #endif
    // Flag to allow windowManager resize
    flags |= SDL_WINDOW_RESIZABLE;
    // Window has no borders
    // flags |= SDL_WINDOW_BORDERLESS;
    // Window grabs input focus
    flags |= SDL_WINDOW_INPUT_GRABBED;
    // Window enables High pixel density if supported by monitor
    flags |= SDL_WINDOW_ALLOW_HIGHDPI;
    
    return flags;
}

void WindowManager::setFullscreen(SDL_bool isFullScreen) {
    // TODO: Implement full screen capability
}

SDL_Window &WindowManager::getWindow() {
    return *window;
}

int WindowManager::getWidth() const {
    return width;
}

int WindowManager::getHeight() const {
    return height;
}
