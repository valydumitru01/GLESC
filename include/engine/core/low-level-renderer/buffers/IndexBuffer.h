/******************************************************************************
 * @file   IndexBuffer.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include <vector>
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"
#include "engine/core/low-level-renderer/graphic-api/GapiEnums.h"

namespace GLESC::GAPI {
    class IndexBuffer {
    public:
        IndexBuffer(const UInt* data, Size count,
                    Enums::BufferUsages bufferUsage = Enums::BufferUsages::DynamicDraw);

        IndexBuffer(const std::vector<UInt>& data,
                    Enums::BufferUsages bufferUsage = Enums::BufferUsages::DynamicDraw);

        ~IndexBuffer();

        [[nodiscard]] Size getCount() const { return count; }

        [[nodiscard]] UInt getBufferID() const { return indexBufferID; }

        void destroy();

        void bind() const;

        void unbind() const;

    private:
        void destroyOnce();

        bool objectAlive = true;
        Size count{0};
        UInt indexBufferID{0};
    }; // class IndexBuffer
} // namespace GLESC

