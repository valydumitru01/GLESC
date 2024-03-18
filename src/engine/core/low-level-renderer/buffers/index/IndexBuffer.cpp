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
#include "engine/core/low-level-renderer/buffers/index/IndexBuffer.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
using namespace GLESC;

IndexBuffer::IndexBuffer(const GAPI::UInt* data, const GAPI::Size count, GAPI::BufferUsages bufferUsage) :
    count(count) {
    getGAPI().genBuffers(1, indexBufferID);
    this->bind();
    getGAPI().setIndexBufferData(data, count, bufferUsage);
}

IndexBuffer::IndexBuffer(const std::vector<GAPI::UInt>& data, GAPI::BufferUsages bufferUsage) :
    IndexBuffer(data.data(), static_cast<GAPI::Size>(data.size()), bufferUsage) {}

IndexBuffer::~IndexBuffer() {
    destroyOnce();
}

void IndexBuffer::destroy() {
    destroyOnce();
}


void IndexBuffer::bind() const {
    getGAPI().bindBuffer(GAPI::BufferTypes::Index, indexBufferID);
}

void IndexBuffer::unbind() const {
    getGAPI().unbindBuffer(GAPI::BufferTypes::Index);
}


void IndexBuffer::destroyOnce() {
    if (objectAlive) {
        getGAPI().deleteBuffer(indexBufferID);
        objectAlive = false;
    }
}
