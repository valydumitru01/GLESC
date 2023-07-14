#include "engine/plat-independence/window/WindowManager.h"
#include "engine/foundation/logger/Logger.h"
#include <string>

WindowManager::WindowManager(const char *title, GraphicsInterface &graphicApi) : graphicApi(graphicApi),
                                                                                 window(nullptr), fullscreen(SDL_FALSE),
                                                                                 height(800), width(1200) {
    initSDL();
    this->graphicApi.setAttributes();
    createWindow(title);
    // Enable mouse relative mode
    // This will make the mouse cursor invisible and locked in the middle of the screen
    setMouseRelative(true);
    
}


void WindowManager::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw EngineException("Unable to initialize SDL: " + std::string(SDL_GetError()));
    Logger::get().success("SDL Initialized!");
}

void WindowManager::createWindow(const char *title) {
    int flags = getRaisedFlags();
    SDL_Window *rawWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);
    if (rawWindow == nullptr)
        throw EngineException("Unable to create window: " + std::string(SDL_GetError()));
    
    
    // Create a shared_ptr to an SDL_Window and assign it to 'window'
    window = std::shared_ptr <SDL_Window>(rawWindow, SDL_DestroyWindow);
    
    Logger::get().success("Window created!");
    SDL_SetWindowMinimumSize(window.get(), WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    
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
    
    // Flags that are needed to be passed to the window * to configure it.
    // To add more flags we need to use the binary OR ( | )
    // More info: https://wiki.libsdl.org/SDL_WindowFlags
    
    int flags = 0;
    // Flag to allow SDL window work with OpenGL
    flags |= SDL_WINDOW_OPENGL;
    
    // Flag to allow window resize
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

SDL_Window *WindowManager::getWindow() {
    return window.get();
}

void WindowManager::swapBuffers() {
    graphicApi.swapBuffers(window);
}

int WindowManager::getWidth() const {
    return width;
}

int WindowManager::getHeight() const {
    return height;
}
