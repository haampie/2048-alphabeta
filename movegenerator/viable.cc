#include "movegenerator.h"
#include <algorithm>

std::vector<Move*> MoveGenerator::viable(Board const &board, bool maximizing, Move *prefer) const
{
  // Slide move
  if (maximizing)
  {
    std::vector<Move*> list;
    for (auto &move : d_slides)
      if (static_cast<board_t>(board) != move->apply(board))
        list.push_back(move);

    // Not on the PV, so don't order moves
    if (not prefer)
      return list;

    auto it = std::find(list.begin(), list.end(), prefer);

    // Not found
    if (it == list.end())
      return list;

    // Put this move up front
    std::rotate(list.begin(), it, list.end());
    return list;
  }

  // Insert move
  std::vector<Move*> list(d_inserts.begin(), d_inserts.begin() + 2 * board.empty());
  // Not on the PV, so don't order moves
  if (not prefer)
    return list;

  auto it = std::find(list.begin(), list.end(), prefer);

  // Not found
  if (it == list.end())
    return list;

  // Put this move up front
  std::rotate(list.begin(), it, list.end());
  return list;
}