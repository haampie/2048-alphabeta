#include "movegenerator.h"
#include <algorithm>

std::vector<char> MoveGenerator::viable(Board const &board, bool maximizing, char prefer) const
{
  // Slide move
  if (maximizing)
  {
    std::vector<char> list;
    list.reserve(4);
    for (char idx = 0; idx != 4; ++idx)
      if (static_cast<board_t>(board) != d_moves[idx]->apply(board))
        list.push_back(idx);

    // Not on the PV, so don't order moves
    if (prefer == 100)
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
  // numbered as 4, 5, 6, ..., 4 + 2 * board.empty();
  auto begin = d_insertsCopyMachine.begin();
  std::vector<char> list(begin, begin + 2 * board.empty());

  // Not on the PV, so don't order moves
  if (prefer == 100)
    return list;

  auto it = std::find(list.begin(), list.end(), prefer);

  // Not found
  if (it == list.end())
    return list;

  // Put this move up front
  std::rotate(list.begin(), it, list.end());
  return list;
}