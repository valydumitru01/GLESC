/******************************************************************************
 * @file   MathException.h
 * @author Valentin Dumitru
 * @date   2023-10-04
 * @brief  Exception class for math errors.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "engine/core/exceptions/EngineException.h"

class MathException : public EngineException {
public:
    explicit MathException(const std::string &message)
            : EngineException("Math error:" + message) {}
};
