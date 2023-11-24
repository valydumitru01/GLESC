/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <vector>
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"

namespace GLESC {
    class IndexBuffer {
    public:
        IndexBuffer(const GAPI::UInt *data, const GAPI::Size count);

        IndexBuffer(const std::vector<GAPI::UInt> &data);
        
        ~IndexBuffer();
        
        void destroy();
        
        void bind() const;
        
        void unbind() const;
        
        [[nodiscard]] inline GAPI::Size getCount() const { return count; }
        
        [[nodiscard]] GAPI::UInt getBufferID() const { return indexBufferID; }
    
    private:
        void destroyOnce();
        
        bool objectAlive = true;
        GAPI::Size count{};
        GAPI::UInt indexBufferID{0};
    };
}