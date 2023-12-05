/**************************************************************************************************
 * @file   TextureAbstractionTests.cpp
 * @author Valentin Dumitru
 * @date   2023-11-09
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/


#include <SDL2/SDL.h>
#include <gtest/gtest.h>
#include <engine/core/low-level-renderer/texture/Texture.h>

#include "LoopHelper.h"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/shaders/Shader.h"
#include "integration/rendering/GAPIBaseRenderTest.h"
struct TextureTestParams {
    std::string texturePath;
};
class TextureAbstractionTests : public ::testing::TestWithParam<TextureTestParams>{
protected:
    GLESC::WindowManager windowManager;
    // These are pointers because we don't want to call the constructor
    GLESC::VertexArray* vao;
    GLESC::VertexBuffer* vbo;
    GLESC::IndexBuffer* ibo;
    GLESC::Shader* shader;
    GLESC::Texture* texture1;
    GLESC::Texture* texture2;
    GLESC::Texture* texture3;
    GLESC::Texture* texture4;
    std::vector<GAPI::Float> vertices = {
            -0.5f, -0.5f,  0.0f,  0.0f, // bottom left
            0.5f, -0.5f,  1.0f,  0.0f,  // bottom right
            0.5f,  0.5f,  1.0f,  1.0f,  // top right
            -0.5f,  0.5f,  0.0f,  1.0f  // top left
    };
    std::vector<GAPI::UInt> indices = {
            0, 1, 2,
            2, 3, 0
    };
    std::string  vertexShaderSource = R"glsl(
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec2 uv;

        out vec2 v_UV;


        void main() {
            gl_Position = vec4(position, 1.0);
            v_UV = uv;
        }
        )glsl";
    
    std::string  fragmentShaderSource = R"glsl(
        in vec2 v_UV;
        uniform sampler2D uTexture; // Uniform for texture

        layout (location = 0) out vec4 color;

        void main() {
            vec4 texColor = texture(uTexture, v_UV);
            color = texColor;
        }
        
        )glsl";
    
    GAPI::RGBColorNormalized backgroundColor = {0.2f, 0.3f, 0.3f, 1.0f};
    
    TextureAbstractionTests() {
    }
    
    void prepareShaders() {
        
        shader = new GLESC::Shader(vertexShaderSource, fragmentShaderSource);
    }
    
    void prepareBuffers() {

        
        vao = new GLESC::VertexArray();
        vao->bind();
        vbo = new GLESC::VertexBuffer(vertices);
        ibo = new GLESC::IndexBuffer(indices);
        
        GLESC::VertexBufferLayout layout;
        layout.push(GAPI::Types::Vec2F); // Position
        layout.push(GAPI::Types::Vec2F); // Texture coordinates
        
        vao->addBuffer(*vbo, layout);
        

        
    }
    
    void destroyRender() {
        ibo->destroy();
        vbo->destroy();
        vao->destroy();
        
        delete ibo;
        delete vbo;
        delete vao;
        
        delete shader;
        windowManager.destroyWindow();
    }
    
    void render()  {
        Logger::get().info("====================== Rendering ======================");
        gapi.clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                        backgroundColor.a);
        gapi.clear({GAPI::ClearBits::Color, GAPI::ClearBits::Depth,
                    GAPI::ClearBits::Stencil});
        vao->bind();
        shader->bind();
        

        gapi.drawTrianglesIndexed(indices.size());
        
        gapi.swapBuffers(windowManager.getWindow());
        gapi.swapBuffers(windowManager.getWindow());
    }
    
    void SetUp() override {
        Logger::get().info("================= Preparing shaders =================");
        prepareShaders();
        Logger::get().info("================= Preparing buffers =================");
        prepareBuffers();
    }
    
    void TearDown() override {
    }

private:
};

TEST_P(TextureAbstractionTests, test) {
    Logger::get().info("====================== Testing ======================");
    checkBackgroundColor();
    
    auto params = GetParam(); // Get the current test parameters
    
    texture1= new GLESC::Texture(params.texturePath);
    GAPI::UInt textureWidth = texture1->getWidth();
    GAPI::UInt textureHeight = texture1->getHeight();
    
    // Calculating the index for the center texel
    GAPI::UInt centerX = textureWidth / 2;
    GAPI::UInt centerY = textureHeight / 2;
    
    // Accessing the color components of the center texel
    expectedTriangleColor = texture1->getPixel(centerX, centerY).getColorNormalized();
    shader->bind();
    texture1->bind(0); // Bind the texture to slot 0
    // The texture is bound to slot 0, so we need to set the uniform to 0
    shader->setUniform("uTexture").u1I(0);
    render();
    checkTriangleColor();
    
    
    checkBufferData<GAPI::BufferTypes::Vertex>(vbo->getBufferID());
    checkBufferData<GAPI::BufferTypes::Index>(ibo->getBufferID());
}

INSTANTIATE_TEST_SUITE_P(
        TextureTestVariants,
        TextureAbstractionTests,
        ::testing::Values(
                TextureTestParams{"assets/textures/Debug1.png"},
                TextureTestParams{"assets/textures/Debug2.png"},
                TextureTestParams{"assets/textures/Debug3.png"},
                TextureTestParams{"assets/textures/Debug4.png"}
                // Add other test cases as needed
        )
);