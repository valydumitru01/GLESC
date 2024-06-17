/******************************************************************************
 * @file   IndexBuffer.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once
#include "engine/core/low-level-renderer/buffers/IndexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
using namespace GLESC::GAPI;

IndexBuffer::IndexBuffer(const UInt* data, const Size count, Enums::BufferUsages bufferUsage) :
    count(count) {
    getGAPI().genBuffers(1, indexBufferID);
    this->bind();
    getGAPI().setIndexBufferData(data, count, bufferUsage);
}

IndexBuffer::IndexBuffer(const std::vector<UInt>& data, Enums::BufferUsages bufferUsage) :
    IndexBuffer(data.data(), static_cast<Size>(data.size()), bufferUsage) {
}

IndexBuffer::~IndexBuffer() {
    destroyOnce();
}

void IndexBuffer::destroy() {
    destroyOnce();
}


void IndexBuffer::bind() const {
    getGAPI().bindBuffer(Enums::BufferTypes::Index, indexBufferID);
}

void IndexBuffer::unbind() const {
    getGAPI().unbindBuffer(Enums::BufferTypes::Index);
}


void IndexBuffer::destroyOnce() {
    if (objectAlive) {
        std::vector<UInt> ibuData = getGAPI().getBufferDataUI(indexBufferID);
        getGAPI().deleteBuffer(indexBufferID);
        objectAlive = false;
    }
}
