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
    Board board;
    board = board.insert(1, 3).insert(1, 6).insert(1, 13);
    Minimax minimax(BSPLib::ProcId(), BSPLib::NProcs());

    if (BSPLib::ProcId() == 0)
      std::cout << board;

    BSPLib::Sync();

    SearchResult result;

    size_t visitedNodes = 0;

    for (size_t depth = 1; depth < 9; ++depth)
    {
      if (BSPLib::ProcId() == 0)
        std::cout << "\n\n> DEPTH " << depth << "\n";

      result = minimax.think(depth, board, result.bestMove, true);
      visitedNodes += result.visited;

      for (size_t proc = 0; proc != BSPLib::NProcs(); ++proc)
      {
        if (BSPLib::ProcId() == proc)
        {
          // Board example = board;
          for (auto it = result.bestMove.rbegin(); it != result.bestMove.rend(); ++it)
          {
            std::cout << *generator[*it] << '\n';
            // example = generator[*it]->apply(example);
            // std::cout << example << '\n';
          }
          std::cout << "\n#nodes: " << result.visited << "\n";
          std::cout << std::fixed << "Score: " << result.score << "\n\n";
        }
        BSPLib::Sync();
      }


      //   BSPLib::Sync();
      // }

      BSPLib::Sync();
    }

    for (size_t proc = 0; proc != BSPLib::NProcs(); ++proc)
    {
      if (BSPLib::ProcId() == proc)
        std::cout << visitedNodes << '\n';

      BSPLib::Sync();
    }
  }, procs);
}
