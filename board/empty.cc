#include "board.h"

size_t Board::empty() const
{
  board_t x = d_board;

  x |= (x >> 2) & 0x3333333333333333ULL;
  x |= (x >> 1);
  x = ~x & 0x1111111111111111ULL;

  x += x >> 32;
  x += x >> 16;
  x += x >> 8;
  x += x >> 4;
  return x & 0xf;
}