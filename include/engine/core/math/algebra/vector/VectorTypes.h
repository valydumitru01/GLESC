/**************************************************************************************************
 * @file   VectorTypes.h
 * @author Valentin Dumitru
 * @date   22/01/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <array>

namespace GLESC::Math {
    /**
     * @brief Type alias for a vector data
     * @details We use a std::array to store the vector data contiguously in memory with a fixed size and minimum
     * overhead.
     * @tparam Type The type of the vector elements
     * @tparam N The number of elements in the vector
     */
    template<typename Type, std::size_t N>
    using VectorData = std::array<Type, N>;


} // namespace GLESC::Math