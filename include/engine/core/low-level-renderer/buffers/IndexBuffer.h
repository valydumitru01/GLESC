/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"

namespace GLESC {
    template<typename GAPI>
    class IndexBuffer {
    public:
        IndexBuffer(IGraphicInterface &graphicInterface, const GAPIuint *data, GAPIsize count) :
                count(count), graphicInterface(graphicInterface) {
            graphicInterface.genBuffers(1, indexBufferID);
            graphicInterface.bindBuffer(GAPIValues::BufferTypeIndex, indexBufferID);
            graphicInterface
                    .setBufferData(reinterpret_cast<const std::any *>(data), count, indexBufferID,
                                   GAPIValues::BufferTypeIndex,
                                   GAPIValues::BufferUsageStatic);
            graphicInterface.unbindBuffer(GAPIValues::BufferTypeIndex);
        }
        
        ~IndexBuffer() {
            graphicInterface.deleteBuffer(indexBufferID);
        }
        
        
        void bind() const {
            graphicInterface.bindBuffer(GAPIValues::BufferTypeIndex, indexBufferID);
        }
        
        void unbind() const {
            graphicInterface.unbindBuffer(GAPIValues::BufferTypeIndex);
        }
        
        
        [[nodiscard]] inline GAPIsize getCount() const { return count; }
    
    private:
        GAPIsize count{};
        GAPIuint indexBufferID{};
        GAPI &graphicInterface;
        // IGraphicInterface &graphicInterface;
    };
}