#include "renderer/WindowManager.h"

WindowManager::WindowManager(const char *title) : windowTitle(title), // Init window name
                                                  height(800), width(1200), // Init the window dimensions
                                                  fullscreen(SDL_FALSE),// Init the window as not fullscreen
                                                  window(nullptr), // Init the window as null
                                                  context(nullptr) // Init the context as null
{
    initSDL();
    createWindow();
    
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
    if (SDL_GL_SetAttribute(attrib, val) == -1) {
        Console::error(string("Unable to set gl attribute: ") + string(SDL_GetError()));
    }
}

void WindowManager::initSDL() {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Console::error(string("Unable to initialize SDL: ") + string(SDL_GetError()));
        return;
    }
    Console::success("SDL Initialized!");
    
    // Applying SDL_GL attributes
    setGlAttributes();
}

void WindowManager::createWindow() {
    int flags = setFlags();
    // Create a shared pointer to an SDL window
    std::shared_ptr <SDL_Window> tempWindow(
            SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN),
            SDL_DestroyWindow);
    window = tempWindow;
    if (tempWindow == nullptr) {
        Console::error(string("Unable to create window: ") + string(SDL_GetError()));
        exit(0);
    }
    
    Console::success(string("Window created!"));
    window = tempWindow;
    SDL_SetWindowMinimumSize(window.get(), WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
}


void WindowManager::setSize(GLsizei width_, GLsizei height_) {
    height = height_;
    width = width_;
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
    if (SDL_SetRelativeMouseMode(isRelative) == -1) {
        Console::error(string("Unable to") + failOutput + string("mouse relative mode: ") + string(SDL_GetError()));
    }
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

SDL_GLContext WindowManager::getContext() {
    return context;
}

WindowManager::~WindowManager() {
    SDL_DestroyWindow(window.get());
    SDL_GL_DeleteContext(context);
}

void WindowManager::swapBuffers() {
    SDL_GL_SwapWindow(window.get());
}