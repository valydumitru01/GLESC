/**************************************************************************************************
 * @file   Cubemap.h
 * @author Valentin Dumitru
 * @date   28/04/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <array>

#include "engine/res-mng/textures/TextureSurface.h"

class Cubemap {
public:
    Cubemap() = default;
    Cubemap(const std::array<std::string, 6>& facePaths);
    ~Cubemap();
    [[nodiscard]] bool hasBeenLoaded() const { return hasLoaded; }

    [[nodiscard]] const std::array<GLESC::ResMng::Texture::TextureSurface, 6>& getCubemapTextures() const {
        return cubemapTextures;
    }

    void bind() const;
    void unbind() const;
    void load(const std::array<std::string, 6>& facePaths);


private:
    bool hasLoaded{false};
    TextureID textureID{0};
    std::array<GLESC::ResMng::Texture::TextureSurface, 6> cubemapTextures{};
}; // class Cubemap
