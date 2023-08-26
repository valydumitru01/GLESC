/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#pragma once

#include <string>
#include "engine/core/logger/Logger.h"

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


