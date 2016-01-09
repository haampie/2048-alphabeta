#include "stdint.h"

#ifndef TYPES_INCLUDE
#define TYPES_INCLUDE

typedef uint64_t board_t;
typedef uint16_t row_t;
static const board_t ROW_MASK = 0xFFFFULL;
static const board_t COL_MASK = 0x000F000F000F000FULL;

#endif