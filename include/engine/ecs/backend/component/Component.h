/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <glm/glm.hpp>
/**
 * @brief Base class for all components
 * @details All components must inherit from this class and must implement all the pure virtual functions.
 * This is necessary for the derived classes to be used in the ECS.
 */
struct Component {
    [[nodiscard]] virtual std::string toString() const = 0;
};

