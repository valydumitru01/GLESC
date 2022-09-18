#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{
    


    
    window = new Window("My Game");
    /*Need to instantiate renderer before initializing window.
    Window depends on the initialization of SDL*/
    renderer=new Renderer(window->height,window->width);

    window->init();
    renderer->init();

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
