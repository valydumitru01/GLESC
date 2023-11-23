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

IndexBuffer::IndexBuffer(const GAPIuint *data,const GAPIsize count) :
        count(count){
    gapi.genBuffers(1, indexBufferID);
    gapi.bindBuffer(GAPIValues::BufferTypeIndex, indexBufferID);
    gapi.setBufferData(data, count,
                       GAPIValues::BufferTypeIndex,
                       GAPIValues::BufferUsageStaticDraw);
    gapi.unbindBuffer(GAPIValues::BufferTypeIndex);
}

IndexBuffer::IndexBuffer(const std::vector<GAPIuint> &data) :
    IndexBuffer(data.data(), static_cast<GAPIsize>(data.size())){
}

IndexBuffer::~IndexBuffer() {
    destroyOnce();
}

void IndexBuffer::destroy() {
    destroyOnce();
}


void IndexBuffer::bind() const {
    gapi.bindBuffer(GAPIValues::BufferTypeIndex, indexBufferID);
}

void IndexBuffer::unbind() const {
    gapi.unbindBuffer(GAPIValues::BufferTypeIndex);
}



void IndexBuffer::destroyOnce(){
    if (objectAlive) {
        gapi.deleteBuffer(indexBufferID);
        objectAlive = false;
    }
}