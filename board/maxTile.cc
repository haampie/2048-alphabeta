#include "board.h"

size_t Board::maxTile() const
{
  size_t board = d_board;
  size_t max = 0;
  for (size_t tile = 0; tile < 16; ++tile)
  {
    size_t score = board & 0xF;
    if (score > max)
      max = score;
    board >>= 4;
  }
  return max;
}