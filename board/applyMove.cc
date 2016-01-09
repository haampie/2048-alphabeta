#include "board.h"
#include "../heuristics/tables.h"

Board Board::applyMove(Move move) const
{
  board_t ret = d_board;

  switch (move)
  {
  case TOP:
  {
    board_t t = transpose();
    ret ^= col_up_table[(t >>  0) & ROW_MASK] <<  0;
    ret ^= col_up_table[(t >> 16) & ROW_MASK] <<  4;
    ret ^= col_up_table[(t >> 32) & ROW_MASK] <<  8;
    ret ^= col_up_table[(t >> 48) & ROW_MASK] << 12;
  }
  break;
  case BOTTOM:
  {
    board_t t = transpose();
    ret ^= col_down_table[(t >>  0) & ROW_MASK] <<  0;
    ret ^= col_down_table[(t >> 16) & ROW_MASK] <<  4;
    ret ^= col_down_table[(t >> 32) & ROW_MASK] <<  8;
    ret ^= col_down_table[(t >> 48) & ROW_MASK] << 12;
  }
  break;
  case LEFT:
  {
    ret ^= board_t(row_left_table[(d_board >>  0) & ROW_MASK]) <<  0;
    ret ^= board_t(row_left_table[(d_board >> 16) & ROW_MASK]) << 16;
    ret ^= board_t(row_left_table[(d_board >> 32) & ROW_MASK]) << 32;
    ret ^= board_t(row_left_table[(d_board >> 48) & ROW_MASK]) << 48;
  }
  break;
  case RIGHT:
  {
    ret ^= board_t(row_right_table[(d_board >>  0) & ROW_MASK]) <<  0;
    ret ^= board_t(row_right_table[(d_board >> 16) & ROW_MASK]) << 16;
    ret ^= board_t(row_right_table[(d_board >> 32) & ROW_MASK]) << 32;
    ret ^= board_t(row_right_table[(d_board >> 48) & ROW_MASK]) << 48;
  }
  break;
  }
  return Board(ret);
}