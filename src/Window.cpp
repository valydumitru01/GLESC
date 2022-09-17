#include "Window.h"
Window::Window(const char* title){
    //Init the window dimensions
    height=800;
    width=1200;
    windowName= (char*)"Game";
    int flags = setFlags();
    windowName=title;
    /* Create windows with SDL */
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    /* Returns null on error*/
    if (window == NULL)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return;
    }
    printf("%s","Window created!");
}

void Window::init(){

    /* Set the minimum window size */
    SDL_SetWindowMinimumSize(window,WINDOW_MIN_WIDTH,WINDOW_MIN_HEIGHT);
    /* Tells OpenGL which size is the viewport where things are displayed 
    Paramenters: Two points (x,y) of the left bottom corner and of the right upper corner*/
    glViewport(0, 0, width, height);
    /* OpenGL context initialization over the SDL window, needed for
    using OpenGL functions*/
    context = SDL_GL_CreateContext(window);
    /* Returns null on error */
    if (context == NULL)
    {
        SDL_Log("Unable to create context: %s", SDL_GetError());
        return;
    }
}
void Window::setSize(GLsizei _width, GLsizei _height){
    height=_height;
    width=_width;
    glViewport(0,0,width,height);
}
int Window::setFlags(){
    /*Flags that are needed to be passed to the window to configure it.
    To add more flags we need to use the binary OR ( | )
    More info: https://wiki.libsdl.org/SDL_WindowFlags*/
    int flags = 0;
    /* Flag for allowing SDL window work with OpenGL */
    flags |= SDL_WINDOW_OPENGL;
    /* Flaf for allowing window resize */
    flags |= SDL_WINDOW_RESIZABLE;

    return flags;
}
void Window::setFullscreen(SDL_bool isFullScreen){

}
SDL_Window* Window::getWindow(){
    return window;
}
Window::~Window(){
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
}
void Window::SwapBuffers(){
    SDL_GL_SwapWindow( window );
}