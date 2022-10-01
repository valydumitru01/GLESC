#include "Renderer.h"

Renderer::Renderer(short height, short width, ShaderManager* ShaderManager)
{

    /*Instantiate the shader loader object.
    This object is in charge of doing all the shader work*/
    this->shaderManager = ShaderManager;
    /*Instantiate the coordinate system that handles our space matrix*/
    coordSystem = new CoordinateSystem(height, width);

    trans = glm::mat4(1.0f);

}
Renderer::~Renderer(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


void Renderer::createBuffers()
{

    float vertices[] = {
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

    int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glCheckError();
    glGenBuffers(1, &VBO);
    glCheckError();
    glGenBuffers(1, &EBO);
    glCheckError();

    // Bind buffers
    glBindVertexArray(VAO);
    glCheckError();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glCheckError();

    // Send data to buffers
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glCheckError();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glCheckError();

}
void Renderer::createShaderAttributes()
{
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glCheckError();
    glEnableVertexAttribArray(0);
    glCheckError();

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glCheckError();
    glEnableVertexAttribArray(1);
    glCheckError();

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glCheckError();
    glEnableVertexAttribArray(2);
    glCheckError();
}
void Renderer::generateTexture(GLuint texture, const char* path)
{
    //all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    glBindTexture(GL_TEXTURE_2D, texture);
    glCheckError();
    //-----------set the texture wrapping parameters------------

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCheckError();

    //----------------------------------------------------------


    //--------------set texture filtering parameters------------
    /**
     * @brief Magnification and minification filtering
     * This can be GL_LINEAR or GL_NEAREST
     * or if we filter with mipmapping
     * GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST
     * GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();    

    //----------------------------------------------------------


    SDL_Surface *surf = TextureManager::LoadTexture(path);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
    glCheckError();
    /* We generate the mipmap to the bound texture */
    glGenerateMipmap(GL_TEXTURE_2D);
    glCheckError();
    /* Clean the surfice */
    SDL_FreeSurface(surf);
}

void Renderer::generateTextures()
{
    glGenTextures(1, &texture1);
    glCheckError();
    generateTexture(texture1,"assets/sprites/wall.jpg");

    glGenTextures(1, &texture2);
    glCheckError();
    generateTexture(texture2,"assets/sprites/awesomeface.png");

    //We need to select the program we use so we can activate the textures inside the shaders
    shaderManager->useShaderProgram();
    //Set texture uniforms, needed to imply different layers of textures
    shaderManager->setInt("texture1", 0);
    shaderManager->setInt("texture2", 1);

}

void Renderer::init()
{
    /**
     * @brief Enable depth test
     * Fragments (pixels) will display in front
     * of each other according to their actual
     * position.
     * 
     */
    glEnable(GL_DEPTH_TEST);

    shaderManager->LoadAndLinkAll();

    
    /*Create VAO VBO and EBO*/ 
    createBuffers();

    createShaderAttributes();

    generateTextures();

}

void Renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, texture1);
    glCheckError();
    glActiveTexture(GL_TEXTURE1);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, texture2);
    glCheckError();
    glBindVertexArray(VAO);
    glCheckError();

    shaderManager->useShaderProgram();
    
    coordSystem->apply();

    shaderManager->setMat4("model", coordSystem->model);

    shaderManager->setMat4("projection", coordSystem->projection);

    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // first container
    // ---------------
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)(SDL_GetTicks() * 0.001), glm::vec3(0.0f, 0.0f, 1.0f));
    float scaleAmount = 1.0f+0.5f*static_cast<float>(sin(SDL_GetTicks() * 0.001));

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