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

  auto movelist = generator.viable(
                    board,
                    maximizing,
                    PV && d_pv.size() > d_depth - depth
                    ? d_pv[d_pv.size() - d_depth + depth - 1]
                    : 100
                  );
  // auto movelist = generator.viable(board, maximizing, nullptr);

  // Reached final depth
  if (depth == 0 or movelist.size() == 0)
    return maximizing ? board.heuristicScore() : -board.heuristicScore();

  // Principal variation
  if (PV)
  {
    // localMax[pid] = max value found by processor pid
    // localMax[d_nprocs] = PV value found by ALL procs
    std::vector<float> localMax(d_nprocs + 1, -1000000000);
    BSPLib::PushContainer(localMax);
    BSPLib::Sync();

    // Search the PV sequentially
    localMax[d_proc] = -search(generator[movelist[0]]->apply(board), depth - 1, -beta, -alpha, not maximizing, true);

    // Store the PV value as the last index which makes
    // determining the global maximum easy
    localMax[d_nprocs] = localMax[d_proc];

    // Use the alpha value
    alpha = localMax[d_proc];

    // Copy the best move sequence since the PV move must
    // be the best so far as it is first traversed through
    if (depth > 1)
    {
      auto it = d_bestMoves[depth - 2].begin();
      std::copy(it, it + depth - 1, d_bestMoves[depth - 1].begin());
    }
    d_bestMoves[depth - 1][depth - 1] = movelist[0];

    // Search the younger brothers in parallel
    // Find the local optimum first

    if(d_proc == 0)
      std::cout << board << '\n';

    for (size_t proc = 0; proc != d_nprocs; ++proc)
    {
      if (d_proc == proc)
        for (auto move = movelist.begin() + d_proc + 1; move < movelist.end(); move += d_nprocs)
          std::cout << depth << "] processor " << proc << " checks " << *generator[*move] << "\n";

      BSPLib::Sync();
    }

    for (auto move = movelist.begin() + d_proc + 1; move < movelist.end(); move += d_nprocs)
    {
      float score = -search(generator[*move]->apply(board), depth - 1, -beta, -alpha, not maximizing, false);

      if (score > localMax[d_proc])
      {
        // Update the best move score found
        localMax[d_proc] = score;

        // Copy the best move sequence
        if (depth > 1)
        {
          auto it = d_bestMoves[depth - 2].begin();
          std::copy(it, it + depth - 1, d_bestMoves[depth - 1].begin());
        }
        d_bestMoves[depth - 1][depth - 1] = *move;
      }

      // Update alpha
      if (score > alpha)
        alpha = score;

      // No need to check for cut-offs at PV-level
    }

    // If a younger brother is better than the PV,
    // communicate your best value to all processors;
    // otherwise let others assume it is -inf
    if (localMax[d_proc] > localMax[d_nprocs])
      for (size_t proc = 0; proc != d_nprocs; ++proc)
        if (proc != d_proc)
          BSPLib::PutIterator(proc, localMax.begin(), d_proc, 1);

    // And let's actually send them.
    BSPLib::Sync();
    BSPLib::PopContainer(localMax);

    // First assume the PV is the global maximum and then
    // try to falsify it. If it cannot be falsified, then
    // there is no need to communicate the optimal move
    // sequence
    float globalMax = localMax[d_nprocs];
    size_t bestProc = d_nprocs;

    // Find the global best
    for (size_t proc = 0; proc != d_nprocs; ++proc)
    {
      if (localMax[proc] > globalMax)
      {
        globalMax = localMax[proc];
        bestProc = proc;
      }
    }

    // If global max is found on another processor, sync
    // the optimal sequence...
    if (bestProc != d_nprocs)
    {
      BSPLib::PushContainer(d_bestMoves[depth - 1]);
      BSPLib::Sync();

      // Broadcast if you have the best sequence
      if (bestProc == d_proc)
        for (size_t proc = 0; proc != d_nprocs; ++proc)
          if (proc != d_proc)
            BSPLib::PutContainer(proc, d_bestMoves[depth - 1]);

      BSPLib::Sync();
      BSPLib::PopContainer(d_bestMoves[depth - 1]);
    }

    return globalMax;
  }
  else // Not on the PV: search on one processor
  {
    float best = -1000000000;
    for (auto &move : movelist)
    {
      float score = -search(generator[move]->apply(board), depth - 1, -beta, -alpha, not maximizing, false);

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

  // To prevent a compiler warning...
  return 0.0;
}