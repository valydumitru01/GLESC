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

#include <utility>
#include <any>

#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

namespace GLESC {
    class VertexBuffer {
    public:
        VertexBuffer(const GAPI::Void* data,
                     GAPI::Size count,
                     GAPI::Size size,
                     GAPI::BufferUsages bufferUsage = GAPI::BufferUsages::DynamicDraw);

        ~VertexBuffer();

        [[nodiscard]] GAPI::UInt getBufferID() const { return vertexBufferID; }

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
        GAPI::UInt vertexBufferID{0};
    }; // class VertexBuffer
} // namespace GLESC

