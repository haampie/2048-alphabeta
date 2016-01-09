#include "board.h"

Board Board::transpose() const
{
  board_t board = d_board;
  board_t a1 = board & 0xF0F00F0FF0F00F0FULL;
  board_t a2 = board & 0x0000F0F00000F0F0ULL;
  board_t a3 = board & 0x0F0F00000F0F0000ULL;
  board_t a = a1 | (a2 << 12) | (a3 >> 12);
  board_t b1 = a & 0xFF00FF0000FF00FFULL;
  board_t b2 = a & 0x00FF00FF00000000ULL;
  board_t b3 = a & 0x00000000FF00FF00ULL;
  return Board(b1 | (b2 >> 24) | (b3 << 24));
}