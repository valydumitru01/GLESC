#include "engine/core/low-level-renderer/texture/debugger/TextureDebugger.h"

#ifndef NLOGGING
std::string Tex::toString(Tex::Format format){
    switch (format){
        case Tex::Format::RGB:
            return "RGB";
        case Tex::Format::RGBA:
            return "RGBA";
        case Tex::Format::BGR:
            return "BGR";
        case Tex::Format::BGRA:
            return "BGRA";
        case Tex::Format::Depth:
            return "Depth";
        case Tex::Format::Stencil:
            return "Stencil";
        case Tex::Format::DepthStencil:
            return "DepthStencil";
        default:
            return "Invalid format";
    }
}
std::string Tex::toString(Tex::BitDepth bitDepth){
    switch (bitDepth){
        case Tex::BitDepth::Bit8:
            return "8";
        case Tex::BitDepth::Bit16:
            return "16";
        case Tex::BitDepth::Bit24:
            return "24";
        case Tex::BitDepth::Bit32:
            return "32";
        default:
            return "Invalid bit depth";
    }
}

#endif // NLOGGING