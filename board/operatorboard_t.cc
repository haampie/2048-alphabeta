#include "board.h"

Board::operator board_t() const
{
  return d_board;
}