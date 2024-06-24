/**************************************************************************************************
 * @file   EntityTypes.h
 * @author Valentin Dumitru
 * @date   13/06/2024
 * @brief  @TODO Add description of this file if needed
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
namespace GLESC {
    /**
     * @brief This is part of the entity metadata and does not affect the entity's behavior or memory allocation.
     * For now is just for differentiationg instance from other entities when creating entity names.
     */
    enum class EntityType {
        Instance,
        Engine,
        Default
    };
}
