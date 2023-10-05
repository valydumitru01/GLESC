/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/exceptions/EngineException.h"

class GAPIException : public EngineException {
public:
    explicit GAPIException(const std::string &message)
            : EngineException("GDI error:" + message) {}
};
