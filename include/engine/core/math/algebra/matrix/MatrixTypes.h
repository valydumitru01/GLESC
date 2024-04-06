/**************************************************************************************************
 * @file   MatrixTypes.h
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
    
    template<typename Type, std::size_t M>
    using MatrixRow = std::array<Type, M>;
    
    template<typename Type, std::size_t N, std::size_t M>
    using MatrixData = std::array<MatrixRow<Type, M>, N>;
    
}