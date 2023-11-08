/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <utility>

#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/asserts/Asserts.h"

namespace GLESC {
    
    class VertexBuffer {
    public:
        VertexBuffer(const std::any *data,
                     GAPIsize size);
        
        ~VertexBuffer();
        
        void bind() const;
        
        void unbind() const;
        
        void setData(const std::any *data, GAPIsize size);
    
    private:
        GAPIuint vertexBufferID{};
        
    };
}