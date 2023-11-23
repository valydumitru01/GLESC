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


VertexBuffer::VertexBuffer(const void *data,
                           GAPIsize size) {
    D_ASSERT_NOT_NULL(data, "Data is null in VertexBuffer constructor");
    D_ASSERT_TRUE(size > 0, "Size is 0 in VertexBuffer constructor");
    gapi.genBuffers(1, vertexBufferID);
    gapi.bindBuffer(GAPIValues::BufferTypeVertex, vertexBufferID);
    gapi.setBufferData(data, size, GAPIValues::BufferTypeVertex,
                       GAPIValues::BufferUsageStaticDraw);
    gapi.unbindBuffer(GAPIValues::BufferTypeVertex);
}


VertexBuffer::~VertexBuffer() {
    destroyOnce();
}

void VertexBuffer::destroy() {
    destroyOnce();
}

void VertexBuffer::bind() const {
    gapi.bindBuffer(GAPIValues::BufferTypeVertex, vertexBufferID);
}

void VertexBuffer::unbind() const {
    gapi.unbindBuffer(GAPIValues::BufferTypeVertex);
}

void VertexBuffer::destroyOnce() {
    if (objectAlive) {
        
        gapi.deleteBuffer(vertexBufferID);
        
        objectAlive = false;
    }
}

