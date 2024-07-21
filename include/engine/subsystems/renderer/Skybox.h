/**************************************************************************************************
 * @file   Skybox.h
 * @author Valentin Dumitru
 * @date   2024-04-28
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "RendererTypes.h"
#include "engine/core/low-level-renderer/shader/Shader.h"
#include "texture/Cubemap.h"

#define SKYBOX_PATH "images/skyboxes/default/"

namespace GLESC::Render {
    /**
     * @brief Class that represents a skybox.
     * @details Stores the skybox cubemap, and handles the textures and rendering of the skybox.
     */
    class Skybox {
    public:
        /**
         * @brief Sybox constructor. Is in charge of loading the cubemap, creating the textures, loading the buffers
         * and loading the shaders.
         */
        explicit Skybox(const std::string& folderName = "default", const std::string& extension = "png");

        /**
         * @brief Returns the average color of the skybox. It is cached so it is not recalculated every frame.
         * @return
         */
        [[nodiscard]] ColorRgb getAverageColor() const { return averageColor; }

        /**
         * @brief Calculates the average color of the skybox.
         * @details Takes a set of random pixles and calculates the average color between them.
         * For now it is not used.
         */
        void calculateAverageColor();
        /**
         * @brief Renders the skybox around the player given the view and projection.
         * @details A skybox is a cubemap that is always aroud the player and simulates infinity distance.
         * This is done by having the skybox follow the camera and having the depth component in the shader to
         * be maximum depth (1.0).
         * @param view
         * @param projection
         */
        void draw(const View& view, const Projection& projection) const ;

    private:
        ColorRgb averageColor;
        UInt skyboxVAOID;
        UInt skyboxVBOID;
        Shader skyboxShader;
        Cubemap skyboxCubemap;

        std::unique_ptr<VertexArray> skyboxVAO;
        std::unique_ptr<VertexBuffer> skyboxVBO;
        float skyboxVertices[108];
    }; // class Skybox
}
