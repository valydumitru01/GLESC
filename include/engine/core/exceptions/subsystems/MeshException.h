/******************************************************************************
 * @file   MeshException.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief An exception that is thrown when a mesh-related error occurs.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once
#include "engine/core/exceptions/EngineException.h"

class MeshException : public EngineException {
public:
    explicit MeshException(const std::string &message) : EngineException("Mesh error:"+message) {}
};