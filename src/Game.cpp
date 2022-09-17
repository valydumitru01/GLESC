#include "Game.h"
#include "MyPath.h"
#include "TextureManager.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{
    //Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }
    //Init GLEW
    glewExperimental = GL_TRUE;
    GLuint err =glewInit();
    if (err!=GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return;
    }
    window = new Window("My Game");
    window->init();
    renderer=new Renderer();
    renderer->init(window->height,window->width);

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
        window->setSize(event.window.data1, event.window.data2);
        break;
    default:
        break;
    }
}

void Game::update(double deltaTime)
{
    cnt++;

    
}

void Game::render(double deltaTime)
{


    renderer->render();
    window->SwapBuffers();
}

void Game::clean()
{
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
