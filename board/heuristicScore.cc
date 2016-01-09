#include "board.h"
#include "../heuristics/tables.h"

float Board::heuristicScore() const
{
  return heur_score_table[(d_board >>  0) & ROW_MASK] +
         heur_score_table[(d_board >> 16) & ROW_MASK] +
         heur_score_table[(d_board >> 32) & ROW_MASK] +
         heur_score_table[(d_board >> 48) & ROW_MASK];
}