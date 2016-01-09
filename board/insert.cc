#include "board.h"

Board Board::insert(board_t tile, size_t index) const
{
  board_t tmp = d_board;
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

  return d_board | tile;
}
