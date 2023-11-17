/**************************************************************************************************
 * @file   GapiStructs.h
 * @author Valentin Dumitru
 * @date   2023-11-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once


#include "GapiTypes.h"

struct RGBColor {
    GAPIbyte r;
    GAPIbyte g;
    GAPIbyte b;
};
struct RGBColorNormalized {
    GAPIfloat r;
    GAPIfloat g;
    GAPIfloat b;
};