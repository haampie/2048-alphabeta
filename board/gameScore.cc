#include "board.h"
#include "../heuristics/tables.h"

float Board::gameScore() const
{
  return score_table[(d_board >>  0) & ROW_MASK] +
         score_table[(d_board >> 16) & ROW_MASK] +
         score_table[(d_board >> 32) & ROW_MASK] +
         score_table[(d_board >> 48) & ROW_MASK];
}