/******************************************************************************
 * @file   BufferLayout.cpp
 * @author Valentin Dumitru
 * @date   2023-11-06
 * @brief  Add description of this file if needed @todo 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/low-level-renderer/buffers/vertex/VertexBufferLayout.h"

using namespace GLESC;


[[nodiscard]] const std::vector<VertexBufferElement> &
VertexBufferLayout::getElements() const { return elements; }

[[nodiscard]] uint32_t VertexBufferLayout::getStride() const { return stride; }