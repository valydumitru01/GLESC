#include "Game.h"
#include "MyPath.h"

SDL_Texture* playerText;
SDL_Rect srcRectangle, destRectangle;

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

        renderer = SDL_CreateRenderer(window, -1, 0);//window,index,flags
        if(renderer){//if renderer is successfully created
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;

    } else {
        isRunning = false;
    }

    std::string str = "example.png";
    std::string img_dir=MyPath::getImageDir(str);
    std::cout << img_dir << std::endl;
    char* path = MyPath::getCharFromStdString(img_dir);
    
    SDL_Surface* tmpSurface = IMG_Load(path);
    std::cout << path << std::endl;
    if (tmpSurface == nullptr){
        std::cout << path << std::endl;
        //std::cout << "Image null" << std::endl;
        printf(SDL_GetError());
    }
    playerText = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

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

void Game::update(){
    cnt++;
    destRectangle.h = 64;
    destRectangle.w = 64;
    destRectangle.x = cnt/2;
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
