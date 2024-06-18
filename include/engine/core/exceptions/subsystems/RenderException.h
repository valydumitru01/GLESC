/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/exceptions/BaseException.h"

class RenderException : public BaseException {
public:
    explicit RenderException(const std::string &message) : BaseException("Rendering error:"+message) {}
};
