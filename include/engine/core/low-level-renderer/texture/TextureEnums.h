/**************************************************************************************************
 * @file   TextureEnums.h
 * @author Valentin Dumitru
 * @date   07/12/2023
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

namespace Tex {
    enum class Format {
        RGB [[maybe_unused]],
        RGBA [[maybe_unused]],
        BGR [[maybe_unused]],
        BGRA [[maybe_unused]],
        Depth [[maybe_unused]],
        Stencil [[maybe_unused]],
        DepthStencil [[maybe_unused]]
    };
    enum class BitDepth {
        Bit8 [[maybe_unused]] = 8,
        Bit16 [[maybe_unused]] = 16,
        Bit24 [[maybe_unused]] = 24,
        Bit32 [[maybe_unused]] = 32
    };
    enum class Slot {
        Slot0 = 0,
        Slot1 [[maybe_unused]] = 1,
        Slot2 [[maybe_unused]] = 2,
        Slot3 [[maybe_unused]] = 3,
        Slot4 [[maybe_unused]] = 4,
        Slot5 [[maybe_unused]] = 5,
        Slot6 [[maybe_unused]] = 6,
        Slot7 [[maybe_unused]] = 7,
        Slot8 [[maybe_unused]] = 8,
        Slot9 [[maybe_unused]] = 9,
        Slot10 [[maybe_unused]] = 10,
        Slot11 [[maybe_unused]] = 11,
        Slot12 [[maybe_unused]] = 12,
        Slot13 [[maybe_unused]] = 13,
        Slot14 [[maybe_unused]] = 14,
        Slot15 [[maybe_unused]] = 15,
        Slot16 [[maybe_unused]] = 16,
        Slot17 [[maybe_unused]] = 17,
        Slot18 [[maybe_unused]] = 18,
        Slot19 [[maybe_unused]] = 19,
        Slot20 [[maybe_unused]] = 20,
        Slot21 [[maybe_unused]] = 21,
        Slot22 [[maybe_unused]] = 22,
        Slot23 [[maybe_unused]] = 23,
        Slot24 [[maybe_unused]] = 24,
        Slot25 [[maybe_unused]] = 25,
        Slot26 [[maybe_unused]] = 26,
        Slot27 [[maybe_unused]] = 27,
        Slot28 [[maybe_unused]] = 28,
        Slot29 [[maybe_unused]] = 29,
        Slot30 [[maybe_unused]] = 30,
        Slot31 [[maybe_unused]] = 31,
        Slot32 [[maybe_unused]] = 32,
        Slot33 [[maybe_unused]] = 33,
        Slot34 [[maybe_unused]] = 34,
        Slot35 [[maybe_unused]] = 35,
        Slot36 [[maybe_unused]] = 36,
        Slot37 [[maybe_unused]] = 37,
        Slot38 [[maybe_unused]] = 38,
        Slot39 [[maybe_unused]] = 39,
        Slot40 [[maybe_unused]] = 40,
        Slot41 [[maybe_unused]] = 41,
        Slot42 [[maybe_unused]] = 42,
        Slot43 [[maybe_unused]] = 43,
        Slot44 [[maybe_unused]] = 44,
        Slot45 [[maybe_unused]] = 45,
        Slot46 [[maybe_unused]] = 46,
        Slot47 [[maybe_unused]] = 47,
        Slot48 [[maybe_unused]] = 48,
        Slot49 [[maybe_unused]] = 49,
        Slot50 [[maybe_unused]] = 50
    };
}