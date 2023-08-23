/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <string>
#include "engine/core/logger/Logger.h"

namespace GLESC{
    template<typename T>
    [[maybe_unused]] [[nodiscard]] std::string toString(const T& valueToString) {
        ASSERT(false, "Value not supported to be converted to string");
    }
}

#ifdef DEBUG_LOGGING
#define DEBUG_CODE(initialMessage, CONTENT) \
        do{                                     \
        Logger::get().info(initialMessage);     \
        CONTENT                                 \
        } while(0)

#else
#define DEBUG_CODE(initialMessage, CONTENT) \
        do { } while (0)
#endif


