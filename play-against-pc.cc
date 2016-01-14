#define BSP_DISABLE_LEGACY

#include "bsp/bsp.h"
#include "board/board.h"
#include "search/search.h"
#include "move/move.h"
#include "heuristics/tables.h"
#include "movegenerator/movegenerator.h"

#include <iostream>
#include <iomanip>
#include <string>

int main(int argc, char **argv)
{
  size_t procs = (argc >= 2 ? std::stoul(argv[1]) : BSPLib::NProcs());

  BSPLib::Execute([]()
  {
    initTables();

    size_t const maxDepth = 10;
    size_t const NProcs = BSPLib::NProcs();
    size_t const ProcId = BSPLib::ProcId();

    Board board;
    board = board.insert(4, 0).insert(3, 0).insert(2, 1);

    if (ProcId == 0)
      std::cout << board;

    Minimax minimax(ProcId, NProcs);
    SearchResult result;

    while (true)
    {
      board_t copy = board;
      BSPLib::Push(copy);
      BSPLib::Sync();
      if (ProcId == 0)
      {
        char move;
        std::cin >> move;
        switch (move)
        {
        case 'w':
          copy = Slide(Slide::TOP).apply(copy);
          break;
        case 'a':
          copy = Slide(Slide::LEFT).apply(copy);
          break;
        case 's':
          copy = Slide(Slide::BOTTOM).apply(copy);
          break;
        case 'd':
          copy = Slide(Slide::RIGHT).apply(copy);
          break;
        }

        for (size_t proc = 1; proc != NProcs; ++proc)
          BSPLib::Put(proc, copy);
      }

      BSPLib::Sync();
      BSPLib::Pop(copy);

      board = Board(copy);

      if (ProcId == 0)
        std::cout << board << std::endl;

      // Iterative deepening.
      for (size_t depth = 1; depth < maxDepth; ++depth)
        result = minimax.think(depth, board, result.bestMove, false);

      if (result.bestMove.size() == 0)
        break;

      board = generator[*result.bestMove.rbegin()]->apply(board);

      if (ProcId == 0)
        std::cout << board;

      BSPLib::Sync();
    }
  }, procs);
}
