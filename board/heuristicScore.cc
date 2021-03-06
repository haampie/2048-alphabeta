#include "board.h"
#include "../heuristics/tables.h"

float Board::heuristicScore() const
{
  board_t trans = transpose();
  return heur_score_table[(d_board >>  0) & ROW_MASK] +
         heur_score_table[(d_board >> 16) & ROW_MASK] +
         heur_score_table[(d_board >> 32) & ROW_MASK] +
         heur_score_table[(d_board >> 48) & ROW_MASK] +
         heur_score_table[(trans >>  0) & ROW_MASK] +
         heur_score_table[(trans >> 16) & ROW_MASK] +
         heur_score_table[(trans >> 32) & ROW_MASK] +
         heur_score_table[(trans >> 48) & ROW_MASK];
}