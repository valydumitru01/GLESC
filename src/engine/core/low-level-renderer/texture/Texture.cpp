

#include "engine/res-mng/textures/TextureLoader.h"
#include "engine/core/low-level-renderer/texture/asserts/TextureAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/texture/Texture.h"
#include "engine/core/low-level-renderer/texture/debugger/TextureDebugger.h"

using namespace GLESC;

Texture::Texture(std::string pathParam) :
        textureID(),
        width(0),
        height(0),
        path(std::move(pathParam)) {
    using namespace GAPI::Texture;
    textureID = gapi.createTexture(Filters::Min::Linear,
                                   Filters::Mag::Linear,
                                   Filters::WrapMode::ClampToEdge,
                                   Filters::WrapMode::ClampToEdge);
    this->bind();
    SDL_SurfacePtr sdlSurface = TextureLoader::loadTexture(path);
    
    initializeData(*sdlSurface);
    PRINT_TEXTURE_DATA(*this);
    if (format->aMask) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     static_cast<GLsizei>(getWidth()),
                     static_cast<GLsizei>(getHeight()),
                     0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     static_cast<GLsizei>(getWidth()),
                     static_cast<GLsizei>(getHeight()),
                     0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    }
    
    
    // gapi.setTextureData(0, width, height, pixels.data());
    
    this->unbind();
}

Texture::~Texture() {
    gapi.deleteTexture(textureID);
}

void Texture::bind(GAPI::UInt slot/*= 0*/) const {
    gapi.bindTextureOnSlot(textureID, slot);
}

void Texture::unbind() const {
    gapi.unbindTexture();
}

void Texture::initializeData(SDL_Surface &sdlSurface) {
    // TODO: Is all this copying really necessary? Maybe use the SDL_Surface directly?
    //    But having our own format is useful
    
    format = std::make_shared<Format>();
    
    format->rMask = sdlSurface.format->Rmask;
    format->gMask = sdlSurface.format->Gmask;
    format->bMask = sdlSurface.format->Bmask;
    format->aMask = sdlSurface.format->Amask;
    format->rLoss = sdlSurface.format->Rloss;
    format->gLoss = sdlSurface.format->Gloss;
    format->bLoss = sdlSurface.format->Bloss;
    format->aLoss = sdlSurface.format->Aloss;
    format->rShift = sdlSurface.format->Rshift;
    format->gShift = sdlSurface.format->Gshift;
    format->bShift = sdlSurface.format->Bshift;
    format->aShift = sdlSurface.format->Ashift;
    
    
    // Assert that the bits per pixel is as expected
    D_ASSERT_BPP_IS_CORRECT(sdlSurface.format->BitsPerPixel);
    
    // Set format's bit depth
    format->bitDepth =
            static_cast<GAPI::Texture::InternalFormat::BitDepth>(sdlSurface.format->BitsPerPixel);
    
    // Set texture dimensions
    width = static_cast<GAPI::UInt>(sdlSurface.w);
    height = static_cast<GAPI::UInt>(sdlSurface.h);
    
    // Calculate the total number of bytes for all pixels
    size_t totalBytes = width * height * static_cast<size_t>(sdlSurface.format->BytesPerPixel);
    
    // Resize the pixel vector to accommodate all bytes
    pixels.resize(totalBytes);
    
    // Copy the pixel data using memcpy for efficiency
    std::memcpy(pixels.data(), sdlSurface.pixels, totalBytes);
    
    // Set format's data type
    format->dataType = GAPI::Types::UByte;
    
    // If the surface has an alpha mask, then it's RGBA, otherwise it's RGB
    if (sdlSurface.format->Amask) {
        format->colorFormat = GAPI::Texture::InternalFormat::ColorFormat::RGBA;
    } else {
        format->colorFormat = GAPI::Texture::InternalFormat::ColorFormat::RGB;
    }
}


Pixel Texture::getPixel(GAPI::UInt x, GAPI::UInt y) const {
    auto baseUBytePixelPtr = pixels.data();
    auto byteDepth = static_cast<GAPI::UInt>(format->bitDepth) / 8;
    
    // Move the pointer to the pixel we want to read
    baseUBytePixelPtr += (y * width + x) * byteDepth;
    Uint32 pixelValue = 0;
    
    // Assuming the data is stored in little-endian format
    for (GAPI::UInt i = 0; i < byteDepth; ++i) {
        pixelValue |= static_cast<Uint32>(baseUBytePixelPtr[i]) << (8 * i);
    }
    
    // Extract the individual color components
    auto r = static_cast<Uint8>((pixelValue & format->rMask) >> format->rShift);
    auto g = static_cast<Uint8>((pixelValue & format->gMask) >> format->gShift);
    auto b = static_cast<Uint8>((pixelValue & format->bMask) >> format->bShift);
    Uint8 a = (format->aMask != 0)
            ? static_cast<Uint8>((pixelValue & format->aMask) >> format->aShift) : 255;
    
    // Normalize if needed (i.e. if the bit depth is less than 8)
    r = (format->rLoss != 0) ? r * 255 / ((1 << format->rLoss) - 1) : r;
    g = (format->gLoss != 0) ? g * 255 / ((1 << format->gLoss) - 1) : g;
    b = (format->bLoss != 0) ? b * 255 / ((1 << format->bLoss) - 1) : b;
    // Alpha normalization is typically not needed if alpha is either 0 or 255
    
    return Pixel{r, g, b, a};
}

std::string Texture::toString() const {
    std::stringstream ss;
    ss << "Texture:\n";
    ss << "\tPath: " << path << "\n";
    ss << "\tWidth: " << width << "\n";
    ss << "\tHeight: " << height << "\n";
    ss << "\tTotal of pixels: " << getTotalOfPixels() << "\n";
    ss << "\tFormat:\n" << format->toString();
    return ss.str();
}

const Format &Texture::getFormat() const {
    return *format;
}