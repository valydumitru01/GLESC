/**************************************************************************************************
 * @file   VertexInstanceBuffer.h
 * @author Valentin Dumitru
 * @date   13/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexBufferLayout.h"

namespace GLESC::GAPI {
    class VertexInstanceBuffer : public VertexBuffer {
    public:
        using VertexBuffer::VertexBuffer; // Inherit constructors

        // Method to setup instance attributes based on a layout
        void setupInstanceAttributes(const VertexBufferLayout &layout, GAPI::UInt startingIndex = 0);
    };
}
