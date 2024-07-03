/**************************************************************************************************
 * @file   Cubemap.h
 * @author Valentin Dumitru
 * @date   28/04/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include <array>

#include "engine/res-mng/textures/TextureSurface.h"

/**
 * @brief Class representing a cubemap texture. It abstract away the creating and handling of cubemaps.
 * @details A cubemap is a type of texture that contains 6 faces of a cube, each face being a 2D texture.
 * @details A cubemap helps retrieving a texel from a 3D direction vector, which is useful for many rendering techniques
 * @details Example of cubemap usage is skyboxes, reflections, refractions, etc.
 *
 */
class Cubemap {
public:
    Cubemap() = default;
    explicit Cubemap(const std::array<std::string, 6>& facePaths);
    ~Cubemap();
    [[nodiscard]] bool hasBeenLoaded() const { return hasLoaded; }

    [[nodiscard]] const std::array<GLESC::ResMng::Texture::TextureSurface, 6>& getCubemapTextures() const {
        return cubemapTextures;
    }

    [[nodiscard]] std::array<GLESC::ResMng::Texture::TextureSurface, 6>& getCubemapTextures() {
        return cubemapTextures;
    }

    [[nodiscard]] std::array<Pixel, 6> getPixelsAtCoords(int x, int y) const;

    void bind() const;
    void unbind() const;
    void load(const std::array<std::string, 6>& facePaths);
    void release();

private:
    bool hasLoaded{false};
    TextureID textureID{0};
    std::array<GLESC::ResMng::Texture::TextureSurface, 6> cubemapTextures{};
}; // class Cubemap
