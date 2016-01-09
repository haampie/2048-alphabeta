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
  Minimax minimax(8);

  board = board.insert(2, 0).insert(1, 0);
  std::cout << board;

  for (size_t ply = 0; ply != 3000; ++ply)
  {
    auto result = minimax.think(board, ply % 2 == 0);

    std::cout << "Move " << ply + 1 << " visited "
              << result.visited << " nodes\n" << board;

    if (not result.bestMove)
    {
      std::cout << "Game over...\n";
      break;
    }

    board = result.bestMove->apply(board);
  }
  std::cout << board;

  // char key;
  // while (std::cin >> key)
  // {
  //   switch (key)
  //   {
  //   case 'a':
  //     board = Slide(Slide::LEFT).apply(board);
  //     break;
  //   case 's':
  //     board = Slide(Slide::BOTTOM).apply(board);
  //     break;
  //   case 'd':
  //     board = Slide(Slide::RIGHT).apply(board);
  //     break;
  //   case 'w':
  //     board = Slide(Slide::TOP).apply(board);
  //     break;
  //   case 'q':
  //     return 1;
  //   }

  //   auto result = minimax.think(board, false);
  //   if (not result.bestMove)
  //   {
  //     std::cout << "Game over...\n";
  //     break;
  //   }
  //   board = result.bestMove->apply(board);
  //   std::cout << "Visited " << result.visited << " nodes\n"
  //             << board;
  // }
}