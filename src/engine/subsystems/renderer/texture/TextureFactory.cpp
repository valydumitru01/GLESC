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

Texture& TextureFactory::loadTexture(const std::string& path) {
    D_ASSERT_FALSE(path.empty(), "Path is empty");
    PathHash hash = std::hash<std::string>{}(path);
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
