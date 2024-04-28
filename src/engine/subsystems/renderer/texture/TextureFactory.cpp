/**************************************************************************************************
 * @file   TextureFactory.cpp
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/subsystems/renderer/texture/TextureFactory.h"

#include "engine/core/hash/Hasher.h"

GLESC::Render::Texture& TextureFactory::loadTexture(const std::string& path) {
    D_ASSERT_FALSE(path.empty(), "Path is empty");
    GLESC::Hasher::Hash hash = std::hash<std::string>{}(path);
    if (textures.find(hash) != textures.end()) {
        return textures[hash];
    }

    // Use emplace to construct the Texture in-place
    auto [newIt, inserted] = textures.emplace(std::piecewise_construct,
                                              std::forward_as_tuple(hash),
                                              std::forward_as_tuple());
    newIt->second.load(path);
    return newIt->second;
}

Cubemap& TextureFactory::loadCubemap(const std::array<std::string, 6>& facePaths) {
    D_ASSERT_FALSE(facePaths.empty(), "Face paths are empty");
    GLESC::Hasher::Hash hash = 0;
    for (const auto& path : facePaths) {
        GLESC::Hasher::hashCombine(hash, std::hash<std::string>{}(path));
    }

    if (cubemaps.find(hash) != cubemaps.end()) {
        return cubemaps[hash];
    }

    // Use emplace to construct the Cubemap in-place
    auto [newIt, inserted] = cubemaps.emplace(std::piecewise_construct,
                                              std::forward_as_tuple(hash),
                                              std::forward_as_tuple());
    for (size_t i = 0; i < facePaths.size(); ++i) {
        newIt->second.cubemapTextures[i].load(facePaths[i]);
    }
    return newIt->second;
}