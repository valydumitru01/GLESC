#include "engine/core/graphics-device-interface/buffers/VertexBuffer.h"

BufferLayout::BufferLayout(std::initializer_list <BufferElement> elements) : elements(elements) {
    calculateOffsetsAndStride();
}

VertexBuffer::VertexBuffer(GraphicsInterface &graphicsInterface, const std::initializer_list <BufferElement> &elements,
                           const void *data, GDIsize size) : graphicInterface(graphicsInterface), vertexBufferID(0),
                                                             layout(elements) {
    
    graphicInterface.genBuffers(1, vertexBufferID);
    graphicInterface.bindBuffer(Buffers::Type::Vertex, vertexBufferID);
    graphicInterface.setBufferData(data, size, vertexBufferID, Buffers::Type::Vertex, Buffers::Usage::Static);
    graphicInterface.unbindBuffer(vertexBufferID);
}

void VertexBuffer::setLayout(const BufferLayout &&layoutParam) {
    this->layout = layoutParam;
}

void VertexBuffer::bind() const {
    graphicInterface.bindBuffer(Buffers::Type::Vertex, vertexBufferID);
}

void VertexBuffer::unbind() const {
    graphicInterface.unbindBuffer(vertexBufferID);
}
