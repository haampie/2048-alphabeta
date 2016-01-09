#ifndef BOARD_INCLUDE
#define BOARD_INCLUDE

#include "../types.h"
#include <cstddef>
#include <iostream>

class Board
{
  friend std::ostream & operator<<(std::ostream &os, const Board& board);
  board_t d_board;
public:
  enum Move
  {
    TOP = 0,
    RIGHT = 1,
    BOTTOM = 2,
    LEFT = 3
  };
  Board();
  Board(board_t position);
  operator board_t() const;
  Board insert(board_t tile, size_t index) const;
  Board transpose() const;
  Board applyMove(Move move) const;
  size_t maxTile() const;
  float gameScore() const;
  float heuristicScore() const;
  size_t empty() const;
};

#endif