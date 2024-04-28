/**************************************************************************************************
 * @file   TextureFactory.h
 * @author Valentin Dumitru
 * @date   2024-04-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <string>
#include <unordered_map>

#include "Cubemap.h"
#include "Texture.h"
#include "engine/core/hash/Hasher.h"

class TextureFactory {
public:
    /**
     * @brief Default constructor.
     */
    TextureFactory() = default;
    GLESC::Render::Texture& loadTexture(const std::string& path);
    Cubemap& loadCubemap(const std::array<std::string, 6>& facePaths);
protected:

private:
    std::unordered_map<GLESC::Hasher::Hash, GLESC::Render::Texture> textures;
    std::unordered_map<GLESC::Hasher::Hash, Cubemap> cubemaps;
}; // class TextureFactory