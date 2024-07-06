
#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"
#include "engine/core/asserts/Asserts.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"

using namespace GLESC::GAPI;

VertexBuffer::VertexBuffer(const Void *data,
                           Size count,
                           Size elementSize,
                           Enums::BufferUsages bufferUsage) {
    D_ASSERT_NOT_NULLPTR(data, "Data is null in VertexBuffer constructor");
    D_ASSERT_TRUE(elementSize > 0, "Size is 0 in VertexBuffer constructor");
    D_ASSERT_TRUE(count > 0, "Count is 0 in VertexBuffer constructor");
    getGAPI().genBuffers(1, vertexBufferID);
    this->bind();
    getGAPI().setBufferData(data, count, elementSize, Enums::BufferTypes::Vertex, bufferUsage);
}

VertexBuffer::~VertexBuffer() {
    destroyOnce();
}

void VertexBuffer::destroy() {
    destroyOnce();
}

void VertexBuffer::bind() const {
    getGAPI().bindBuffer(Enums::BufferTypes::Vertex, vertexBufferID);
}

void VertexBuffer::unbind() const {
    getGAPI().unbindBuffer(Enums::BufferTypes::Vertex);
}

void VertexBuffer::destroyOnce() {
    if (objectAlive) {
        getGAPI().deleteBuffer(vertexBufferID);

        objectAlive = false;
    }
    D_ASSERT_TRUE(!objectAlive, "Failed to destroy VertexBuffer");
}
