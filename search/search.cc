#include "bsp/bsp.h"
#include "search.h"
#include "../movegenerator/movegenerator.h"
#include <limits>
#include <string>
#include <vector>

float Minimax::search(Board board, size_t depth, float alpha, float beta, bool maximizing, bool PV)
{
  ++d_visited;
  auto movelist = generator.viable(board, maximizing);

  // Reached final depth
  if (depth == 0 or movelist.size() == 0)
    return maximizing ? board.heuristicScore() : -board.heuristicScore();

  // Go over the moves
  float best = -1000000000;
  Move *bestMove = nullptr;

  // Principal variation
  if (PV)
  {
    // PVSplit: this is the PV-move
    std::vector<float> scores(movelist.size(), 0.0);
    BSPLib::PushContainer(scores);
    BSPLib::Sync();

    scores[0] = -search(movelist[0]->apply(board), depth - 1, -beta, -alpha, not maximizing, true);
    alpha = scores[0];

    // Go over the elder brothers
    for (size_t idx = d_proc + 1, nmoves = movelist.size(); idx < nmoves; idx += d_nprocs)
    {
      scores[idx] = -search(movelist[idx]->apply(board), depth - 1, -beta, -alpha, not maximizing, false);

      for (size_t proc = 0; proc != d_nprocs; ++proc)
        if (proc != d_proc)
          BSPLib::PutIterator(proc, scores.begin(), idx, 1);
    }

    // for(size_t idx = 0; idx != d_nprocs; ++idx)
    // {
    //   if(idx == d_proc)
    //     std::cout << idx << ": " << d_visited << '\n';
    //   BSPLib::Sync();
    // }

    BSPLib::Sync();

    // Find the global best (should be done by going through local best scores)
    for (size_t idx = 0; idx != movelist.size(); ++idx)
    {
      if (scores[idx] > best)
      {
        bestMove = movelist[idx];
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
        best = score;

      if (score > alpha)
        alpha = score;

      if (beta <= alpha)
        break;
    }
  }

  if (depth == d_depth)
    d_bestMove = bestMove;

  return best;
}