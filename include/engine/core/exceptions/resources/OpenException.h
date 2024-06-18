/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/exceptions/EngineException.h"

class OpenException : public EngineException {
public:
    explicit OpenException(const std::string &message) : EngineException(message) {}
private:
};
