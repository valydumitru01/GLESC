
#include "engine/subsystems/renderer/texture/Cubemap.h"
#include "engine/subsystems/renderer/texture/TextureAdapter.h"

Cubemap::Cubemap(const std::array<std::string, 6>& facePaths) {
    load(facePaths);
}

Cubemap::~Cubemap() {
    if (hasLoaded) {
        release();
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
        cubemapTextures[i].load("/cubemaps/"+facePaths[i], false);
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

std::array<Pixel, 6> Cubemap::getPixelsAtCoords(const int x, const int y) const {
    std::array<Pixel, 6> pixels{};
    for (int i = 0; i < 6; i++) {
        pixels[i] = cubemapTextures[i].getPixel(x, y);
    }
    return pixels;
}

void Cubemap::release() {
    if (hasLoaded) {
        for (auto& texture : cubemapTextures) {
            texture.release();
        }
    }
}

void Cubemap::bind() const {
    D_ASSERT_TRUE(hasLoaded, "Cubemap not loaded");
    getGAPI().bindTextureOnSlot(textureID, Enums::Texture::Types::TextureCubeMap, 0);
}

void Cubemap::unbind() const {
    D_ASSERT_TRUE(hasLoaded, "Cubemap not loaded");
    getGAPI().unbindTexture(Enums::Texture::Types::TextureCubeMap);
}
