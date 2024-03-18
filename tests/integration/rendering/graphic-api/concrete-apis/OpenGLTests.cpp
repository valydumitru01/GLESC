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

#include "integration/rendering/RenderingTestHelper.h"
#include <engine/Config.h>
#include <engine/core/logger/Logger.h>
#include <engine/core/low-level-renderer/shader/ShaderLoader.h>

class OpenGLTests : public ::testing::Test {
protected:
    
    SDL_Window *window{};
    
    SDL_GLContext glContext{};
    
    GLuint shaderProgram{};
    
    
    void destroyOpenGL(const std::string &message) {
        // Cleanup
        glDeleteProgram(shaderProgram);
        Logger::get().success("Shader program deleted!");
        SDL_GL_DeleteContext(glContext);
        Logger::get().success("OpenGL context deleted!");
        SDL_DestroyWindow(window);
        Logger::get().success("Window deleted!");
        SDL_Quit();
        Logger::get().success("SDL quit!");
        Logger::get().error(message);
    }
    
    void initializeOpengl() {
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
        window = SDL_CreateWindow("GAPI Test", GLESC_WINDOW_X, GLESC_WINDOW_Y, GLESC_WINDOW_WIDTH,
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
    
    void prepareShaders() {
        shaderProgram =
                ShaderLoader::loadShader(vertexShaderSourceColor, fragmentShaderSourceColor);
        Logger::get().success("Shader program created successfully");
    }
    
    GLuint VBO{};
    GLuint IBO{};
    GLuint VAO{};
    
    void prepareBuffers() {
        // Vertex Array Object (VAO)
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        Logger::get().success("VAO created!");
        
        // Vertex Buffer Object (VBO)
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, positionOnlyVertices.size() * sizeof(float),
                     positionOnlyVertices.data(),
                     GL_STATIC_DRAW);
        Logger::get().success("VBO created!");
        
        // Set vertex attributes
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *) 0);
        glEnableVertexAttribArray(0);
        Logger::get().success("Vertex attributes set!");
        
        // Vertex Element Buffer Object (EBO)
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(),
                     GL_STATIC_DRAW);
        Logger::get().success("EBO created!");
        
        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Unbind VAO (to prevent accidental modification)
        glBindVertexArray(0);
    }
    
    void render() {
        // Render
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                     backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
        Logger::get().success("Clear values set!");
        
        // Use shader program
        glUseProgram(this->shaderProgram);
        
        // Set the color uniform
        GLint colorLocation = glGetUniformLocation(this->shaderProgram, "uColor");
        glUniform4f(colorLocation, expectedFigureColor.r, expectedFigureColor.g,
                    expectedFigureColor.b,
                    expectedFigureColor.a);
        Logger::get().success("Color uniform set!");
        
        
        // Draw the triangle
        glBindVertexArray(VAO);
        Logger::get().success("VAO bound!");
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        Logger::get().success("Triangle drawn!");
        glBindVertexArray(0);
        
        // Swap window
        SDL_GL_SwapWindow(window);
        SDL_GL_SwapWindow(window);
        Logger::get().success("Window swapped!");
        
    }
    
    void SetUp() override {
        initializeOpengl();
        Logger::get().success("OpenGL initialized!");
        prepareShaders();
        Logger::get().success("Shaders prepared!");
        prepareBuffers();
        Logger::get().success("Buffers prepared!");
        
        render();
        Logger::get().success("Rendered!");
    }
    
    void destroyRender() {
        // Cleanup
        Logger::get().success("Destroying render!");
        glDeleteBuffers(1, &VBO);
        Logger::get().success("VBO deleted!");
        glDeleteVertexArrays(1, &VAO);
        Logger::get().success("VAO deleted!");
        destroyOpenGL("OpenGL destroyed!");
    }
    
    void TearDown() override {
        destroyRender();
    }
};


TEST_F(OpenGLTests, test) {
    checkBackgroundColor();
    checkCenterColor(expectedFigureColor);
    checkIndices(IBO, indices);
    checkVertices(VBO, positionOnlyVertices);
}