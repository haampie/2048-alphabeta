#include "movegenerator.h"
#include <algorithm>

std::vector<Move*> MoveGenerator::viable(Board const &board, bool maximizing, Move *prefer) const
{
  // Slide move
  if (maximizing)
  {
    std::vector<Move*> list;
    list.reserve(4);
    for (size_t idx = 0; idx != 4; ++idx)
      if (static_cast<board_t>(board) != d_moves[idx]->apply(board))
        list.push_back(d_moves[idx]);

    // Not on the PV, so don't order moves
    if (prefer == nullptr)
      return list;

    auto it = std::find(list.begin(), list.end(), prefer);

    // Not found
    if (it == list.end())
      return list;

    // Put this move up front
    std::rotate(list.begin(), it, list.end());
    return list;
  }

  // Insert move (skip 4 inserts)
  auto begin = d_moves.begin() + 4;
  std::vector<Move*> list(begin, begin + 2 * board.empty());

  // Not on the PV, so don't order moves
  if (prefer == nullptr)
    return list;

  auto it = std::find(list.begin(), list.end(), prefer);

  // Not found
  if (it == list.end())
    return list;

  // Put this move up front
  std::rotate(list.begin(), it, list.end());
  return list;
}