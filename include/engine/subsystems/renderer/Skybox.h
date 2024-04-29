/**************************************************************************************************
 * @file   Skybox.h
 * @author Valentin Dumitru
 * @date   2024-04-28
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <string>

#include "RendererTypes.h"
#include "engine/core/low-level-renderer/shader/Shader.h"
#include "texture/Cubemap.h"

#define SKYBOX_PATH "images/skyboxes/default/"

class Skybox {
public:
    /**
     * @brief Default constructor.
     */
    Skybox() : skyboxCubemap(Cubemap(std::array<std::string, 6>{
                   SKYBOX_PATH + std::string("right.png"),
                   SKYBOX_PATH + std::string("left.png"),
                   SKYBOX_PATH + std::string("top.png"),
                   SKYBOX_PATH + std::string("bottom.png"),
                   SKYBOX_PATH + std::string("front.png"),
                   SKYBOX_PATH + std::string("back.png")
               })), skyboxShader("SkyboxShader.glsl"){
        size_t skyboxVerticesCount = sizeof(skyboxVertices) / sizeof(float);
        size_t skyboxVerticesSize = sizeof(float);

        skyboxVAO = std::make_unique<VertexArray>();
        skyboxVAO->bind();
        skyboxVBO = std::make_unique<VertexBuffer>(
            &skyboxVertices,
            skyboxVerticesCount,
            skyboxVerticesSize,
            Enums::BufferUsages::StaticDraw);

        VertexBufferLayout skyboxLayout;
        skyboxLayout.push(Enums::Types::Vec3F);
        skyboxVAO->addBuffer(*skyboxVBO.get(), skyboxLayout);

    }


    void draw(const GLESC::Render::View& view, const GLESC::Render::Projection& projection) {
        Mat3F resizedView(view);
        GLESC::Render::VP viewTranslationless(resizedView);

        // change depth function so depth test passes when values are equal to depth buffer's content
        getGAPI().setDepthFunction(Enums::DepthFuncs::LessEqual);
        skyboxShader.bind();
        skyboxShader.setUniform("uVPTranslationless", viewTranslationless * projection);
        skyboxVAO->bind();
        skyboxCubemap.bind();
        getGAPI().drawTriangles(0, 36);
        getGAPI().setDepthFunction(Enums::DepthFuncs::Less);


    }

private:
    UInt skyboxVAOID;
    UInt skyboxVBOID;
    Shader skyboxShader;
    Cubemap skyboxCubemap;

    std::unique_ptr<VertexArray> skyboxVAO;
    std::unique_ptr<VertexBuffer> skyboxVBO;
    float skyboxVertices[108] = {
        // positions
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    };
}; // class Skybox
