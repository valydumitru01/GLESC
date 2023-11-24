/******************************************************************************
 * @file   Example.h
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

IndexBuffer::IndexBuffer(const GAPI::UInt *data, const GAPI::Size count) :
        count(count){
    gapi.genBuffers(1, indexBufferID);
    this->bind();
    gapi.setBufferData(data, count,
                       GAPI::BufferTypes::Index,
                       GAPI::BufferUsages::StaticDraw);
}

IndexBuffer::IndexBuffer(const std::vector<GAPI::UInt> &data) :
    IndexBuffer(data.data(), static_cast<GAPI::Size>(data.size())){}

IndexBuffer::~IndexBuffer() {
    destroyOnce();
}

void IndexBuffer::destroy() {
    destroyOnce();
}


void IndexBuffer::bind() const {
    gapi.bindBuffer(GAPI::BufferTypes::Index, indexBufferID);
}

void IndexBuffer::unbind() const {
    gapi.unbindBuffer(GAPI::BufferTypes::Index);
}



void IndexBuffer::destroyOnce(){
    if (objectAlive) {
        gapi.deleteBuffer(indexBufferID);
        objectAlive = false;
    }
}