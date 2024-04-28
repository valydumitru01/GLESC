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

#include "LoopHelper.cpp"
#include "engine/core/low-level-renderer/buffers/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "../../../../include/engine/subsystems/renderer/texture/Texture.h"
#include "engine/core/window/WindowManager.h"
#include "engine/core/low-level-renderer/shader/Shader.h"
#include "integration/rendering/RenderingTestHelper.h"

class TextureAbstractionTests : public ::testing::Test{
protected:
    GLESC::WindowManager windowManager;
    // These are pointers because we don't want to call the constructor
    VertexArray* vao;
    VertexBuffer* vbo;
    IndexBuffer* ibo;
    Shader* shader;
    GAPITexture* texture;
    std::vector<std::string> texturePaths{
            "assets/textures/Debug1.png",
            "assets/textures/Debug2.png",
            "assets/textures/Debug3.png",
            "assets/textures/Debug4.png"
    };
    
    
    RGBAColorNormalized backgroundColor = {0.2f, 0.3f, 0.3f, 1.0f};
    
    TextureAbstractionTests() {
    }
    
    void prepareShaders() {
        
        shader = new Shader(vertexShaderSourceTexture, fragmentShaderSourceTexture);
    }
    
    void prepareBuffers() {

        
        vao = new VertexArray();
        vao->bind();
        vbo = new VertexBuffer(positionAndUVVertices.data(), positionAndUVVertices.size(),
            positionAndUVVertices.size() * sizeof(float) * 2, Enums::BufferUsages::StaticDraw);
        ibo = new IndexBuffer(indices);
        
        VertexBufferLayout layout;
        layout.push(Enums::Types::Vec2F); // Position
        layout.push(Enums::Types::Vec2F); // Texture coordinates
        
        vao->addBuffer(*vbo, layout);
        

        
    }
    
    void render()  {
        Logger::get().info("====================== Rendering ======================");
        getGAPI().clearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                        backgroundColor.a);
        getGAPI().clear({Enums::ClearBits::Color, Enums::ClearBits::Depth,
                    Enums::ClearBits::Stencil});
        vao->bind();
        shader->bind();
        

        getGAPI().drawTrianglesIndexed(indices.size());
        
        getGAPI().swapBuffers(windowManager.getWindow());
    }
    
    void drawAndCheckTexture(std::string texturePath){
        texture= new GAPITexture(texturePath);
        
        shader->bind();
        texture->bind(GAPITexture::Slot::Slot0); // Bind the texture to slot 0
        // The texture is bound to slot 0, so we need to set the uniform to 0
        shader->setUniform("uTexture",0);
        render();
        // checkTextureData(texture->getTextureID(), texture->getPixelsInBytes());
        Logger::get().info("============Checking texture data=============");
        auto actualData = getGAPI().getTextureData(texture->getTextureID());
        EXPECT_EQ(texture->getPixelsInBytes().size(), actualData.size());
        for (size_t i = 0; i < texture->getPixelsInBytes().size(); ++i) {
            EXPECT_EQ(texture->getPixelsInBytes()[i], actualData[i])
                                << "Texture data mismatch at index " << i;
        }
        Logger ::get().success("Texture data is correct");
    }
    
    void SetUp() override {
        Logger::get().info("================= Preparing shaders =================");
        prepareShaders();
        Logger::get().info("================= Preparing buffers =================");
        prepareBuffers();
    }
    
    void TearDown() override {
        ibo->destroy();
        vbo->destroy();
        vao->destroy();
        
        delete ibo;
        delete vbo;
        delete vao;
        
        delete shader;
        windowManager.destroyWindow();
    }
    
    
};

TEST_F(TextureAbstractionTests, test) {
    Logger::get().info("====================== Testing ======================");
    for (auto &texturePath : texturePaths) {
        drawAndCheckTexture(texturePath);
        delete texture;
    }
    checkBackgroundColor();
    
    checkIndices(ibo->getBufferID(), indices);
    checkVertices(vbo->getBufferID(),positionAndUVVertices);
}

