#include "engine/core/window/WindowManager.h"
#include "engine/core/logger/Logger.h"
#include <string>

WindowManager::WindowManager(const char *title, GraphicsInterface &graphicApi) : graphicApi(graphicApi),
                                                                                 window(createWindow(title)), fullscreen(SDL_FALSE),
                                                                                 height(800), width(1200) {
    initSDL();
    
    // Enable mouse relative mode
    // This will make the mouse cursor invisible and locked in the middle of the screen
    setMouseRelative(true);
    
}


void WindowManager::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw EngineException("Unable to initialize SDL: " + std::string(SDL_GetError()));
    Logger::get().success("SDL Initialized!");
}

SDL_Window & WindowManager::createWindow(const char *title) {
    this->graphicApi.setAttributes();
    int flags = getRaisedFlags();
    SDL_Window *tempWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);
    if (tempWindow == nullptr)
        throw EngineException("Unable to create windowManager: " + std::string(SDL_GetError()));
    
    Logger::get().success("Window created!");
    SDL_SetWindowMinimumSize(tempWindow, WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    
    return *tempWindow;
}


void WindowManager::setSize(int windowWidth, int windowHeight) {
    width = windowWidth;
    height = windowHeight;
    
    graphicApi.setViewport(0, 0, width, height);
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
    // Flag to allow SDL windowManager work with OpenGL
    flags |= SDL_WINDOW_OPENGL;
    
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
    return window;
}

int WindowManager::getWidth() const {
    return width;
}

int WindowManager::getHeight() const {
    return height;
}
