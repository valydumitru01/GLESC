/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/exceptions/resources/ResourceException.h"
#include "SDL2/SDL_image.h"

class TextureManager {
public:
    explicit TextureManager(GLESC_RENDER_API &graphicInterfaceParam) :
            graphicInterface(graphicInterfaceParam) {};
private:
    GLESC_RENDER_API &graphicInterface;
};
