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
    destroyOnce();
}

void VertexArray::destroy() {
    destroyOnce();
}

void VertexArray::bind() const {
    gapi.bindVertexArray(vertexArrayID);
}

void VertexArray::unbind() const {
    gapi.unbindVertexArray();
}


void VertexArray::addBuffer(const GLESC::VertexBuffer &vb,
                            const GLESC::VertexBufferLayout &layout) {
    this->bind(); // Bind the VAO to set up its state
    vb.bind(); // Bind the VBO to associate it with the VAO
    
    // Retrieve the vertex attribute elements
    auto const &elements = layout.getElements();
    // Get the stride (byte offset between consecutive attributes)
    auto const &stride = layout.getStride();
    
    GAPIuint offset = 0; // Start with an offset of 0
    for (size_t i = 0; i < elements.size(); ++i) {
        // For each element in the layout
        auto const &element = elements[i];
        
        // Enable the vertex attribute array
        gapi.enableVertexData(static_cast<GAPIuint>(i));
        
        // Get the data from the enum type
        auto const typeCount = static_cast<GAPIuint>(getTypeCount(element.type));
        auto const type = getTypePrimitiveType(element.type);
        // The type size can be vectors or matrices, so we get the size from the primitive type
        // and not from the type of the element of the layout because it can be a vector or a matrix
        // and gapi recognizes only the size of the primitive types
        auto const typeSize = static_cast<GAPIuint>(getTypeSize(type));
        
        // Set up the vertex attribute pointers
        gapi.createVertexData(static_cast<GAPIuint>(i),
                              typeCount,
                              type,
                              element.normalized,
                              stride,
                              offset);
        
        // Calculate the offset for the next attribute
        offset += typeCount * typeSize;
    }
}

void VertexArray::destroyOnce() {
    if (objectAlive) {
        gapi.deleteVertexArray(vertexArrayID);
        objectAlive = false;
    }
}