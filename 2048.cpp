#include "board/board.h"
#include "heuristics/tables.h"
#include "search/search.h"
#include "move/move.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "movegenerator/movegenerator.h"

int main()
{
  initTables();
  Board board;
  Minimax minimax(12);

  board = board.insert(1,0).insert(1,2).insert(4,3).insert(6,3);
  board.print();

  for (size_t ply = 0; ply != 3000; ++ply)
  {
    std::cout << "Move " << ply + 1 << '\n';
    bool slide = ply % 2 == 0;
    board.print();
    auto result = minimax.think(board, slide);

    if(not result.bestMove)
    {
      std::cout << "Game over...\n";
      break;
    }

    board = result.bestMove->apply(board);
  }
  board.print();

  // char key;
  // while(std::cin >> key)
  // {
  //   switch(key)
  //   {
  //     case 'a':
  //       board = board.applyMove(Board::LEFT);
  //     break;
  //     case 's':
  //       board = board.applyMove(Board::BOTTOM);
  //     break;
  //     case 'd':
  //       board = board.applyMove(Board::RIGHT);
  //     break;
  //     case 'w':
  //       board = board.applyMove(Board::TOP);
  //     break;
  //   }

  //   auto result = minimax.think(board, false);
  //   board = board.insert(1, result.bestMove);
  //   board.print();
  // }
}