/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/low-level-renderer/buffers/vertex/VertexBuffer.h"

using namespace GLESC;


VertexBuffer::~VertexBuffer() {
    destroyOnce();
}

void VertexBuffer::destroy() {
    destroyOnce();
}

void VertexBuffer::bind() const {
    gapi.bindBuffer(GAPI::BufferTypes::Vertex, vertexBufferID);
}

void VertexBuffer::unbind() const {
    gapi.unbindBuffer(GAPI::BufferTypes::Vertex);
}

void VertexBuffer::destroyOnce() {
    if (objectAlive) {
        
        gapi.deleteBuffer(vertexBufferID);
        
        objectAlive = false;
    }
}

