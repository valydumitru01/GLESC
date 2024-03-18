/******************************************************************************
 * @file   VertexArray.cpp
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"

using namespace GLESC;

VertexArray::VertexArray() {
    getGAPI().genVertexArray(vertexArrayID);
}

VertexArray::~VertexArray() {
    destroyOnce();
}

void VertexArray::destroy() {
    destroyOnce();
}

void VertexArray::bind() const {
    getGAPI().bindVertexArray(vertexArrayID);
}

void VertexArray::unbind() const {
    getGAPI().unbindVertexArray();
}


void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {

    auto const& elements = layout.getElements();
    auto const& stride = layout.getStride();
    GAPI::UInt offset = 0;

    vb.bind();
    this->bind();

    for (size_t i = 0; i < elements.size(); ++i) {
        auto const& element = elements[i];
        auto const typeCount = static_cast<GAPI::UInt>(getTypeCount(element.type));
        auto const type = getTypePrimitiveType(element.type);
        auto const typeSize = static_cast<GAPI::UInt>(getTypeSize(type));

        // Set up the vertex attribute pointers
        getGAPI().createVertexData(static_cast<GAPI::UInt>(i), typeCount, type, element.normalized, stride, offset);
        // Enable the vertex attribute array
        getGAPI().enableVertexData(static_cast<GAPI::UInt>(i));
        // Calculate the offset for the next attribute
        offset += typeCount * typeSize;
    }

}


void VertexArray::destroyOnce() {
    if (objectAlive) {
        getGAPI().deleteVertexArray(vertexArrayID);
        objectAlive = false;
    }
}
