/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/low-level-renderer/buffers/IndexBuffer.h"
#include "engine/core/low-level-renderer/graphic-device-interface/GraphicInterface.h"

using namespace GLESC;

IndexBuffer::IndexBuffer(GraphicInterface &graphicInterface, const GDIuint *data, GDIsize count) :
        count(count), indexBufferID(0), graphicInterface(graphicInterface) {
    graphicInterface.genBuffers(1, indexBufferID);
    graphicInterface.bindBuffer(GDIValues::BufferTypeIndex, indexBufferID);
    graphicInterface.setBufferData(data, count, indexBufferID, GDIValues::BufferTypeIndex, GDIValues::BufferUsageStatic);
    graphicInterface.unbindBuffer(GDIValues::BufferTypeIndex);
}

IndexBuffer::~IndexBuffer() {
    graphicInterface.deleteBuffer(indexBufferID);
}


void IndexBuffer::bind() const{
    graphicInterface.bindBuffer(GDIValues::BufferTypeIndex, indexBufferID);
}

void IndexBuffer::unbind() const{
    graphicInterface.unbindBuffer(GDIValues::BufferTypeIndex);
}
