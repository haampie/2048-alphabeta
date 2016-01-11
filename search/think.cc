#include "search.h"
#include "../movegenerator/movegenerator.h"
#include <limits>

SearchResult Minimax::think(size_t depth, Board &board, bool maximizing)
{
  d_depth = depth;
  d_visited = 0;

  if (generator.viable(board, maximizing).size() == 0)
    return SearchResult(nullptr, 0, d_visited);

  float result = search(board, d_depth, -1000000000,
                        1000000000, maximizing, true);

  return SearchResult(d_bestMove, result, d_visited);
}
