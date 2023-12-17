/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <utility>
#include <any>

#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/asserts/Asserts.h"

namespace GLESC {
    
    class VertexBuffer {
    public:
        template<class Type>
        VertexBuffer(const Type *data, GAPI::Size size) {
            D_ASSERT_NOT_NULLPTR(data, "Data is null in VertexBuffer constructor");
            D_ASSERT_TRUE(size > 0, "Size is 0 in VertexBuffer constructor");
            getGAPI().genBuffers(1, vertexBufferID);
            this->bind();
            getGAPI().setBufferStaticData(data, size,
                                          GAPI::BufferTypes::Vertex);
        }
        
        template<class Type, class = std::enable_if_t<isGraphicsType_v<Type>>>
        VertexBuffer(const std::vector<Type> &data) :
            VertexBuffer(data.data(), data.size()) {
        
        }
        
        ~VertexBuffer();
        
        [[nodiscard]] GAPI::UInt getBufferID() const { return vertexBufferID; }
        
        void destroy();
        
        void bind() const;
        
        void unbind() const;
    
    private:
        /**
         * @brief This method destroys the vertex buffer object once.
         * It is called from the destructor and the destroy method.
         * If its called once the next time it will do nothing.
         * This is to prevent double deletion.
         * Enables the destruction of this object from the destroy method.
         */
        void destroyOnce();
        
        bool objectAlive = true;
        GAPI::UInt vertexBufferID{0};
        
    };
}