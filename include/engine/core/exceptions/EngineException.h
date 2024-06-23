/******************************************************************************
* @file   EngineException.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief Exception class for the engine.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include "BaseException.h"


class EngineException : public BaseException {
public:
    explicit EngineException(const std::string &message) : BaseException(message) {}
};
