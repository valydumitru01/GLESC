/**************************************************************************************************
 * @file   Default.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/scene/Scene.h"

class Default : public GLESC::Scene::Scene {
public:
    SCENE_DEFINITION(Default)

    void init() override;
    void update() override;

}; // class Default
