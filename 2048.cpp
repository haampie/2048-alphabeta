#define BSP_DISABLE_LEGACY

#include "bsp/bsp.h"
#include "board/board.h"
#include "search/search.h"
#include "move/move.h"
#include "heuristics/tables.h"
#include "movegenerator/movegenerator.h"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
  size_t procs = (argc >= 2 ? std::stoul(argv[1]) : BSPLib::NProcs());

  BSPLib::Execute([]()
  {
    initTables();
    Board board;
    board = board.insert(8, 0)
            .insert(8, 0)
            .insert(5, 0)
            .insert(4, 1)
            .insert(5, 1)
            .insert(2, 1)
            .insert(5, 2)
            .insert(2, 2)
            .insert(2, 4)
            .insert(1, 4)
            .insert(1, 4)
            .insert(1, 4);

    Minimax minimax(BSPLib::ProcId(), BSPLib::NProcs());
    std::cout << board;

    for (size_t depth = 3; depth < 11; ++depth)
    {
      std::cout << "\n\n-- Searching at depth " << depth << "--\n";
      auto result = minimax.think(depth, board, true);

      for (auto it = result.bestMove.rbegin(); it != result.bestMove.rend(); ++it)
        std::cout << **it << '\n';

    }

    // for (size_t ply = 0; ply != 3000; ++ply)
    // {
    //   auto result = minimax.think(8, board, ply % 2 == 0);

    //   for (size_t idx = 0; idx != BSPLib::NProcs(); ++idx)
    //   {
    //     if (idx == BSPLib::ProcId())
    //     {
    //       std::cout << "Proc " << idx << " visited "
    //                 << result.visited << '\n';
    //     }
    //     BSPLib::Sync();
    //   }

    //   if (not result.bestMove)
    //   {
    //     std::cout << "Game over...\n";
    //     break;
    //   }

    //   board = result.bestMove->apply(board);

    //   if (BSPLib::ProcId() == 0)
    //     std::cout << *result.bestMove << '\n' << board;

    //   BSPLib::Sync();
    // }

  }, procs);
}

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