/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"


BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements) : elements(elements) {
    calculateOffsetsAndStride();
}

VertexBuffer::VertexBuffer(IGraphicInterface &graphicsInterface,
                           const std::initializer_list<BufferElement> &elements,
                           const std::any *data,
                           GAPIsize size) : graphicInterface(graphicsInterface) {
    
    graphicInterface.genBuffers(1, vertexBufferID);
    graphicInterface.bindBuffer(GAPIValues::BufferTypeVertex, vertexBufferID);
    graphicInterface
            .setBufferData(data, size, vertexBufferID, GAPIValues::BufferTypeVertex,
                           GAPIValues::BufferUsageStatic);
    graphicInterface.unbindBuffer(GAPIValues::BufferTypeVertex);
}

VertexBuffer::~VertexBuffer() {
    graphicInterface.deleteBuffer(vertexBufferID);
}

void VertexBuffer::bind() const {
    graphicInterface.bindBuffer(GAPIValues::BufferTypeVertex, vertexBufferID);
}

void VertexBuffer::unbind() const {
    graphicInterface.unbindBuffer(GAPIValues::BufferTypeVertex);
}
