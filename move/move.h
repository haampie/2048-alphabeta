#ifndef MOVE_INCLUDE
#define MOVE_INCLUDE

#include <iostream>
#include "../board/board.h"

class Move
{
public:
  virtual Board apply(Board board)
  {
    return Board();
  }
  virtual ~Move() {}
};

class Insert : public Move
{
  size_t d_num;
  size_t d_pos;
public:
  Insert(size_t num, size_t pos);
  Board apply(Board board) override;
};

class Slide : public Move
{
public:
  enum Direction
  {
    TOP = 0,
    RIGHT = 1,
    BOTTOM = 2,
    LEFT = 3
  };
  Slide(Direction dir);
  Board apply(Board board) override;
private:
  Direction d_dir;
};

#endif