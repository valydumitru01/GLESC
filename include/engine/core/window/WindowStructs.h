/**************************************************************************************************
 * @file   WindowStructs.h
 * @author Valentin Dumitru
 * @date   29/11/2023
 * @brief Defines structures related to window properties.
 * @details This file contains the definition of the WindowDimensions structure, which holds
 * information about the dimensions of a window, including its width and height.
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

namespace GLESC {
    struct WindowDimensions {
        int width;
        int height;
        
        WindowDimensions() : width(0), height(0) {}
        
        WindowDimensions(int width, int height) : width(width), height(height) {}
    };
}
