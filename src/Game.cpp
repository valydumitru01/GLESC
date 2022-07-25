#include "Game.h"
#include "MyPath.h"
#include "TextureManager.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int width, int height, bool fullscreen)
{

    
    
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

    SDL_GL_SetSwapInterval(1);

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
    /** Must create the window after initing SDL **/
    window = new Window("My Game");
    
    
    /** Must init **/
    window->init();
    
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
    
    
    
 
    /* We bind the created buffer to a specific type.
    There can only be one buffer of each type.
    Therefore any buffer calls we make to GL_ARRAY_BUFFER will configure the 
    current bound buffer */
    
    shaderLoader->LoadAndLinkAll();

    /* Vertices of the Rectangle */
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    }; 

    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };
    
    /* We generate the buffer
    The first parameter is the ammount of buffer objects we want to generate 
    The second is the reference to the object ID as uint, if we generate more tan one, we need to pass an array of uint */ 
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);  


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    /* Copies the previously defined vertices into the buffer's memory 
    We pass the buffer, the size of the vertices array, the vertices and 
    how we want the GPU to manage the vertices 
    More info here: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


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

}

void Game::render()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderLoader->getShaderProgramID());
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    window->SwapBuffers();
}

void Game::clean()
{
    
    SDL_DestroyRenderer(renderer);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderLoader->getShaderProgramID());
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
