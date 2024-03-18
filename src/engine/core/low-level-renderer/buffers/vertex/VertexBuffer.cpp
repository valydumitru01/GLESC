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
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/asserts/Asserts.h"

using namespace GLESC;

VertexBuffer::VertexBuffer(const GAPI::Void* data,
                     GAPI::Size count,
                     GAPI::Size size,
                     GAPI::BufferUsages bufferUsage) {
    D_ASSERT_NOT_NULLPTR(data, "Data is null in VertexBuffer constructor");
    D_ASSERT_TRUE(size > 0, "Size is 0 in VertexBuffer constructor");
    getGAPI().genBuffers(1, vertexBufferID);
    this->bind();
    getGAPI().setBufferData(data, count, size, GAPI::BufferTypes::Vertex, bufferUsage);
}

VertexBuffer::~VertexBuffer() {
    destroyOnce();
}

void VertexBuffer::destroy() {
    destroyOnce();
}

void VertexBuffer::bind() const {
    getGAPI().bindBuffer(GAPI::BufferTypes::Vertex, vertexBufferID);
}

void VertexBuffer::unbind() const {
    getGAPI().unbindBuffer(GAPI::BufferTypes::Vertex);
}

void VertexBuffer::destroyOnce() {
    if (objectAlive) {
        
        getGAPI().deleteBuffer(vertexBufferID);
        
        objectAlive = false;
    }
}

