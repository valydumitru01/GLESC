/******************************************************************************
* @file   GAPIException.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief Exception class for the engine.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/core/exceptions/EngineException.h"

class GAPIException : public EngineException {
public:
    explicit GAPIException(const std::string &message)
            : EngineException("GAPI error:" + message) {}
};
