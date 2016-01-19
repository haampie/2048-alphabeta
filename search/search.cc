#include "bsp/bsp.h"
#include "search.h"
#include "../movegenerator/movegenerator.h"
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

float Minimax::search(Board board, size_t depth, float alpha, float beta, bool maximizing, bool PV)
{
  ++d_visited;

  if (depth == 0)
    return maximizing ? board.heuristicScore() : -board.heuristicScore();

  auto movelist = generator.viable(
                    board,
                    maximizing,
                    PV && d_pv.size() > d_depth - depth
                    ? d_pv[d_pv.size() - d_depth + depth - 1]
                    : nullptr
                  );
  // Reached final depth
  if (movelist.size() == 0)
    return maximizing ? board.heuristicScore() : -board.heuristicScore();

  // There are moves, so start searching.

  if (PV)
  {
    // New PV move
    float best = -search(movelist[0]->apply(board), depth - 1, -beta, -alpha, not maximizing, true);
    alpha = best;

    // Copy the best move sequence
    if (depth > 1)
    {
      auto it = d_bestMoves[depth - 2].begin();
      std::copy(it, it + depth - 1, d_bestMoves[depth - 1].begin());
    }
    d_bestMoves[depth - 1][depth - 1] = movelist[0];

    // Search the remaing bits
    for (size_t idx = 1, max = movelist.size(); idx < max; ++idx)
    {
      float score = -search(movelist[idx]->apply(board), depth - 1, -beta, -alpha, not maximizing, false);

      if (score > best)
      {
        // Set the new best move value
        best = score;

        // Copy the best move sequence
        if (depth > 1)
        {
          auto it = d_bestMoves[depth - 2].begin();
          std::copy(it, it + depth - 1, d_bestMoves[depth - 1].begin());
        }
        d_bestMoves[depth - 1][depth - 1] = movelist[idx];
      }

      if (score > alpha)
        alpha = score;

      if (beta <= alpha)
        break;
    }
    return best;
  }
  else
  {
    float best = -1000000000;
    for (auto &move : movelist)
    {
      float score = -search(move->apply(board), depth - 1, -beta, -alpha, not maximizing, false);

      if (score > best)
      {
        // Set the new best move value
        best = score;

        // Copy the best move sequence
        if (depth > 1)
        {
          auto it = d_bestMoves[depth - 2].begin();
          std::copy(it, it + depth - 1, d_bestMoves[depth - 1].begin());
        }
        d_bestMoves[depth - 1][depth - 1] = move;
      }

      if (score > alpha)
        alpha = score;

      if (beta <= alpha)
        break;
    }
    return best;
  }
}