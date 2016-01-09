#include "search.h"
#include "../movegenerator/movegenerator.h"
#include <limits>

SearchResult Minimax::think(Board &board, bool maximizing)
{
  if (generator.viable(board, maximizing).size() == 0)
    return SearchResult(nullptr, 0);

  float result = search(board, d_depth, -1000000000,
                        1000000000, maximizing);

  return SearchResult(d_bestMove, result);
}
