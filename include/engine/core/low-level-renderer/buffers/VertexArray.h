/******************************************************************************
 * @file   VertexArray.h
 * @author Valentin Dumitru
 * @date   2023-11-07
 * @brief  * @brief @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/core/low-level-renderer/buffers/VertexBuffer.h"
#include "engine/core/low-level-renderer/buffers/VertexBufferLayout.h"

namespace GLESC::GAPI {
    class VertexArray {
    public:
        VertexArray();

        ~VertexArray();

        [[nodiscard]] UInt getRendererID() const { return vertexArrayID; }

        void destroy();

        /**
         * @brief Add a vertex buffer to the vertex array
         * @details The vertex buffer and the layout are moved, so they will be invalid after this call
         * @param vb The vertex buffer to add
         * @param layout The layout of the vertex buffer
         */
        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        void bind() const;

        void unbind() const;

    private:
        void destroyOnce();

        bool objectAlive = true;
        UInt vertexArrayID{0};
    }; // class VertexArray
} // namespace GLESC
