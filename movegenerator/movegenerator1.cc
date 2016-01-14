#include "movegenerator.h"

MoveGenerator::MoveGenerator()
{
  d_moves.push_back(new Slide(Slide::TOP));
  d_moves.push_back(new Slide(Slide::RIGHT));
  d_moves.push_back(new Slide(Slide::BOTTOM));
  d_moves.push_back(new Slide(Slide::LEFT));

  // Add a 2 tile.
  for (size_t pos = 0; pos != 15; ++pos)
  {
    // d_moves.push_back(new Insert(2, pos));
    d_moves.push_back(new Insert(1, pos));

    // inserts start at index 4
    d_insertsCopyMachine.push_back(4 + pos);
  }
}