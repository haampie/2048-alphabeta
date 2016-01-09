#include "movegenerator.h"

std::vector<Move*> MoveGenerator::viable(Board &board, bool maximizing) const
{

  // Slide move
  if(maximizing)
  {
    std::vector<Move*> list;
    for (auto &move : d_slides)
      if(static_cast<board_t>(board) != move->apply(board))
        list.push_back(move);
    return list;
  }

  // Insert move
  return std::vector<Move*>(d_inserts.begin(), d_inserts.begin() + 2 * board.empty());
}