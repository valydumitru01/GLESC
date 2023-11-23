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
        VertexBuffer() = default;
        
        VertexBuffer(const void *data, GAPIsize size);
        
        template<typename T>
        VertexBuffer(std::vector<T> data) :
                VertexBuffer(data.data(), data.size() * sizeof(T)) {}
        
        ~VertexBuffer();
        
        [[nodiscard]] GAPIuint getBufferID() const { return vertexBufferID; }
        
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
        GAPIuint vertexBufferID{};
        
    };
}