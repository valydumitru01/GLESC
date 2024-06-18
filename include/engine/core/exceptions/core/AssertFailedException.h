/**************************************************************************************************
 * @file   AssertFailedException.h
 * @author Valentin Dumitru
 * @date   08/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/core/exceptions/EngineException.h"

class AssertFailedException : public EngineException {
public:
    explicit AssertFailedException(const std::string& message) : EngineException("Assert Failed: " + message) {}
}; // class AssertFailedException
