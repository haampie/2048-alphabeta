#ifndef INCLUDE_SEARCH
#define INCLUDE_SEARCH

#include "../board/board.h"
#include "../move/move.h"

struct SearchResult
{
  SearchResult(Move *best, float bestScore, size_t nodes)
    : bestMove(best), score(bestScore), visited(nodes)
  {}

  Move *bestMove;
  float score;
  size_t visited;
};

class Minimax
{
  size_t d_depth;
  size_t d_visited;
  bool d_maximizing;
  Move *d_bestMove;
  float search(Board board, size_t depth, float alpha, float beta, bool maximizing);
public:
  Minimax(size_t depth);
  SearchResult think(Board &board, bool maximizing);
};

#endif