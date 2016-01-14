#ifndef INCLUDE_SEARCH
#define INCLUDE_SEARCH

#include "../board/board.h"
#include "../move/move.h"
#include <vector>

struct SearchResult
{
  SearchResult()
  : score(0.0), visited(0)
  {}
  
  SearchResult(std::vector<size_t> &best, float bestScore, size_t nodes)
    : bestMove(best), score(bestScore), visited(nodes)
  {}

  std::vector<size_t> bestMove;
  float score;
  size_t visited;
};

class Minimax
{
  size_t d_depth;
  size_t d_proc;
  size_t d_nprocs;
  size_t d_visited;
  std::vector<std::vector<size_t>> d_bestMoves;
  std::vector<size_t> d_pv;
  bool d_maximizing;
  Move *d_bestMove;
  float search(Board board, size_t depth, float alpha, float beta, bool maximizing, bool PV);
public:
  Minimax(size_t processor, size_t num_processors);
  SearchResult think(size_t depth, Board &board, std::vector<size_t> const &pv, bool maximizing);
};

#endif