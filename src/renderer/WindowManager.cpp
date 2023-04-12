#include "renderer/WindowManager.h"

WindowManager::WindowManager(const char *title) : window(nullptr), fullscreen(SDL_FALSE),
                                                  height(800),
                                                  width(1200) {
    initSDL();
    createWindow(title);
    // Enable mouse relative mode
    // This will make the mouse cursor invisible and locked in the middle of the screen
    setMouseRelative(true);
    
}

void WindowManager::setGlAttributes() {
    
    // Attributes that configure SDL with OpenGL
    // More info: https://wiki.libsdl.org/SDL_GLattr
    
    
    // @brief Core functions of OpenGL a.k.a. full modern openGL functionality.
    // More info: https://wiki.libsdl.org/SDL_GLprofile
    setGlAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // We're using OpenGL Version 4.3 (released in 2012).
    // Changing this numbers will change some functions available of OpenGL.
    // Choosing a relatively old version of OpenGl allow most computers to use it.
    setGlAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    setGlAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    #ifdef DEBUG
    Console::warning("ENTERING DEBUG MODE");
    //
    // @brief Enables debug mode
    // Improves debugging outputs
    // Possible performance loss
    //
    //
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    #endif
    
    // Stencil size of 4 bits is used
    // Could be increased later if needed
    // Increases performance the lower it is, less data stored in each pixel
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 4);
}

void WindowManager::setGlAttribute(SDL_GLattr attrib, int val) {
    if (SDL_GL_SetAttribute(attrib, val) == -1)
        throw EngineException("Unable to set gl attribute: " + string(SDL_GetError()));
    
}

void WindowManager::initSDL() {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw EngineException("Unable to initialize SDL: " + string(SDL_GetError()));
    
    Console::success("SDL Initialized!");
    
    // Applying SDL_GL attributes
    setGlAttributes();
}

void WindowManager::createWindow(const char *title) {
    int flags = setFlags();
    SDL_Window *rawWindow =
            SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);
    if (rawWindow == nullptr) {
        throw EngineException("Unable to create window: " + std::string(SDL_GetError()));
    }
    
    // Create a shared_ptr to an SDL_Window and assign it to 'window'
    window = std::shared_ptr <SDL_Window>(rawWindow, SDL_DestroyWindow);
    
    Console::success("Window created!");
    SDL_SetWindowMinimumSize(window.get(), WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    
}


void WindowManager::setSize(GLsizei windowWidth, GLsizei windowHeight) {
    width = windowWidth;
    height = windowHeight;
    glViewport(0, 0, width, height);
}

void WindowManager::setMouseRelative(bool enabled) {
    SDL_bool isRelative;
    string failOutput;
    if (enabled) {
        isRelative = SDL_TRUE;
        failOutput = "disable";
    } else {
        isRelative = SDL_FALSE;
        failOutput = "enable";
    }
    
    // Tells SDL whether we want to set relative mode to our mouse.
    if (SDL_SetRelativeMouseMode(isRelative) == -1)
        throw EngineException("Unable to " + failOutput + " mouse relative mode: " + string(SDL_GetError()));
}

int WindowManager::setFlags() {
    
    // Flags that are needed to be passed to the window * to configure it.
    // To add more flags we need to use the binary OR ( | )
    // More info: https://wiki.libsdl.org/SDL_WindowFlags
    
    int flags = 0;
    // Flag to allow SDL window work with OpenGL
    flags |= SDL_WINDOW_OPENGL;
    
    // Flag to allow window resize
    flags |= SDL_WINDOW_RESIZABLE;
    // Window has no borders
    flags |= SDL_WINDOW_BORDERLESS;
    // Window grabs input focus
    flags |= SDL_WINDOW_INPUT_GRABBED;
    /* Window enables High pixel density if supported by monitor */
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
    SDL_GL_SwapWindow(window.get());
}

int WindowManager::getWidth() const {
    return width;
}

int WindowManager::getHeight() const {
    return height;
}
