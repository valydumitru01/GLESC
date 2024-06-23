/******************************************************************************
* @file   OpenException.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief Exception class for when a resource cannot be opened.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/exceptions/EngineException.h"

class OpenException : public EngineException {
public:
    explicit OpenException(const std::string &message) : EngineException(message) {}
private:
};
