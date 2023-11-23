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
        GAPIType type;
        GAPIbool normalized;
    };
    
    class VertexBufferLayout {
    
    public:
        VertexBufferLayout() : stride(0) {}
        
        [[nodiscard]] const std::vector<VertexBufferElement> &getElements() const;
        
        [[nodiscard]] uint32_t getStride() const;
        
        void push(GAPIType type, GAPIbool normalized = GAPI_FALSE) {
            auto typeSize = getTypeSize(type);
            elements.push_back({type, normalized});
            
            stride += static_cast<GAPIuint>(typeSize);
        }
    
    private:
        std::vector<VertexBufferElement> elements;
        GAPIuint stride;
        
    }; // class VertexBufferLayout
} // namespace GLESC