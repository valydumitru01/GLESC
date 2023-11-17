/**************************************************************************************************
 * @file   RenderingTest.cpp
 * @author Valentin Dumitru
 * @date   2023-11-09
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <engine/core/low-level-renderer/graphic-api/Gapi.h>
#include <engine/subsystems/renderer/shaders/ShaderLoader.h>
#include <engine/core/window/WindowManager.h>
#include "../../../unit/engine/LoopHelper.h"
#include "../../../unit/engine/core/math/MathTestHelper.h"

class GAPIHelloTriangleTests : public ::testing::Test {
protected:
    
    void SetUp() override {
        render();
        prepareShaders();
    }
    
    void TearDown() override {
        destroyGAPI("Test finished!");
        
        // Test passed
        ASSERT_TRUE(true);
    }
    
    GAPIuint VBO;
    GAPIuint VAO;
    float backgroundColor[4] = {0.2f, 0.3f, 0.3f, 1.0f};
    float triangleColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    
    GLESC::WindowManager windowManager{};
    
    GAPIuint shaderProgram{};
private:
    void destroyGAPI(const std::string &message) {
        // Cleanup
        gapi.deleteVertexArray(VAO);
        GLESC::Logger::get().success("VAO deleted!");
        gapi.deleteBuffer(VBO);
        GLESC::Logger::get().success("VBO deleted!");
        
        // Cleanup
        GLESC::Logger::get().error(message);
        gapi.destroyShaderProgram(shaderProgram);
        gapi.deleteContext();
        windowManager.destroyWindow();
        SDL_Quit();
    }
    
    void render() {
        // Triangle vertices
        GLfloat vertices[] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};
        
        // Vertex Buffer Object (VBO)
        gapi.genBuffers(1, VBO);
        GLESC::Logger::get().success("VBO created!");
        
        gapi.bindBuffer(GAPIValues::BufferTypeVertex, VBO);
        GLESC::Logger::get().success("VBO bound!");
        
        gapi.setBufferData(vertices, sizeof(vertices), GAPIValues::BufferTypeVertex,
                           GAPIValues::BufferUsageStaticDraw);
        GLESC::Logger::get().success("VBO data set!");
        
        // Vertex Array Object (VAO)
        gapi.genVertexArray(VAO);
        GLESC::Logger::get().success("VAO created!");
        
        gapi.bindVertexArray(VAO);
        GLESC::Logger::get().success("VAO bound!");
        
        // Set vertex attributes
        gapi.vertexAttribPointer(0, 3, GAPITypes::Float, GAPI_FALSE, 3 * sizeof(float), 0);
        GLESC::Logger::get().success("Vertex attributes set!");
        gapi.enableVertexAttribArray(0);
        GLESC::Logger::get().success("Vertex attributes enabled!");
        
        // Unbind VAO
        gapi.unbindVertexArray();
        GLESC::Logger::get().success("VAO unbound!");
        
        
        // Render
        gapi.clearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2],
                        backgroundColor[3]);
        GLESC::Logger::get().success("Clear color set!");
        gapi.clear({GAPIValues::ClearBitsColor, GAPIValues::ClearBitsDepth,
                    GAPIValues::ClearBitsStencil});
        GLESC::Logger::get().success("Clear values set!");
        
        // Draw the triangle
        gapi.bindVertexArray(VAO);
        GLESC::Logger::get().success("VAO bound!");
        gapi.draw(GAPIValues::PrimitiveTypeTriangles, 0, 3);
        GLESC::Logger::get().success("Triangle drawn!");
        gapi.unbindVertexArray();
        GLESC::Logger::get().success("VAO unbound!");
        gapi.setUniform(shaderProgram, "uColor")->u4F(triangleColor);
        
        // Swap window
        gapi.swapBuffers(windowManager.getWindow());
        GLESC::Logger::get().success("Window swapped!");
    }
    
    void prepareShaders() {
        // Shader sources
        const char *vertexShaderSource = R"glsl(
        /* version automatically set */
        layout (location = 0) in vec3 position;
        void main() {
            gl_Position = vec4(position, 1.0);
        }
        )glsl";
        const char *fragmentShaderSource = R"glsl(
        /* version automatically set */
        out vec4 color;
        uniform vec4 uColor; // Uniform for color
        void main() {
            color = uColor;
        }
        )glsl";
        shaderProgram = ShaderLoader::loadShader(vertexShaderSource, fragmentShaderSource);
        GLESC::Logger::get().success("Shader program created successfully");
    }
};


TEST_F(GAPIHelloTriangleTests, test) {
    
    
    
    
    // Check if the background color is correct
    auto [r, g, b] = gapi.readPixelColorNormalized(0, 0);
    EXPECT_EQ_CUSTOM(r, backgroundColor[0]);
    EXPECT_EQ_CUSTOM(g, backgroundColor[1]);
    EXPECT_EQ_CUSTOM(b, backgroundColor[2]);
    
    // Check if the triangle is drawn correctly
    // The shader program is set to draw a triangle with the color red
    auto [r1, g1, b1] = gapi.readPixelColorNormalized(400, 300);
    EXPECT_EQ_CUSTOM(r1, 1.0f);
    EXPECT_EQ_CUSTOM(g1, 0.0f);
    EXPECT_EQ_CUSTOM(b1, 0.0f);
    
    
}


