/******************************************************************************
 * @file   VertexBuffer.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/core/low-level-renderer/graphic-api/GapiEnums.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

namespace GLESC::GAPI {
    class VertexBuffer {
    public:
        VertexBuffer(const Void *data,
                     Size count,
                     Size elementSize,
                     Enums::BufferUsages bufferUsage = Enums::BufferUsages::DynamicDraw);

        ~VertexBuffer();

        [[nodiscard]] UInt getBufferID() const { return vertexBufferID; }

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
        UInt vertexBufferID{0};
    }; // class VertexBuffer
} // namespace GLESC
