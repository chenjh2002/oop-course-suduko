//===----------------------------------------------------
//                    SODUKU
// Created by chenjunhao on 2024/9/24.
// SUDUKO src/include/config.h
//
//===-----------------------------------------------------

#pragma once

#include <cstdint>

namespace suduko {

using grid_element_t = uint8_t;
using row_t = int32_t;
using col_t = int32_t;

static const int32_t MAX_GRID_SIZE = 9;
static const int32_t MAX_BOX_SIZE = 3;
static const int32_t INVALID_ROW_INDEX = -1;
static const int32_t INVALID_COL_INDEX = -1;

/**
 * Mask of the specific number
 */
#define ONE_MASK 0x0001
#define TWO_MASK 0x0002
#define THREE_MASK 0x0004
#define FOUR_MASK 0x0008
#define FIVE_MASK 0x0010
#define SIX_MASK 0x0020
#define SEVEN_MASK 0x0040
#define EIGHT_MASK 0x0080
#define NINE_MASK 0x0100

#define FULL_MASK (ONE_MASK | TWO_MASK | THREE_MASK | FOUR_MASK | FIVE_MASK | SIX_MASK | SEVEN_MASK | EIGHT_MASK | NINE_MASK)

#define __number_to_mask(x) (ONE_MASK << (x - 1))
} // namespace suduko
