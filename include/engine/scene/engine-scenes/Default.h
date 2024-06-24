/**************************************************************************************************
 * @file   Default.h
 * @author Valentin Dumitru
 * @date   13/05/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/scene/Scene.h"

/**
 * @brief Default scene.
 * @details This is the default scene that is loaded when the engine starts.
 * It contains some objects rotationg, some lights and the camera with default camera movement.
 */
class Default : public GLESC::Scene::Scene {
public:
    SCENE_DEFINITION(Default)

    void init() override;
    void update() override;

}; // class Default
