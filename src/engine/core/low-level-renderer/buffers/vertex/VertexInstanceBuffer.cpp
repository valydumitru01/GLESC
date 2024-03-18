/**************************************************************************************************
 * @file   VertexInstanceBuffer.cpp
 * @author Valentin Dumitru
 * @date   13/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "engine/core/low-level-renderer/buffers/vertex/VertexInstanceBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"

using namespace GLESC;

void VertexInstanceBuffer::setupInstanceAttributes(const VertexBufferLayout& layout, GAPI::UInt startingIndex) {
    // Assume the buffer is already bound, but it might be a good idea to bind it here again for safety
    bind();

    const auto& elements = layout.getElements();
    GAPI::UInt offset = 0;
    for (size_t i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        GAPI::UInt globalIndex = startingIndex + i; // Global attribute index considering the startingIndex

        // Calculate the size and type of the attribute
        GAPI::TypeCount typeCount = getTypeCount(element.type);
        GAPI::Types type = getTypePrimitiveType(element.type);
        GAPI::TypeSize typeSize = getTypeSize(type);

        // Setup the attribute pointer for this element
        getGAPI().createVertexData(globalIndex, static_cast<GAPI::UInt>(typeCount), type, element.normalized,
                                   layout.getStride(), offset);

        // This is the crucial part for instanced attributes, telling OpenGL this attribute varies per instance rather than per vertex
        getGAPI().setVertexAttribDivisor(globalIndex, 1);

        offset += static_cast<int>(typeCount) * static_cast<int>(typeSize);
    }
}
