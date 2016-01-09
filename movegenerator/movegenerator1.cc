#include "movegenerator.h"

MoveGenerator::MoveGenerator()
{
  d_slides.push_back(new Slide(Slide::TOP));
  d_slides.push_back(new Slide(Slide::RIGHT));
  d_slides.push_back(new Slide(Slide::BOTTOM));
  d_slides.push_back(new Slide(Slide::LEFT));

  // Add a 2 tile.
  for (size_t pos = 0; pos != 15; ++pos)
    d_inserts.push_back(new Insert(1, pos));
}