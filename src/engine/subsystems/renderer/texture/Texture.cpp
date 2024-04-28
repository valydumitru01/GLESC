#include <sstream>
#include <engine/core/asserts/Asserts.h>
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/subsystems/renderer/texture/Texture.h"

#include "engine/subsystems/renderer/texture/TextureAdapter.h"

using namespace GLESC::Render;



Texture::Texture(const std::string& path) {
    textureID = textureID = getGAPI().createTexture(Enums::Texture::Types::Texture2D,
                                                    Enums::Texture::Filters::Min::Linear,
                                                    Enums::Texture::Filters::Mag::Linear,
                                                    Enums::Texture::Filters::WrapMode::ClampToEdge,
                                                    Enums::Texture::Filters::WrapMode::ClampToEdge);
    load(path);
}

Texture::~Texture() {
    if (hasLoaded) {
        getGAPI().deleteTexture(textureID);
    }
}

void Texture::load(const std::string& path) {
    D_ASSERT_TRUE(!path.empty(), "File path is empty.");
    textureSurface.load(path);
    load(textureSurface);
}

void Texture::load(const ResMng::Texture::TextureSurface& textureSurfaceParam) {
    hasLoaded = true;
    textureSurface = textureSurfaceParam;
    Enums::Texture::CPUBufferFormat inputFormat = getTextureInputFormat(textureSurface.getFormat().colorFormat);
    Enums::Texture::BitDepth bitDepth = getTextureBitDepth(textureSurface.getFormat().bitDepth);

    getGAPI().setTextureData(
        Enums::Texture::Types::Texture2D, 0, textureSurface.getWidth(), textureSurface.getHeight(),
        inputFormat, bitDepth, textureSurface.getPixels().data());

}

void Texture::bind(TextureSlot textureSlot/*= 0*/) const {
    D_ASSERT_TRUE(hasLoaded, "Texture not loaded");
    getGAPI().bindTextureOnSlot(textureID, Enums::Texture::Types::Texture2D, textureSlot);
}

void Texture::unbind() const {
    D_ASSERT_TRUE(hasLoaded, "Texture not loaded");
    getGAPI().unbindTexture(Enums::Texture::Types::Texture2D);
}
