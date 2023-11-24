/******************************************************************************
 * @file   BufferLayout.h
 * @author Valentin Dumitru
 * @date   2023-11-06
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/core/low-level-renderer/graphic-api/Gapi.h"

namespace GLESC {
    struct VertexBufferElement {
        GAPI::Types type;
        GAPI::Bool normalized;
    };
    
    class VertexBufferLayout {
    
    public:
        VertexBufferLayout() : stride(0) {}
        
        [[nodiscard]] const std::vector<VertexBufferElement> &getElements() const;
        
        [[nodiscard]] uint32_t getStride() const;
        
        void push(GAPI::Types type, GAPI::Bool normalized = GAPI::Bool::False) {
            auto typeSize = getTypeSize(type);
            elements.push_back({type, normalized});
            
            stride += static_cast<GAPI::UInt>(typeSize);
        }
    
    private:
        std::vector<VertexBufferElement> elements;
        GAPI::UInt stride;
        
    }; // class VertexBufferLayout
} // namespace GLESC