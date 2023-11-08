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
        ShaderDataType type;
        ShaderDataDim dimension;
        GAPIuint count;
        GAPIsize offset;
        GAPIbool normalized;
    };
    
    class VertexBufferLayout {
    
    public:
        VertexBufferLayout() : stride(0) {}
        
        [[nodiscard]] const std::vector<VertexBufferElement> &getElements() const;
        
        [[nodiscard]] uint32_t getStride() const;
        
        template<ShaderDataType shaderDataType, ShaderDataDim shaderDataDim>
        void push(GAPIuint count) {
            elements.push_back({shaderDataType, shaderDataDim, count, 0, false});
            
            stride += static_cast<GAPIuint>(shaderDataType)
                      * static_cast<GAPIuint>(shaderDataDim)
                      * count;
        }
    
    private:
        std::vector<VertexBufferElement> elements;
        GAPIuint stride;
    };
}