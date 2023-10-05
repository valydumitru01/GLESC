/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
 
#include "engine/core/exceptions/EngineException.h"

class MeshException : public EngineException {
public:
    explicit MeshException(const std::string &message) : EngineException("Mesh error:"+message) {}
};