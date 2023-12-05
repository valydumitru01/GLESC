/**************************************************************************************************
 * @file   TextureAsserts.h
 * @author Valentin Dumitru
 * @date   01/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#define D_ASSERT_BPP_IS_CORRECT(bpp) \
    D_ASSERT_TRUE(bpp == 8 || bpp==16 || bpp == 24 || bpp == 32, "Texture bpp is not correct")