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

    
    /*Instantiate the shader loader object.
    This object is in charge of doing all the shader work*/
    shaderManager=new ShaderManager();
    
    /**
     * Attributes that configure SDL with OpenGL
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
    /*This makes our buffer swap syncronized with the monitor's vertical refresh
    0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync */
    int status=SDL_GL_SetSwapInterval(1);
    if(status == -1){
        cout<< SDL_GetError() <<endl;
        SDL_GL_SetSwapInterval(0);
    }
    /**
     * SDL has several subsystems like SDL_INIT_AUDIO or SDL_INIT_VIDEO.
     * SDL_INIT_EVERYTHING is just a call to each one of them.
     * More info: https://wiki.libsdl.org/SDL_Init 
     */
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
    
    
    
    /**
     * We bind the created buffer to a specific type.
     * There can only be one buffer of each type.
     * Therefore any buffer calls we make to GL_ARRAY_BUFFER will configure the 
     * current bound buffer
     */
    shaderManager->LoadAndLinkAll();

    /* Vertice data of the triangle */
    float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* EBO for squares, not to repeat vertices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

    

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    /* Set the filter to the mipmaps in case of minifying or magnifying the textures */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    
    SDL_Surface* surf=TextureManager::LoadTexture("assets/sprites/wall.jpg");
    /**
     * @brief Generates the texture on the object bound
     * Params:
     * 1) The bound object
     * 2) The level of mipmap for which we want to generate the texture
     * 3) Which way we want to store the image, we only have rgb
     * 4 & 5) Width and height of the image
     * 6) Always 0, legacy
     * 7) The format of the source image, just RGB in this case
     * 8) How is the image pixels are stored as, bytes in this case
     * 9) The actual image data
     */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
    /* We generate the mipmap to the bound texture */
    glGenerateMipmap(GL_TEXTURE_2D);
    /* Clean the surfice */
    SDL_FreeSurface(surf);




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

    

    glBindTexture(GL_TEXTURE_2D, texture);



    shaderManager->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    window->SwapBuffers();
}

void Game::clean()
{
    
    SDL_DestroyRenderer(renderer);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderManager->getShaderProgramID());
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
