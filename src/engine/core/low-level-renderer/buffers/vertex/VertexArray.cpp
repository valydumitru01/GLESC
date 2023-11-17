/******************************************************************************
 * @file   VertexArray.cpp
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/core/low-level-renderer/buffers/vertex/VertexArray.h"

using namespace GLESC;

VertexArray::VertexArray(){
    gapi.genVertexArray(vertexArrayID);
}

VertexArray::~VertexArray() {
    gapi.deleteVertexArray(vertexArrayID);
}

void VertexArray::bind() const {
    gapi.bindVertexArray(vertexArrayID);
}

void VertexArray::unbind() const {
    gapi.unbindVertexArray();
}

GAPIuint VertexArray::getRendererID() const {
    return vertexArrayID;
}


void VertexArray::addBuffer(const GLESC::VertexBuffer &vb,
                            const GLESC::VertexBufferLayout &layout) {
    this->bind();
    vb.bind();
    auto const &elements = layout.getElements();
    auto const &stride = layout.getStride();
    GAPIuint offset = 0;
    for (int i = 0; i < elements.size(); ++i) {
        auto const &element = elements[i];
        
        gapi.enableVertexAttribArray(i);
        gapi.vertexAttribPointer(i, element.count, element.type, GAPI_FALSE, stride, offset);
        
        offset += element.count
                  * static_cast<GAPIuint>(element.dimensionSize)
                  * static_cast<GAPIuint>(element.typeSize);
        
    }
}