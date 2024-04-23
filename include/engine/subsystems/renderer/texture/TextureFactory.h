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
#include <unordered_map>

#include "engine/core/low-level-renderer/texture/Texture.h"
using PathHash = std::size_t;
class TextureFactory {
public:
    /**
     * @brief Default constructor.
     */
    TextureFactory() = default;
    Texture& loadTexture(const std::string& path);
protected:

private:
    std::unordered_map<PathHash, Texture> textures;
}; // class TextureFactory