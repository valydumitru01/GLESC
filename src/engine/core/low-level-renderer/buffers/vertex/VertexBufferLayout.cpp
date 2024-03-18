/******************************************************************************
 * @file   VertexBufferLayout.cpp
 * @author Valentin Dumitru
 * @date   2023-11-06
 * @brief  @todo Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#include "engine/core/low-level-renderer/buffers/vertex/VertexBufferLayout.h"

using namespace GLESC;



void VertexBufferLayout::push(GAPI::Types type, GAPI::Bool normalized)  {
    auto typeSize = getTypeSize(type);
    elements.push_back({type, normalized});

    stride += static_cast<GAPI::UInt>(typeSize);
}