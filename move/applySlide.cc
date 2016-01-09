#include "move.h"
#include "../heuristics/tables.h"

Board Slide::apply(Board board)
{
  board_t ret = board;
  switch (d_dir)
  {
  case TOP:
  {
    board_t t = board.transpose();
    ret ^= col_up_table[(t >>  0) & ROW_MASK] <<  0;
    ret ^= col_up_table[(t >> 16) & ROW_MASK] <<  4;
    ret ^= col_up_table[(t >> 32) & ROW_MASK] <<  8;
    ret ^= col_up_table[(t >> 48) & ROW_MASK] << 12;
  }
  break;
  case BOTTOM:
  {
    board_t t = board.transpose();
    ret ^= col_down_table[(t >>  0) & ROW_MASK] <<  0;
    ret ^= col_down_table[(t >> 16) & ROW_MASK] <<  4;
    ret ^= col_down_table[(t >> 32) & ROW_MASK] <<  8;
    ret ^= col_down_table[(t >> 48) & ROW_MASK] << 12;
  }
  break;
  case LEFT:
  {
    ret ^= board_t(row_left_table[(static_cast<Board>(board) >>  0) & ROW_MASK]) <<  0;
    ret ^= board_t(row_left_table[(static_cast<Board>(board) >> 16) & ROW_MASK]) << 16;
    ret ^= board_t(row_left_table[(static_cast<Board>(board) >> 32) & ROW_MASK]) << 32;
    ret ^= board_t(row_left_table[(static_cast<Board>(board) >> 48) & ROW_MASK]) << 48;
  }
  break;
  case RIGHT:
  {
    ret ^= board_t(row_right_table[(static_cast<Board>(board) >>  0) & ROW_MASK]) <<  0;
    ret ^= board_t(row_right_table[(static_cast<Board>(board) >> 16) & ROW_MASK]) << 16;
    ret ^= board_t(row_right_table[(static_cast<Board>(board) >> 32) & ROW_MASK]) << 32;
    ret ^= board_t(row_right_table[(static_cast<Board>(board) >> 48) & ROW_MASK]) << 48;
  }
  break;
  }
  return Board(ret);
}