/**************************************************************************************************
 * @file   TextureDebugger.h
 * @author Valentin Dumitru
 * @date   04/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#ifndef NLOGGING

#include <string>
#include "engine/core/low-level-renderer/texture/TextureEnums.h"
#define PRINT_TEXTURE_DATA(texture) Logger::get().info(toString());

namespace Tex{
    std::string toString(Tex::Format format);
    std::string toString(Tex::BitDepth bitDepth);
}
#endif // NLOGGING