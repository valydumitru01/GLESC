/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/low-level-renderer/graphic-api/Gapi.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"

namespace GLESC {
    class IndexBuffer {
    public:
        IndexBuffer(const GAPIuint *data, GAPIsize count) :
                count(count){
            gapi.genBuffers(1, indexBufferID);
            gapi.bindBuffer(GAPIValues::BufferTypeIndex, indexBufferID);
            gapi.setBufferData(data, count, indexBufferID,
                                   GAPIValues::BufferTypeIndex,
                                   GAPIValues::BufferUsageStatic);
            gapi.unbindBuffer(GAPIValues::BufferTypeIndex);
        }
        
        ~IndexBuffer() {
            gapi.deleteBuffer(indexBufferID);
        }
        
        
        void bind() const {
            gapi.bindBuffer(GAPIValues::BufferTypeIndex, indexBufferID);
        }
        
        void unbind() const {
            gapi.unbindBuffer(GAPIValues::BufferTypeIndex);
        }
        
        
        [[nodiscard]] inline GAPIsize getCount() const { return count; }
    
    private:
        GAPIsize count{};
        GAPIuint indexBufferID{};
    };
}