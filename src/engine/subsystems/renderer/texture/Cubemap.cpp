/**************************************************************************************************
 * @file   Cubemap.cpp
 * @author Valentin Dumitru
 * @date   28/04/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/subsystems/renderer/texture/Cubemap.h"
#include "engine/subsystems/renderer/texture/TextureAdapter.h"

Cubemap::Cubemap(const std::array<std::string, 6>& facePaths) {
    load(facePaths);
}

Cubemap::~Cubemap() {
    if (hasLoaded) {
        getGAPI().deleteTexture(textureID);
    }
}

void Cubemap::load(const std::array<std::string, 6>& facePaths) {
    textureID = getGAPI().createTexture(Enums::Texture::Types::TextureCubeMap,
                                        Enums::Texture::Filters::Min::Linear,
                                        Enums::Texture::Filters::Mag::Linear,
                                        Enums::Texture::Filters::WrapMode::ClampToEdge,
                                        Enums::Texture::Filters::WrapMode::ClampToEdge,
                                        Enums::Texture::Filters::WrapMode::ClampToEdge);
    for (size_t i = 0; i < facePaths.size(); ++i) {
        cubemapTextures[i].load(facePaths[i], false);
        auto nextFaceEnumInt = static_cast<int>(Enums::Texture::Types::TextureCubeMapPositiveX) + i;
        auto nextFaceEnum = static_cast<Enums::Texture::Types>(nextFaceEnumInt);
        getGAPI().setTextureData(nextFaceEnum,
                                 0,
                                 cubemapTextures[i].getWidth(),
                                 cubemapTextures[i].getHeight(),
                                 getTextureInputFormat(cubemapTextures[i].getFormat().colorFormat),
                                 getTextureBitDepth(cubemapTextures[i].getFormat().bitDepth),
                                 cubemapTextures[i].getPixels().data());
    }
    hasLoaded = true;
}


void Cubemap::bind() const {
    D_ASSERT_TRUE(hasLoaded, "Cubemap not loaded");
    getGAPI().bindTextureOnSlot(textureID, Enums::Texture::Types::TextureCubeMap, 0);
}

void Cubemap::unbind() const {
    D_ASSERT_TRUE(hasLoaded, "Cubemap not loaded");
    getGAPI().unbindTexture(Enums::Texture::Types::TextureCubeMap);
}
