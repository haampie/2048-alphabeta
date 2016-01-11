#ifndef MOVE_INCLUDE
#define MOVE_INCLUDE

#include <iostream>
#include "../board/board.h"

class Move
{
  friend std::ostream &operator<<(std::ostream &os, const Move& move);
public:
  virtual Board apply(Board board)
  {
    return Board();
  }
  virtual ~Move() {}
protected:
  virtual void print(std::ostream& os) const;
};

class Insert : public Move
{
  size_t d_num;
  size_t d_pos;
public:
  Insert(size_t num, size_t pos);
  Board apply(Board board) override;
protected:
  void print(std::ostream& os) const override;
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
  Direction d_dir;
protected:
  void print(std::ostream& os) const override;
private:
};

#endif