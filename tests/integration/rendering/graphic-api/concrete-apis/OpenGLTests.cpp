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
#include <engine/subsystems/renderer/shaders/ShaderLoader.h>
#include "unit/engine/LoopHelper.h"
#include "integration/rendering/IHelloTriangleRenderTest.h"
class OpenGLTests : public IHelloTriangleRenderTest {
protected:
    
    SDL_Window *window{};
    
    SDL_GLContext glContext{};
    
    GLuint shaderProgram{};
    
    
    
    void destroyOpenGL(const std::string &message){
        // Cleanup
        GLESC::Logger::get().error(message);
        glDeleteProgram(shaderProgram);
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    void initializeOpengl(){
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
    void prepareShaders() override{
        shaderProgram = ShaderLoader::loadShader(vertexShaderSource, fragmentShaderSource);
        GLESC::Logger::get().success("Shader program created successfully");
    }
    
    GLuint VBO{};
    GLuint VAO{};
    
    void prepareBuffers() override{
        // Vertex Buffer Object (VBO)
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        
        // Vertex Array Object (VAO)
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        // Set vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                              (GLvoid *) 0);
        glEnableVertexAttribArray(0);
        
        // Unbind VAO
        glBindVertexArray(0);
    }
    
    void render() override{
        // Render
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                     backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use shader program
        glUseProgram(this->shaderProgram);
        
        // Set the color uniform
        GLint colorLocation = glGetUniformLocation(this->shaderProgram, "uColor");
        glUniform4f(colorLocation, triangleColor.r, triangleColor.g, triangleColor.b,
                    triangleColor.a);
        
        // Draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Swap window
        SDL_GL_SwapWindow(window);
    }
    
    void SetUp() override {
        initializeOpengl();
        prepareShaders();
        prepareBuffers();
        
        LOOP() {
            render();
        }
    }
    
    void destroyRender() override{
        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    
    void TearDown() override {
        destroyRender();
    }
};











TEST_F(OpenGLTests, test) {
    // Binding before reading
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Get the size of the buffer data
    GLint bufferSize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    size_t numElements = bufferSize / sizeof(float);
    
    // Read the buffer data
    std::vector<float> actualVertices(numElements);
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, actualVertices.data());
    
    // Check the vertex data
    ASSERT_EQ(actualVertices.size(), vertices.size());
    for (size_t i = 0; i < actualVertices.size(); ++i) {
        std::cout << "Vertex data " << i << ": " << actualVertices[i] << "\n";
        EXPECT_NEAR(actualVertices[i], vertices[i], dataEpsilon)
                            << "Vertex data mismatch at index " << i;
    }
    
    // Check the background color
    float pixel[3];
    glReadPixels(10, 10, 1, 1, GL_RGBA, GL_FLOAT, pixel);
    EXPECT_NEAR(pixel[0], backgroundColor.r, colorEpsilon);
    EXPECT_NEAR(pixel[1], backgroundColor.g, colorEpsilon);
    EXPECT_NEAR(pixel[2], backgroundColor.b, colorEpsilon);
    
    // Check the triangle color
    glReadPixels(400, 300, 1, 1, GL_RGBA, GL_FLOAT, pixel);
    EXPECT_NEAR(pixel[0], triangleColor.r, colorEpsilon);
    EXPECT_NEAR(pixel[1], triangleColor.g, colorEpsilon);
    EXPECT_NEAR(pixel[2], triangleColor.b, colorEpsilon);
}