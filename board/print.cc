#include "board.h"
#include <iomanip>

std::ostream &operator<<(std::ostream &os, const Board& board)
{
  board_t copy = board.d_board;
  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      size_t value = 1 << (copy & 0xF);
      os << std::setw(5) << (value == 1 ? 0 : value);
      copy >>= 4;
    }
    os << '\n';
  }
  return os << '\n';
}