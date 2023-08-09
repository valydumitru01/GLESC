/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "BaseException.h"


class EngineException : public BaseException {
public:
    explicit EngineException(const std::string &message) : BaseException(message) {}
};
