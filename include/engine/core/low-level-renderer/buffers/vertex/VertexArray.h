/******************************************************************************
 * @file   VertexArray.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace GLESC {
    class VertexArray {
    public:
        VertexArray();
        
        ~VertexArray();
        
        void addBuffer(const GLESC::VertexBuffer &vb, const GLESC::VertexBufferLayout &layout);
        
        void bind() const;
        
        void unbind() const;
        
        [[nodiscard]] GAPIuint getRendererID() const;
    
    private:
        GAPIuint vertexArrayID;
    }; // class VertexArray
    
} // namespace GLESC