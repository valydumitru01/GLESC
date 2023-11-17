/**************************************************************************************************
 * @file   WindowException.h
 * @author Valentin Dumitru
 * @date   2023-11-16
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include "engine/core/exceptions/EngineException.h"

class WindowException : EngineException{
public:
    explicit WindowException(const std::string &message)
            : EngineException("Window error: " + message) {}
}; // class WindowException