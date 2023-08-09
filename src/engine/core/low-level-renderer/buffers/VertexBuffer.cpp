/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"


BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements) : elements(elements) {
    calculateOffsetsAndStride();
}

VertexBuffer::VertexBuffer(GraphicInterface &graphicsInterface,
                           const std::initializer_list<BufferElement> &elements,
                           const void *data,
                           GDIsize size) : graphicInterface(graphicsInterface), vertexBufferID(0) {
    
    graphicInterface.genBuffers(1, vertexBufferID);
    graphicInterface.bindBuffer(GDIValues::BufferTypeVertex, vertexBufferID);
    graphicInterface
            .setBufferData(data, size, vertexBufferID, GDIValues::BufferTypeVertex, GDIValues::BufferUsageStatic);
    graphicInterface.unbindBuffer(GDIValues::BufferTypeVertex);
}

VertexBuffer::~VertexBuffer() {
    graphicInterface.deleteBuffer(vertexBufferID);
}

void VertexBuffer::bind() const {
    graphicInterface.bindBuffer(GDIValues::BufferTypeVertex, vertexBufferID);
}

void VertexBuffer::unbind() const {
    graphicInterface.unbindBuffer(GDIValues::BufferTypeVertex);
}
