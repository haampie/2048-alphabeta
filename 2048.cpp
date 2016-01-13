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
    board = board.insert(1, 3)
            .insert(1, 6)
            .insert(1, 13);

    Minimax minimax(BSPLib::ProcId(), BSPLib::NProcs());


    if (BSPLib::ProcId() == 0)
      std::cout << board;

    SearchResult result;

    size_t visitedNodes = 0;

    for (size_t depth = 1; depth < 9; ++depth)
    {
      if (BSPLib::ProcId() == 0)
        std::cout << "\n\n-- Searching at depth " << depth << "\n";

      result = minimax.think(depth, board, result.bestMove, true);
      visitedNodes += result.visited;

      if (BSPLib::ProcId() == 0)
        for (auto it = result.bestMove.rbegin(); it != result.bestMove.rend(); ++it)
          std::cout << **it << '\n';

      BSPLib::Sync();
    }

    if (BSPLib::ProcId() == 0)
      std::cout << "VISITED: " << visitedNodes << '\n';
  }, procs);
}
