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

    Minimax minimax(ProcId, NProcs);
    SearchResult result;

    for (size_t ply = 0; ply != 1000; ++ply)
    {
      // Iterative deepening.
      for (size_t depth = 1; depth < maxDepth; ++depth)
        result = minimax.think(depth, board, result.bestMove, ply % 2 == 0);

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
