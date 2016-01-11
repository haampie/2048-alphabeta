#include "move.h"

std::ostream &operator<<(std::ostream &os, Move const &move)
{
  move.print(os);
  return os;
}

void Move::print(std::ostream &os) const
{
  os << "Empty move";
}

void Insert::print(std::ostream &os) const
{
  os << "Insert " << (1 << d_num) << " at " << d_pos;
}

void Slide::print(std::ostream &os) const
{
  switch(d_dir)
  {
    case TOP:
      os << "Slide up";
    break;
    case BOTTOM:
      os << "Slide down";
    break;
    case LEFT:
      os << "Slide left";
    break;
    case RIGHT:
      os << "Slide right";
    break;
  }
}