/**************************************************************************************************
 * @file   ModelLoader.h
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "engine/core/asserts/Asserts.h"

class ModelLoader {
public:
    static const aiScene* loadModel(const std::string& path) {
        const aiScene* scene = importer.ReadFile(path,
                                                 aiProcess_Triangulate // Convert all the models to triangles
                                                 | aiProcess_FlipUVs // OpenGL uses inverted UVs
                                                 | aiProcess_GenNormals // Generate normals if they are missing
                                                 | aiProcess_JoinIdenticalVertices // Join identical vertices/positions
        );
        D_ASSERT_NOT_NULLPTR(scene, "Failed to load model: " + path);
        D_ASSERT_FALSE(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE, "Model is incomplete: " + path);
        D_ASSERT_NOT_NULLPTR(scene->mRootNode, "Model has no root node: " + path);
        return scene;
    }

    static Assimp::Importer importer;
}; // class ModelLoader
