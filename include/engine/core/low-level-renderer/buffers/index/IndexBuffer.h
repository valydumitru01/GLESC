/******************************************************************************
 * @file   IndexBuffer.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <vector>
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/core/low-level-renderer/graphic-api/Gapi.h"

namespace GLESC {
    class IndexBuffer {
    public:
        IndexBuffer(const GAPI::UInt* data, GAPI::Size count,
                    GAPI::BufferUsages bufferUsage = GAPI::BufferUsages::DynamicDraw);

        IndexBuffer(const std::vector<GAPI::UInt>& data,
                    GAPI::BufferUsages bufferUsage = GAPI::BufferUsages::DynamicDraw);

        ~IndexBuffer();

        [[nodiscard]] GAPI::Size getCount() const { return count; }

        [[nodiscard]] GAPI::UInt getBufferID() const { return indexBufferID; }

        void destroy();

        void bind() const;

        void unbind() const;

    private:
        void destroyOnce();

        bool objectAlive = true;
        GAPI::Size count{0};
        GAPI::UInt indexBufferID{0};
    }; // class IndexBuffer
} // namespace GLESC

