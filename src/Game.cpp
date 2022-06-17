#include "Game.h"
#include "MyPath.h"
#include "TextureManager.h"
SDL_Texture* playerText;
SDL_Rect srcRectangle, destRectangle;
double positionX=0;
Game::Game(){

}

Game::~Game(){

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystem initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(window){//window=0, means is being created
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//window,index,flags
        if(renderer){//if renderer is successfully created
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;

    } else {
        isRunning = false;
    }

    std::string str = "example.png";
    char* path = MyPath::getImageDir(str);  
    playerText = TextureManager::LoadTexture(path,renderer);

}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;

    }
}

void Game::update(double deltaTime){
    cnt++;
    destRectangle.h = 64;
    destRectangle.w = 64;
    positionX+=deltaTime*100;
    destRectangle.x =std::trunc(positionX);

    std::cout<<destRectangle.x<<std::endl;
}

void Game::render(){
    SDL_RenderClear(renderer);
    //null, for the source rectangle will use the entire image
    //null, will draw the whole render frame
    SDL_RenderCopy(renderer, playerText, NULL, &destRectangle);
    //this is where we would add stuff to render
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
