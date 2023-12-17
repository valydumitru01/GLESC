/******************************************************************************
 * @file   VertexArray.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  @todo Add description of this file if needed
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
        
        void destroy();
        
        void addBuffer(const GLESC::VertexBuffer &vb, const GLESC::VertexBufferLayout &layout);
        
        void bind() const;
        
        void unbind() const;
        
        [[nodiscard]] GAPI::UInt getRendererID() const {
            return vertexArrayID;
        }
    
    private:
        void destroyOnce();
        
        bool objectAlive = true;
        GAPI::UInt vertexArrayID{0};
    }; // class VertexArray
    
} // namespace GLESC