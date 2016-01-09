#include "board.h"
#include <iomanip>

void Board::print() const
{
  board_t copy = d_board;
  for (size_t i = 0; i < 4; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      size_t value = 1 << (copy & 0xF);
      std::cout << std::setw(5) << (value == 1 ? 0 : value);
      copy >>= 4;
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}