/**************************************************************************************************
 * @file   MeshRenderingTest.cpp
 * @author Valentin Dumitru
 * @date   2024-03-27
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include <gtest/gtest.h>

#include "engine/core/window/WindowManager.h"
#include "engine/subsystems/renderer/Renderer.h"
#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"
#include "engine/core/low-level-renderer/shader/Shader.h"
#include "integration/rendering/RenderingTestHelper.h"
#include "LoopHelper.cpp"

using namespace GLESC::Render;
class MeshRenderingTest : public ::testing::Test {
protected:
    GLESC::WindowManager windowManager;
    Renderer renderer;
    ColorMesh mesh;
    Material material;
    GLESC::Transform::Transform transform;
    // These are pointers because we don't want to call the constructor
    MeshRenderingTest() : windowManager(), renderer(windowManager) {
        mesh = MeshFactory::cube(ColorRgba(1,0,0,1));
        renderer.sendMeshData(material,mesh, transform);
    }


    void prepareShaders() {
    }

    void prepareBuffers() {
    }

    void render() {
        renderer.start();
        renderer.renderMeshes(0.01);
        renderer.swapBuffers();
    }

    void SetUp() override {
        LOOP_S(3) {
            render();
        }
    }

    void TearDown() override {
    }

private
:
};

TEST_F(MeshRenderingTest, test) {
    checkBackgroundColor();
}
