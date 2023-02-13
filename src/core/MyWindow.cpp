#include "core/MyWindow.h"

MyWindow::MyWindow(const char *title)
    // Init window name
    :windowName(title),
    // Init the window dimensions
    height(800),
    width(1200)
{
    
}
void MyWindow::setGlAttributes()
{
    /**
     * Attributes that configure SDL with OpenGL
     * More info: https://wiki.libsdl.org/SDL_GLattr
     */

    /**
     * @brief Core functions of OpenGL a.k.a. full
     * modern openGL functionality.
     * More info: https://wiki.libsdl.org/SDL_GLprofile
     *
     */
    setGlAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    /**
     * @brief We're using OpenGL Version 4.3 (released in 2012).
     * Changing this numbers will change some functions available of OpenGL.
     * Probably wouldn't affect us much.
     * Choosing a relatively old version of OpenGl allow most computers to use it.
     *
     */
    setGlAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    setGlAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#ifdef DEBUG
    Console::warning("ENTERING DEBUG MODE");
    /**
     * @brief Enables debug mode
     * Improves debugging outputs
     * Possible performance loss
     *
     */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

    // TODO: Learn what this attribute does
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void MyWindow::setGlAttribute(SDL_GLattr attrib, int val)
{
    if (SDL_GL_SetAttribute(attrib, val) == -1)
    {
        Console::error(string("Unable to set gl attribute: ") + string(SDL_GetError()));
    }
}
void MyWindow::init()
{

    //---------------------------Init SDL-----------------------
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Console::error(string("Unable to initialize SDL: ") + string(SDL_GetError()));
        return;
    }
    Console::success("SDL Initialized!");
    //-----------------------------------------------------------

    // Applying SDL_GL attributes
    setGlAttributes();

    //----------------------Create Window-------------------------
    int flags = setFlags();
    /* Create windows with SDL */
    if ((window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags)) == NULL)
    {
        Console::error(string("Unable to create window: ") + string(SDL_GetError()));

        return;
    }
    Console::success(string("Window created!"));
    // Set the minimum window size
    SDL_SetWindowMinimumSize(window, WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);

    /**
     * @brief Tells OpenGL which size is the viewport where things are displayed
     * @param Point Left bottom corner
     * @param Point Right up corner
     */
    glViewport(0, 0, width, height);
    /**
     * @brief
     *
     */
    /* OpenGL context initialization over the SDL window, needed for using OpenGL functions*/
    if ((context = SDL_GL_CreateContext(window)) == NULL)
    {
        Console::error(string("Unable to create context: ") + string(SDL_GetError()));
        return;
    }
    else
        Console::success("GL context created!");

    //----------------------------------------------------------

    //--------------------------Init GLEW-----------------------
    GLuint err;
    glewExperimental = GL_TRUE;
    if ((err = glewInit()) != GLEW_OK)
    {

        Console::error(string("Unable to initialize GLEW: "));
        std::cout << glewGetErrorString(err) << std::endl;
        return;
    }
    Console::success("Glew Initialized!");
    //-----------------------------------------------------------

    /*This makes our buffer swap syncronized with the monitor's vertical refresh
    0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive v-sync */
    if (SDL_GL_SetSwapInterval(1) == -1)
    {
        Console::error(string("Unable activate v-sync (swap interval): ") + string(SDL_GetError()));
    }

    /* Set mouse relative */
    setMouseRelative(true);
}
void MyWindow::setSize(GLsizei _width, GLsizei _height)
{
    height = _height;
    width = _width;
    glViewport(0, 0, width, height);
}
void MyWindow::setMouseRelative(bool enabled)
{
    SDL_bool isRelative;
    string failOutput;
    if (enabled)
    {
        isRelative = SDL_TRUE;
        failOutput = "disable";
    }
    else
    {
        isRelative = SDL_FALSE;
        failOutput = "enable";
    }
    /**
     * @brief Tells SDL whether we want to set relative mode to our mouse.
     */
    if (SDL_SetRelativeMouseMode(isRelative) == -1)
    {
        Console::error(string("Unable to") + failOutput + string("mouse relative mode: ") + string(SDL_GetError()));
    }
}
int MyWindow::setFlags()
{
    /**
     * @brief Flags that are needed to be passed to the window * to configure it.
     *
     * To add more flags we need to use the binary OR ( | )
     * More info: https://wiki.libsdl.org/SDL_WindowFlags
     */
    int flags = 0;
    /* Flag to allow SDL window work with OpenGL */
    flags |= SDL_WINDOW_OPENGL;

    /* Flag to allow window resize */
    flags |= SDL_WINDOW_RESIZABLE;
    /* WIndow has no borders */
    flags |= SDL_WINDOW_BORDERLESS;
    /* Window grabs input focus */
    flags |= SDL_WINDOW_INPUT_GRABBED;
    /* Window enables High pixel density if supported by monitor */
    flags |= SDL_WINDOW_ALLOW_HIGHDPI;

    return flags;
}
void MyWindow::setFullscreen(SDL_bool isFullScreen)
{
}
SDL_Window *MyWindow::getWindow()
{
    return window;
}
SDL_GLContext *MyWindow::getContext()
{
    return &context;
}
MyWindow::~MyWindow()
{
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
}
void MyWindow::SwapBuffers()
{
    SDL_GL_SwapWindow(window);
}