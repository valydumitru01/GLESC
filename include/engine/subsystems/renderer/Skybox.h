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

#include "RendererTypes.h"
#include "engine/core/low-level-renderer/shader/Shader.h"
#include "texture/Cubemap.h"

#define SKYBOX_PATH "images/skyboxes/default/"

namespace GLESC::Render {
    class Skybox {
    public:
        /**
         * @brief Default constructor.
         */
        Skybox();

        [[nodiscard]] ColorRgb getAverageColor() const {
            return averageColor;
        }

        void calculateAverageColor();
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
