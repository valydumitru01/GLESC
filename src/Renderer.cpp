#include "Renderer.h"

Renderer::Renderer(short height, short width)
{
    /*Instantiate the shader loader object.
    This object is in charge of doing all the shader work*/
    shaderManager = new ShaderManager();
    /*Instantiate the coordinate system that handles our space matrix*/
    coordSystem = new CoordinateSystem(height, width);
    GLuint err;

    /*Set all the GL attribures*/
    setGlAttributes();

    /*This makes our buffer swap syncronized with the monitor's vertical refresh
    0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive v-sync */
    if (SDL_GL_SetSwapInterval(1) == -1)
    {
        SDL_Log("Unable activate v-sync (swap interval): %s", SDL_GetError());
    }
    //Init GLEW
    glewExperimental = GL_TRUE;
    if ((err =glewInit())!=GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return;
    }
    std::cout << "Subsystem initialized..." << std::endl;

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

}
Renderer::~Renderer(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void Renderer::setGlAttributes()
{
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
}
void Renderer::createShaderAttributes()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
void Renderer::createBuffers()
{
    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Send data to buffers
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.data()), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.data()), indices.data(), GL_STATIC_DRAW);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Renderer::generateTexture(GLuint texture, const char* path)
{
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_Surface *surf = TextureManager::LoadTexture(path);
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
}

void Renderer::generateTextures()
{
    glGenTextures(1, &texture1);
    generateTexture(texture1,"assets/sprites/wall.jpg");

    glGenTextures(1, &texture2);
    generateTexture(texture2,"assets/sprites/awesomeface.png");
}

void Renderer::init()
{

    glEnable(GL_DEPTH_TEST);
    /**
     * We bind the created buffer to a specific type.
     * There can only be one buffer of each type.
     * Therefore any buffer calls we make to GL_ARRAY_BUFFER will configure the
     * current bound buffer
     */
    shaderManager->LoadAndLinkAll();

    vertices = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

    indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    /*Create VAO VBO and EBO*/ 
    createBuffers();

    createShaderAttributes();

    generateTextures();

    //We need to select the program we use so we can activate the textures inside the shaders
    shaderManager->useShaderProgram();
    //Set texture uniforms, needed to imply different layers of textures
    shaderManager->setInt("texture1", 0);
    shaderManager->setInt("texture2", 1);

    trans = glm::mat4(1.0f);
}

void Renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO);

    coordSystem->apply();

    shaderManager->setMat4("model", coordSystem->model);
    shaderManager->setMat4("view", coordSystem->view);
    shaderManager->setMat4("projection", coordSystem->projection);

    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // first container
    // ---------------
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)(SDL_GetTicks() * 0.001), glm::vec3(0.0f, 0.0f, 1.0f));
    float scaleAmount = static_cast<float>(sin(SDL_GetTicks() * 0.001));

    transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
    // get their uniform location and set matrix (using glm::value_ptr)
    unsigned int transformLoc = glGetUniformLocation(shaderManager->getShaderProgramID(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // with the uniform matrix set, draw the first container
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // second transformation
    // ---------------------
    transform = glm::mat4(1.0f); // reset it to identity matrix
    transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
    scaleAmount = static_cast<float>(sin(SDL_GetTicks() * 0.001));

    transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform)); // this time take the matrix value array's first element as its memory pointer value

    // now with the uniform matrix being replaced with new transformations, draw it again.
    glDrawArrays(GL_TRIANGLES, 0, 36);
}