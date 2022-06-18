#include "Game.h"
#include "MyPath.h"
#include "TextureManager.h"

enum class SCREENSIZE
{
    is640x480,
    is1366x768,
    fullscreen
};

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{

    int flags = 0;
    std::vector<SDL_DisplayMode> mResolutions;

    int display_count = SDL_GetNumVideoDisplays();

    SDL_Log("Number of displays: %i", display_count);

    for (int display_index = 0; display_index <= display_count; display_index++)
    {
        SDL_Log("Display %i:", display_index);

        int modes_count = SDL_GetNumDisplayModes(display_index);

        for (int mode_index = 0; mode_index <= modes_count; mode_index++)
        {
            SDL_DisplayMode mode = {SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0};

            if (SDL_GetDisplayMode(display_index, mode_index, &mode) == 0)
            {
                SDL_Log(" %i bpp\t%i x %i @ %iHz",
                        SDL_BITSPERPIXEL(mode.format), mode.w, mode.h, mode.refresh_rate);

                mResolutions.push_back(mode);
            }
        }
    }

    unsigned int window_flags = SDL_WINDOW_OPENGL;
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Failed to init SDL Video, error: %s", SDL_GetError());
        return;
    }

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
        { // window=0, means is being created
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // window,index,flags
        if (renderer)
        { // if renderer is successfully created
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(renderer, 640, 480);

    std::string str = "example.png";
    char *path = MyPath::getImageDir(str);
    playerText = TextureManager::LoadTexture(path, renderer);
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
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
