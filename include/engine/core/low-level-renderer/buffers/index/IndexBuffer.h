/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <vector>
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

namespace GLESC {
    class IndexBuffer {
    public:
        IndexBuffer() = default;
        IndexBuffer(const GAPIuint *data,const GAPIsize count);
        IndexBuffer(const std::vector<GAPIuint> &data);
        
        ~IndexBuffer();
        
        void destroy();
        
        void bind() const;
        
        void unbind() const;
        
        [[nodiscard]] inline GAPIsize getCount() const { return count; }
        
        [[nodiscard]] GAPIuint getBufferID() const { return indexBufferID; }
    
    private:
        void destroyOnce();
        
        bool objectAlive = true;
        GAPIsize count{};
        GAPIuint indexBufferID{};
    };
}