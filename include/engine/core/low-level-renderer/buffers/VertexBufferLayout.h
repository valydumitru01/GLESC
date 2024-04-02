/******************************************************************************
 * @file   VertexBufferLayout.h
 * @author Valentin Dumitru
 * @date   2023-11-06
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "../graphic-api/Gapi.h"

namespace GLESC::GAPI {
    struct VertexBufferElement {
        Enums::Types type;
        Bool normalized;
    };
    
    class VertexBufferLayout {
    
    public:
        VertexBufferLayout() : stride(0) {}
        
        [[nodiscard]] const std::vector<VertexBufferElement> &getElements() const { return elements; }
        [[nodiscard]] uint32_t getStride() const { return stride; }
        
        void push(Enums::Types type, Bool normalized = Bool::False);
    
    private:
        std::vector<VertexBufferElement> elements;
        UInt stride;
        
    }; // class VertexBufferLayout
} // namespace GLESC