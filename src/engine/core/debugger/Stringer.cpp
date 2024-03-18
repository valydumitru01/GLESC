/**************************************************************************************************
 * @file   Stringer.cpp
 * @author Valentin Dumitru
 * @date   10/03/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024$ Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#include "engine/core/debugger/Stringer.h"


int GLESC::Stringer::floatPrecision = DEFAULT_FLOAT_PRECISION;

std::string GLESC::Stringer::replace(const std::string& string, const std::string& stringToReplace,
                                     const std::string& replacement) {
    std::string result = string;
    size_t pos = 0;
    while ((pos = result.find(stringToReplace, pos)) != std::string::npos) {
        result.replace(pos, stringToReplace.length(), replacement);
        pos += replacement.length();
    }
    return result;
}

bool GLESC::Stringer::contains(const std::string& string, const std::string& substring) {
    return string.find(substring) != std::string::npos;
}