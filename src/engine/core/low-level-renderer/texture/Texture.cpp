

#include <sstream>
#include <engine/core/asserts/Asserts.h>
#include "engine/res-mng/textures/TextureLoader.h"
#include "engine/core/low-level-renderer/texture/asserts/TextureAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/texture/Texture.h"
#include "engine/core/low-level-renderer/texture/debugger/TextureDebugger.h"

using namespace GLESC;

inline GAPI::Texture::CPUBufferFormat getTextureInputFormat(Tex::Format format) {
    switch (format) {
        case Tex::Format::RGB:
            return GAPI::Texture::CPUBufferFormat::RGB;
        case Tex::Format::RGBA:
            return GAPI::Texture::CPUBufferFormat::RGBA;
        default:
            D_ASSERT_TRUE(false, "Invalid texture format");
    }
}

inline GAPI::Texture::BitDepth getTextureBitDepth(Tex::BitDepth bitDepth) {
    switch (bitDepth) {
        case Tex::BitDepth::Bit8:
            return GAPI::Texture::BitDepth::Bit8;
        case Tex::BitDepth::Bit16:
            return GAPI::Texture::BitDepth::Bit16;
        case Tex::BitDepth::Bit24:
            return GAPI::Texture::BitDepth::Bit24;
        case Tex::BitDepth::Bit32:
            return GAPI::Texture::BitDepth::Bit32;
        default:
            D_ASSERT_TRUE(false, "Invalid texture bit depth");
    }
}

Texture::Texture(std::string pathParam) :
        textureID(),
        width(0),
        height(0),
        path(std::move(pathParam)) {
    textureID = getGAPI().createTexture(GAPI::Texture::Filters::Min::Linear,
                                   GAPI::Texture::Filters::Mag::Linear,
                                   GAPI::Texture::Filters::WrapMode::ClampToEdge,
                                   GAPI::Texture::Filters::WrapMode::ClampToEdge);
    this->bind();
    SDL_SurfacePtr sdlSurface = TextureLoader::loadTexture(path);
    initializeData(*sdlSurface);
    PRINT_TEXTURE_DATA(*this);
    GAPI::Texture::CPUBufferFormat inputFormat = getTextureInputFormat(format->colorFormat);
    GAPI::Texture::BitDepth bitDepth = getTextureBitDepth(format->bitDepth);
    
    getGAPI().setTextureData(0, width, height, inputFormat, bitDepth, pixels.data());
    
    
    this->unbind();
}

Texture::~Texture() {
    getGAPI().deleteTexture(textureID);
}

void Texture::bind(Tex::Slot slot/*= Tex::Slot::Slot0*/) const {
    getGAPI().bindTextureOnSlot(textureID, static_cast<GAPI::UInt>(slot));
}

void Texture::unbind() const {
    getGAPI().unbindTexture();
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
    
    if (format->aMask)
        format->colorFormat = Tex::Format::RGBA;
    else
        format->colorFormat = Tex::Format::RGB;
    
    // Set format's bit depth
    format->bitDepth = static_cast<Tex::BitDepth>(sdlSurface.format->BitsPerPixel);
    
    // Set texture dimensions
    width = static_cast<GAPI::UInt>(sdlSurface.w);
    height = static_cast<GAPI::UInt>(sdlSurface.h);
    
    // Calculate the total number of bytes for all pixels
    size_t totalBytes = width * height * static_cast<size_t>(sdlSurface.format->BytesPerPixel);
    
    // Resize the pixel vector to accommodate all bytes
    pixels.resize(totalBytes);
    
    // Copy the pixel data using memcpy for efficiency
    std::memcpy(pixels.data(), sdlSurface.pixels, totalBytes);
    
}


Pixel Texture::getPixel(unsigned int x, unsigned int y) const {
    D_ASSERT_TRUE(x < width && y < height, "Pixel coordinates out of bounds");
    auto baseUBytePixelPtr = pixels.data();
    
    // Calculate the number of bytes per pixel
    // Divide by 8 because the bit depth is stored in bits and each byte has 8 bits
    auto byteDepth = static_cast<GAPI::UInt>(format->bitDepth) / 8;
    
    // Move the pointer to the pixel we want to read
    // Multiply by byteDepth because the pixel data is stored as bytes
    baseUBytePixelPtr += (y * width + x) * byteDepth;
    Uint32 pixelValue = 0;
    
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
    
    unsigned int pixelCount = 20;
    pixelCount = GLESC::Math::sqrt(pixelCount);
    unsigned int widthStep = std::max(1u, getWidth() / pixelCount);
    unsigned int heightStep = std::max(1u, getHeight() / pixelCount);
    Logger::get().info("\tPixels:");
    for (GAPI::UInt y = 0; y < getHeight() - 1; y += heightStep) {
        for (GAPI::UInt x = 0; x < getWidth() - 1; x += widthStep) {
            auto pixel = getPixel(x, y);
            
            Logger::get().info("\t\tPixel at (" + std::to_string(x) + ", " + std::to_string(y) +
                               "): " + pixel.toString());
        }
    }
    return ss.str();
}

const Format &Texture::getFormat() const {
    return *format;
}