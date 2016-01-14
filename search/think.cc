#include "search.h"
#include "../movegenerator/movegenerator.h"
#include <limits>

SearchResult Minimax::think(size_t depth, Board &board, std::vector<size_t> const &pv, bool maximizing)
{
  d_depth = depth;
  d_visited = 0;
  d_pv = pv;

  std::vector<Move*> nullmove;

  // Check if there is at least one move available
  if (generator.viable(board, maximizing, 100).size() == 0)
    return SearchResult();

  // Initialize the best move sequence tables
  d_bestMoves.resize(depth);

  for (size_t idx = 0; idx != depth; ++idx)
    d_bestMoves[idx].resize(idx + 1, 100);

  // Start searching!
  float result = search(board, d_depth, -1000000000,
                        1000000000, maximizing, true);

  return SearchResult(d_bestMoves[depth-1], result, d_visited);
}
