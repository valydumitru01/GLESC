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
#include <engine/core/low-level-renderer/shader/ShaderLoader.h>
#include "LoopHelper.h"
#include "integration/rendering/IBaseRenderTest.h"

class OpenGLTests : public IBaseRenderTest {
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
        GLESC::Logger::get().error(message);
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
    
    void prepareShaders() override {
        shaderProgram = ShaderLoader::loadShader(vertexShaderSource, fragmentShaderSource);
        GLESC::Logger::get().success("Shader program created successfully");
    }
    
    GLuint VBO{};
    GLuint EBO{};
    GLuint VAO{};
    
    void prepareBuffers() override {
        // Vertex Array Object (VAO)
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        Logger::get().success("VAO created!");
        
        // Vertex Buffer Object (VBO)
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                     GL_STATIC_DRAW);
        Logger::get().success("VBO created!");
        
        // Set vertex attributes
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *) 0);
        glEnableVertexAttribArray(0);
        Logger::get().success("Vertex attributes set!");
        
        // Vertex Element Buffer Object (EBO)
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(),
                     GL_STATIC_DRAW);
        Logger::get().success("EBO created!");
        
        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // Unbind VAO (to prevent accidental modification)
        glBindVertexArray(0);
    }
    
    void render() override {
        // Render
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                     backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
        Logger::get().success("Clear values set!");
        
        // Use shader program
        glUseProgram(this->shaderProgram);
        
        // Set the color uniform
        GLint colorLocation = glGetUniformLocation(this->shaderProgram, "uColor");
        glUniform4f(colorLocation, expectedTriangleColor.r, expectedTriangleColor.g, expectedTriangleColor.b,
                    expectedTriangleColor.a);
        Logger::get().success("Color uniform set!");
        
        
        // Draw the triangle
        glBindVertexArray(VAO);
        Logger::get().success("VAO bound!");
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        Logger::get().success("Triangle drawn!");
        glBindVertexArray(0);
        
        // Swap window
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
        
        LOOP() {
            render();
        }
        Logger::get().success("Rendered!");
    }
    
    void destroyRender() override {
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
    Logger::get().success("Test started!");
    // Binding before reading
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    Logger::get().success("Reading buffer data!");
    // Get the size of the buffer data
    GLint bufferSize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    Logger::get().success("Read buffer size: " + std::to_string(bufferSize));
    size_t numElements = bufferSize / sizeof(float);
    
    
    // Read the buffer data
    std::vector<float> actualVertices(numElements);
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, actualVertices.data());
    Logger::get().success("Buffer data read! Data: ");
    for (auto &actualVertex : actualVertices) {
        Logger::get().success(std::to_string(actualVertex));
    }
    
    // Check the vertex data
    ASSERT_EQ(actualVertices.size(), vertices.size());
    for (size_t i = 0; i < actualVertices.size(); ++i) {
        std::cout << "Vertex data " << i << ": " << actualVertices[i] << "\n";
        EXPECT_NEAR(actualVertices[i], vertices[i], dataEpsilon)
                            << "Vertex data mismatch at index " << i;
    }
    
    // Check the background color
    GAPI::RGBColorNormalized pixel{};
    Logger::get().success("Reading pixel color!");
    glReadPixels(10, 10, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
    Logger::get().success("Pixel color read! Pixel: " + std::to_string(pixel.r) + " " +
                          std::to_string(pixel.g) + " " + std::to_string(pixel.b));
    EXPECT_NEAR(pixel.r, backgroundColor.r, colorEpsilon);
    EXPECT_NEAR(pixel.g, backgroundColor.g, colorEpsilon);
    EXPECT_NEAR(pixel.b, backgroundColor.b, colorEpsilon);
    Logger::get().success("Pixel color checked!");
    
    // Check the triangle color
    Logger::get().success("Reading triangle color!");
    glReadPixels(400, 300, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
    Logger::get().success("Triangle color read! Pixel: " + std::to_string(pixel.r) + " " +
                          std::to_string(pixel.g) + " " + std::to_string(pixel.b));
    EXPECT_NEAR(pixel.r, expectedTriangleColor.r, colorEpsilon);
    EXPECT_NEAR(pixel.g, expectedTriangleColor.g, colorEpsilon);
    EXPECT_NEAR(pixel.b, expectedTriangleColor.b, colorEpsilon);
    Logger::get().success("Triangle color checked!");
}