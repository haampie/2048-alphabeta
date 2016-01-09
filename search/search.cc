#include "search.h"
#include "../movegenerator/movegenerator.h"
#include <limits>
#include <string>

float Minimax::search(Board board, size_t depth,
                      float alpha, float beta,
                      bool maximizing)
{
  ++d_visited;
  auto movelist = generator.viable(board, maximizing);

  // Reached final depth
  if (depth == 0 or movelist.size() == 0)
    return maximizing ? board.heuristicScore() : -board.heuristicScore();

  // Go over the moves
  float best = -1000000000;
  Move *bestMove = nullptr;

  for (auto &move : movelist)
  {
    float score = -search(move->apply(board), depth - 1, -beta, -alpha, not maximizing);

    if (score > best)
    {
      bestMove = move;
      best = score;
    }

    if (score > alpha)
      alpha = score;

    if (beta <= alpha)
      break;
  }

  if (depth == d_depth)
    d_bestMove = bestMove;

  return best;
}
