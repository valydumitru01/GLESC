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
#include "engine/subsystems/renderer/shaders/Shader.h"
#include "integration/rendering/RenderingTestHelper.h"
#include "LoopHelper.cpp"


class MeshRenderingTest : public ::testing::Test {
protected:
    GLESC::WindowManager windowManager;
    GLESC::Renderer renderer;
    GLESC::ColorMesh mesh;
    GLESC::Material material;
    GLESC::Transform transform;
    // These are pointers because we don't want to call the constructor
    MeshRenderingTest() : windowManager(), renderer(windowManager) {
        mesh = GLESC::MeshFactory::cube(RGBA(1,0,0,1));
        renderer.setData(material,mesh, transform);
    }


    void prepareShaders() {
    }

    void prepareBuffers() {
    }

    void render() {
        renderer.clear();
        renderer.renderMeshes(0.01);
        renderer.applyMaterial(material);
        renderer.applyTransform(mesh, GLESC::Transform());
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
