
#include "engine/core/low-level-renderer/buffers/VertexBufferLayout.h"

using namespace GLESC::GAPI;

void VertexBufferLayout::push(Enums::Types type, Bool normalized) {
    auto typeSize = getTypeSize(type);
    elements.push_back({type, normalized});

    stride += static_cast<UInt>(typeSize);
}
