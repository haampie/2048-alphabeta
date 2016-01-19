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
  size_t maxDepth = (argc >= 2 ? std::stoul(argv[1]) : 9);
  initTables();
  Board board;
  board = board.insert(1, 3).insert(1, 6).insert(1, 13);

  Minimax minimax;

  std::cout << board;

  SearchResult result;

  size_t visitedNodes = 0;

  for (size_t depth = 1; depth < maxDepth; ++depth)
  {
    std::cout << "\n\n> DEPTH " << depth << "\n";

    result = minimax.think(depth, board, result.bestMove, true);
    visitedNodes += result.visited;

    // Board example = board;
    for (auto it = result.bestMove.rbegin(); it != result.bestMove.rend(); ++it)
      if (*it != nullptr)
        std::cout << **it << '\n';

    std::cout << "\n#nodes: " << result.visited << "\n";
    std::cout << std::fixed << "Score: " << result.score << "\n\n";

  }

  std::cout << "TOTAL VISITED: " << visitedNodes << '\n';
}
