#include <sstream>
#include <engine/core/asserts/Asserts.h>
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/subsystems/renderer/texture/Texture.h"

#include "engine/subsystems/renderer/texture/TextureAdapter.h"

using namespace GLESC::Render;


Texture::Texture(const std::string& path, const bool flipTexture/*= true*/) {
    load(path, flipTexture);
}

Texture::~Texture() {
    if (hasLoaded) {
        getGAPI().deleteTexture(textureID);
    }
}

void Texture::load(const std::string& path, const bool flipTexture) {
    D_ASSERT_TRUE(!path.empty(), "File path is empty.");
    textureID = textureID = getGAPI().createTexture(Enums::Texture::Types::Texture2D,
                                                    Enums::Texture::Filters::Min::Linear,
                                                    Enums::Texture::Filters::Mag::Linear,
                                                    Enums::Texture::Filters::WrapMode::ClampToEdge,
                                                    Enums::Texture::Filters::WrapMode::ClampToEdge);
    textureSurface.load(path, flipTexture);
    load(textureSurface);
    hasLoaded = true;
}

void Texture::load(const ResMng::Texture::TextureSurface& textureSurfaceParam) {
    textureSurface = textureSurfaceParam;
    const Enums::Texture::CPUBufferFormat inputFormat = getTextureInputFormat(textureSurface.getFormat().colorFormat);
    const Enums::Texture::BitDepth bitDepth = getTextureBitDepth(textureSurface.getFormat().bitDepth);

    getGAPI().setTextureData(
        Enums::Texture::Types::Texture2D, 0, textureSurface.getWidth(), textureSurface.getHeight(),
        inputFormat, bitDepth, textureSurface.getPixels().data());
}

void Texture::bind(const TextureSlot textureSlot/*= 0*/) const {
    D_ASSERT_TRUE(hasLoaded, "Texture not loaded");
    getGAPI().bindTextureOnSlot(textureID, Enums::Texture::Types::Texture2D, textureSlot);
}

void Texture::unbind() const {
    D_ASSERT_TRUE(hasLoaded, "Texture not loaded");
    getGAPI().unbindTexture(Enums::Texture::Types::Texture2D);
}

void Texture::release() {
    textureSurface.release();
}
