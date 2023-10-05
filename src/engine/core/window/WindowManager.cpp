/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/core/window/WindowManager.h"
using namespace GLESC;
WindowManager::WindowManager(GLESC_RENDER_API &graphicInterfaceParam) :
        graphicInterface(graphicInterfaceParam) {
    initSDL();
    window = createWindow(GLESC_WINDOW_TITLE);
    graphicInterface.preWindowCreationInit();
    graphicInterface.createContext(*window, width, height, x, y);
    graphicInterface.postWindowCreationInit();
    
    isInitialized = SDL_TRUE;
    // Enable mouse relative mode
    // This will make the mouse cursor invisible and locked in the middle of the screen
    setMouseRelative(true);
}

void WindowManager::setSize(uint16_t windowWidth, uint16_t windowHeight) {
    ASSERT(isInitialized, "WindowManager not initialized! Cannot set size!");
    width = windowWidth;
    height = windowHeight;
    
    graphicInterface.setViewport(0, 0, width, height);
}


void WindowManager::setFullscreen(SDL_bool isFullScreen) {
    ASSERT(isInitialized, "WindowManager not initialized! Cannot set fullscreen!");
    fullscreen = isFullScreen;
    SDL_SetWindowFullscreen(window, fullscreen);
}


void WindowManager::setMouseRelative(bool enabled) {
    ASSERT(isInitialized, "WindowManager not initialized! Cannot set mouse relative!");
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
        throw EngineException(
                "Unable to " + failOutput + " mouse relative mode: " + std::string(SDL_GetError()));
}

SDL_Window &WindowManager::getWindow() {
    ASSERT(isInitialized, "WindowManager not initialized! Cannot get window!");
    return *window;
}

uint32_t WindowManager::getWidth() const {
    ASSERT(isInitialized, "WindowManager not initialized! Cannot get width!");
    return width;
}


uint32_t WindowManager::getHeight() const {
    ASSERT(isInitialized, "WindowManager not initialized! Cannot get height!");
    return height;
}

int WindowManager::getRaisedFlags() {
    
    // Flags that are needed to be passed to the windowManager * to configure it.
    // To add more flags we need to use the binary OR ( | )
    // More info: https://wiki.libsdl.org/SDL_WindowFlags
    
    int flags = 0;
    #if GLESC_RENDER_API == OpenGLAPI
    // Flag to allow SDL windowManager work with OpenGL
    flags |= SDL_WINDOW_OPENGL;
    #elif GLESC_RENDER_API == VulkanAPI
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


void WindowManager::initSDL() {
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    ASSERT_EQUAL(result, 0, "Unable to initialize SDL: " + std::string(SDL_GetError()));
    Logger::get().success("SDL Initialized!");
}


SDL_Window *WindowManager::createWindow(const char *title) {
    int flags = getRaisedFlags();
    SDL_Window *tempWindow =
            SDL_CreateWindow(title, GLESC_WINDOW_X, GLESC_WINDOW_Y, GLESC_WINDOW_WIDTH, GLESC_WINDOW_HEIGHT, flags);
    ASSERT_NOT_EQUAL(tempWindow, nullptr, "Unable to create windowManager: " + std::string(SDL_GetError()));
    Logger::get().success("Window created!");
    SDL_SetWindowMinimumSize(tempWindow, windowMinWidth, windowMinHeight);
    
    return tempWindow;
}