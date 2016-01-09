#include "move.h"

Board Insert::apply(Board board)
{
  board_t tmp = board;
  size_t index = d_pos;
  size_t tile = d_num;
  while (true)
  {
    while ((tmp & 0xf) != 0)
    {
      tmp >>= 4;
      tile <<= 4;
    }

    if (index == 0)
      break;
    
    --index;
    tmp >>= 4;
    tile <<= 4;
  }

  return static_cast<board_t>(board) | tile;
}