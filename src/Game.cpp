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

    window->init();

    shaderManager = new ShaderManager();

    camera = new Camera(shaderManager);
    /*Need to instantiate renderer before initializing window.
    Window depends on the initialization of SDL*/
    renderer = new Renderer(window->height, window->width, shaderManager);

    renderer->init();

    isRunning = true;
}
bool firstMouse=false;
int lastX;
int lastY;
float pitch=90;
float yaw=0;
void Game::handleEvents()
{
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_D])
    {
        camera->moveRight();
    }
    if (state[SDL_SCANCODE_A])
    {
        camera->moveLeft();
    }
    if (state[SDL_SCANCODE_S])
    {
        camera->moveBackwards();
    }
    if (state[SDL_SCANCODE_W])
    {
        camera->moveForward();
    }
    if (state[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }
    // else if(state[SDL_SCANCODE_])

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
    case SDL_MOUSEMOTION:
    {
        int xMouse;
        int yMouse;
        
        SDL_GetGlobalMouseState(&xMouse, &yMouse);

        if (firstMouse)
        {
            lastX = window->width/2;
            lastY = window->height/2;
            firstMouse = false;
        }
        else{
        float xOffset = xMouse - lastX;
        float yOffset = lastY - yMouse; // reversed since y-coordinates range from bottom to top
        const float sensitivity = 0.005f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;
        yaw += xOffset;
        pitch += yOffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        camera->setDirection(yaw, pitch);

        Console::info(string("xMouse: ") + to_string(xMouse) + string("xMouse: ") + to_string(yMouse));
        }
    }

    break;
    default:
        break;
    }
}

void Game::update(double deltaTime)
{
    cnt++;
    camera->setElapsedTime(deltaTime);
}

void Game::render(double deltaTime)
{

    renderer->render();
    camera->updateView();
    window->SwapBuffers();
}

void Game::clean()
{
    delete camera;
    delete renderer;
    delete shaderManager;
    delete window;
    SDL_Quit();
    Console::importantInfo("Game cleaned");
}
