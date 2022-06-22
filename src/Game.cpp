#include "Game.h"
#include "MyPath.h"
#include "TextureManager.h"
SDL_Texture *playerText;
SDL_Rect srcRectangle, destRectangle;
double positionX = 0;
Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{

    /*Flags that are needed to be passed to the window to configure it.
    To add more flags we need to use the binary OR ( | )
    More info: https://wiki.libsdl.org/SDL_WindowFlags*/
    int flags = 0;
    /* Flag for allowing SDL window work with OpenGL */
    flags |= SDL_WINDOW_OPENGL;

    /**
     * @brief Attributes that configure SDL with OpenGL
     * More info: https://wiki.libsdl.org/SDL_GLattr
     */

    /*Core functions of OpenGL, we get to use all non-deprecated functions
    https://wiki.libsdl.org/SDL_GLprofile*/
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    /*We're using OpenGL Version 4.3 (released in 2012):
    Changing this numbers will change some functions available of OpenGL
    (probably wouldn't affect us that much, but it's better if we stay on just one)
    We are choosing this version as most computers will support it. */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    /* TODO: Learn about other attributes, including what this one does */
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    /* Initialize SDL, needs a paramterer to indicate what to initialize
    SDL has several subsystems like SDL_INIT_AUDIO or SDL_INIT_VIDEO.
    SDL_INIT_EVERYTHING is just a call to each one of them.
    More info: https://wiki.libsdl.org/SDL_Init */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    std::cout << "Subsystem initialized..." << std::endl;
    /* Create windows with SDL */
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    /* Returns null on error*/
    if (window == NULL)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return;
    }
    /* OpenGL context initialization over the SDL window, needed for
    using OpenGL functions*/
    context = SDL_GL_CreateContext(window);

    /* Returns null on error */
    if (context == NULL)
    {
        SDL_Log("Unable to create context: %s", SDL_GetError());
        return;
    }
    /* Needed before glewInit() to enable glew functionality,
    the word experimental is meaningless */
    glewExperimental = GL_TRUE;
    /* Init glew */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return;
    }

    std::string str = "example.png";
    char *path = MyPath::getImageDir(str);
    playerText = TextureManager::LoadTexture(path, renderer);

    isRunning = true;
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update(double deltaTime)
{
    cnt++;
    destRectangle.h = 64;
    destRectangle.w = 64;
    positionX += deltaTime * 100;
    destRectangle.x = std::trunc(positionX);

    std::cout << destRectangle.x << std::endl;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // null, for the source rectangle will use the entire image
    // null, will draw the whole render frame
    SDL_RenderCopy(renderer, playerText, NULL, &destRectangle);
    // this is where we would add stuff to render
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
