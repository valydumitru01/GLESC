/**************************************************************************************************
 * @file   OpenGLTests.cpp
 * @author Valentin Dumitru
 * @date   2023-11-09
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <engine/Config.h>
#include <engine/core/logger/Logger.h>
#include "../../../../unit/engine/LoopHelper.h"
class OpenGLTests : public ::testing::Test {
protected:
    
    SDL_Window *window{};
    
    SDL_GLContext glContext{};
    
    GLuint shaderProgram{};
    
    static GLuint compileShader(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        
        // Check for shader compile errors
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
        }
        
        return shader;
    }
    
    void destroyOpenGL(const std::string &message){
        // Cleanup
        GLESC::Logger::get().error(message);
        glDeleteProgram(shaderProgram);
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    void initializeTest(){
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
            ASSERT_TRUE(false);
        }
        
        // Set OpenGL attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        // Create window
        window =SDL_CreateWindow("GAPI Test", GLESC_WINDOW_X, GLESC_WINDOW_Y, GLESC_WINDOW_WIDTH,
                                 GLESC_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
        if (!window) {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            SDL_Quit();
            ASSERT_TRUE(false);
        }
        
        // Create OpenGL context
        glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            SDL_Log("Failed to create OpenGL context: %s", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            ASSERT_TRUE(false);
        }
        
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK) {
            destroyOpenGL("Unable to initialize GLEW: " +
                          std::string((char *) glewGetErrorString(glewError)));
            ASSERT_TRUE(false);
        }
    }
    // Function to link shader program and check for errors
    static void linkProgram(GLuint program) {
        glLinkProgram(program);
        
        // Check for linking errors
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            throw std::runtime_error("Shader link failed: " + std::string(infoLog));
        }
    }
    void prepareShaders(){
        // Shader sources
        const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 position;
        void main() {
            gl_Position = vec4(position, 1.0);
        }
        )glsl";
            
            const char* fragmentShaderSource = R"glsl(
        #version 330 core
        out vec4 color;
        uniform vec4 uColor; // Uniform for color
        void main() {
            color = uColor;
        }
        )glsl";
        // Compile shaders
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        
        // Create shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        linkProgram(shaderProgram);
        
        // Delete shaders after linking
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    void SetUp() override {
        initializeTest();
        prepareShaders();
    }
    
    void TearDown() override {
        destroyOpenGL("Test finished!");
    }
};











TEST_F(OpenGLTests, test) {
    // Triangle vertices
    GLfloat vertices[] = {
            0.0f,  0.5f,  0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
    
    // Vertex Buffer Object (VBO)
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Vertex Array Object (VAO)
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    
    // Unbind VAO
    glBindVertexArray(0);
    
    // Main loop
    LOOP()
    {
        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use shader program
        glUseProgram(this->shaderProgram);
        
        // Set the color uniform
        GLint colorLocation = glGetUniformLocation(this->shaderProgram, "uColor");
        glUniform4f(colorLocation, 1.0f, 0.0f, 0.0f, 1.0f); // Red color
        
        // Draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Swap window
        SDL_GL_SwapWindow(window);
    }
    
    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
