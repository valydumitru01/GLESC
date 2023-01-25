#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{

    window = new MyWindow("My Game");

    window->init();

    shaderManager = new ShaderManager();

    camera = new Camera(shaderManager);

    coordSystem = new CoordinateSystem(height, width, camera->cameraPos);

    gui = new GUI(window, shaderManager);
    /*Need to instantiate renderer before initializing window.
    Window depends on the initialization of SDL*/
    renderer = new Renderer(window->height, window->width, shaderManager, coordSystem);

    renderer->init();

    isRunning = true;
}
bool firstMouse = false;
int lastX;
int lastY;
float pitch = 0;
float yaw = 0;
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
    if (state[SDL_SCANCODE_SPACE])
    {
        camera->moveUp();
    }
    if (state[SDL_SCANCODE_LSHIFT])
    {
        camera->moveDown();
    }
    if (state[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
        return;
    }
    if (state[SDL_SCANCODE_LCTRL])
    {
    }

    // else if(state[SDL_SCANCODE_])

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        ImGui_ImplSDL2_ProcessEvent(&event);
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
            int xMouse = event.motion.xrel;
            int yMouse = event.motion.yrel;

            if (firstMouse)
            {
                lastX = window->width / 2;
                lastY = window->height / 2;
                firstMouse = false;
            }
            else
            {
                float xOffset = xMouse - lastX;
                float yOffset = lastY - yMouse; // reversed since y-coordinates range from bottom to top
                const float sensitivity = 0.04f;
                xOffset *= sensitivity;
                yOffset *= sensitivity;
                camera->yaw += xOffset;
                camera->pitch += yOffset;

                if (camera->pitch > 89.0f)
                    camera->pitch = 89.0f;
                if (camera->pitch < -89.0f)
                    camera->pitch = -89.0f;
                if(mouseEnabled)
                    camera->updateDirection();

                Console::info(string("xMouse: ") + to_string(xMouse) + string("xMouse: ") + to_string(yMouse));
            }
        }
        break;
        case SDL_KEYDOWN:
        {
            /* Check the SDLKey values and move change the coords */
            switch (event.key.keysym.sym)
            {
            case SDLK_LCTRL:
                window->mouseRelative=!window->mouseRelative;
                window->setMouseRelative(window->mouseRelative);
                break;
            case SDLK_d:
                break;
            case SDLK_s:
                break;
            case SDLK_w:
                break;
            default:
                break;
            }
        }
        default:
            break;
        }
    }
}

void Game::update(double deltaTime)
{
    cnt++;
    gui->update();
    camera->setElapsedTime(deltaTime);
    // gui->update();
}

void Game::render(double deltaTime)
{
    coordSystem->setView(camera->getLookAtMatrix());
    gui->render();
    camera->updateDirection();
    renderer->render();
    gui->render();
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
