/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/low-level-renderer/graphic-device-interface/GraphicInterface.h"

namespace GLESC {
    class IndexBuffer {
    public:
        IndexBuffer(GraphicInterface &graphicInterface, const unsigned int *data, unsigned int count);
        
        ~IndexBuffer();
        
        void bind() const;
        
        void unbind() const;
        
        [[nodiscard]] inline GDIsize getCount() const { return count; }
    
    private:
        GDIsize count;
        GDIint indexBufferID;
        GraphicInterface &graphicInterface;
    };
}