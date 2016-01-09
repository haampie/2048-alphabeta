#include "search.h"
#include "../movegenerator/movegenerator.h"
#include <limits>
#include <string>

float Minimax::search(Board board, size_t depth,
                      float alpha, float beta,
                      bool maximizing)
{
  auto movelist = generator.viable(board, maximizing);

  if (depth == 0 || movelist.size() == 0)
  {
    // std::cout << board.heuristicScore() << '\n';
    return maximizing ? board.heuristicScore() : -board.heuristicScore();
  }

  float best = -1000000000;
  Move *bestMove = nullptr;

  for (auto &move : movelist)
  {
    float score = -search(move->apply(board), depth - 1, -beta, -alpha, not maximizing);

    if(depth == d_depth)
      std::cout << score;

    if (score > best)
    {
      if(depth == d_depth)
        std::cout << " (picked this " << (maximizing ? "max)" : "min)");

      bestMove = move;
      best = score;
    }
    if(depth == d_depth)
      std::cout << '\n';

    if (score > alpha)
      alpha = score;

    if (beta <= alpha)
      break;
  }

  if (depth == d_depth)
    d_bestMove = bestMove;

  return best;
}
