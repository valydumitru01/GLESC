/**************************************************************************************************
 * @file   MeshRenderingTest.cpp
 * @author Valentin Dumitru
 * @date   11/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include <gtest/gtest.h>
#include <SDL2/SDL.h>

#include "LoopHelper.cpp"
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"
#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/shader/ShaderLoader.h"
#include "engine/core/window/WindowManager.h"
#include <integration/rendering/RenderingTestHelper.h>

#include "engine/subsystems/renderer/Renderer.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"


class MeshRenderingTest : public ::testing::Test {
protected:
    GLESC::WindowManager windowManager;
    GLESC::Renderer renderer;

    GLESC::Material material;
    GLESC::ColorMesh mesh = GLESC::MeshFactory::cube({12, 12, 12, 12});
    GLESC::Transform transform{{0, 0, 0}, {0, 0, 0}, {1, 1, 1}};

    MeshRenderingTest() : renderer(windowManager) {
        renderer.setData(material, mesh, transform);
        Vec3D cameraPos = {0, 0, 0};
        Vec3D cameraRotation = {0, 0, 0};
        Mat4D view;
        view.makeViewMatrix(cameraPos, cameraRotation);
        renderer.setView(view);
    }


    void render() {
        LOOP_S(4) {
            renderer.clear();
            renderer.renderMeshes(0.1);
            renderer.swapBuffers();
        }
    }

    void SetUp() override {
    }
};

TEST_F(MeshRenderingTest, test) {
    this->render();
    checkBackgroundColor();
    checkCenterColor(expectedFigureColor);
}
