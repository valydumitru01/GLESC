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

#include "engine/GLESC.h"

class Game {
public:
    Game(GLESC::Engine& engine);
    void update();
private:
    GLESC::Engine& engine;
}; // class Game

