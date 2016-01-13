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

  auto movelist = generator.viable(board, maximizing, PV && d_pv.size() > d_depth - depth ? d_pv[d_pv.size() - d_depth + depth - 1] : nullptr);
  // auto movelist = generator.viable(board, maximizing, nullptr);

  // Reached final depth
  if (depth == 0 or movelist.size() == 0)
    return maximizing ? board.heuristicScore() : -board.heuristicScore();

  // Go over the moves
  float best = -1000000000;

  // Principal variation
  if (PV)
  {
    std::vector<float> scores(d_nprocs + 1, -1000000000);
    BSPLib::PushContainer(scores);
    BSPLib::Sync();

    size_t bestMove = 0;

    // Search the PV sequentially
    scores[0] = -search(movelist[0]->apply(board), depth - 1, -beta, -alpha, not maximizing, true);
    alpha = scores[0];

    // Search the elder brothers in parallel
    for (size_t idx = 0, nmoves = movelist.size(); d_proc + 1 + idx * d_nprocs < nmoves; idx += d_nprocs)
    {
      Move const * const move = d_proc + 1 + idx * d_nprocs;
      scores[idx] = -search(movelist[moveIndex]->apply(board), depth - 1, -beta, -alpha, not maximizing, false);

      // Store the current best move (can be removed...)
      bestMove = movelist[idx];

      // Copy the best move sequence
      if (depth > 1)
      {
        auto it = d_bestMoves[depth - 2].begin();
        std::copy(it, it + depth - 1, d_bestMoves[depth - 1].begin());
      }
      d_bestMoves[depth - 1][depth - 1] = movelist[idx];

      // for (size_t proc = 0; proc != d_nprocs; ++proc)
      //   if (proc != d_proc)
      //     BSPLib::PutIterator(proc, scores.begin(), idx, 1);
    }

    BSPLib::Sync();

    // Find the global best (should be done by going through local best scores)
    for (size_t idx = 0; idx != movelist.size(); ++idx)
    {
      if (scores[idx] > best)
      {
        // Set the new best move value
        best = scores[idx];
      }
    }

    BSPLib::PopContainer(scores);
  }
  else // Not on the PV: search on one processor
  {
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
  }

  return best;
}