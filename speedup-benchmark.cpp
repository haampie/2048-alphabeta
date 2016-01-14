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

    size_t maxDepth = 11;
    size_t const NProcs = BSPLib::NProcs();
    size_t const ProcId = BSPLib::ProcId();

    Board board;
    board = board.insert(2, 0).insert(1, 7);

    Minimax minimax(ProcId, NProcs);
    SearchResult result;

    for (size_t ply = 0; ply != 10000; ++ply)
    {
      // Iterative deepening.
      bool maximize = (ply % 2 == 0);
      maxDepth = maximize ? 6 : 3;
      for (size_t depth = maxDepth-1; depth < maxDepth; ++depth)
      {
        // std::cout << "depth = " << depth << std::endl;
        result = minimax.think(depth, board, result.bestMove, maximize);
      }

      if (result.bestMove.size() == 0)
      {
        if (ProcId == 0)
          std::cout << "Ply: " << ply << std::endl << board;
        break;
      }

      board = generator[*result.bestMove.rbegin()]->apply(board);
      
      if (ProcId == 0)
        std::cout << board;

      BSPLib::Sync();
    }
  }, procs);
}
