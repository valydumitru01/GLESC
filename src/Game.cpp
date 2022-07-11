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

    window = new Window((char*)"My Game");
    window->init();
    shaderLoader=new ShaderLoader();
    
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
    
    /* OpenGL context initialization over the SDL window, needed for
    using OpenGL functions*/
    context = SDL_GL_CreateContext(this->window->getWindow());

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
    
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };  
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    shaderLoader->LoadAndLinkAll();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  


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
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        window->setSize(event.window.data1,event.window.data2);
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
    
}

void Game::clean()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
