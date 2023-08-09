/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/exceptions/EngineException.h"

class GDIException : public EngineException {
public:
    explicit GDIException(const std::string &message) : EngineException("GDI error:"+message) {}
};
