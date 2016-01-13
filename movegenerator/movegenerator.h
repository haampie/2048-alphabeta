#ifndef MOVEGEN_INCLUDE
#define MOVEGEN_INCLUDE

#include <vector>
#include "../move/move.h"

class MoveGenerator
{
  std::vector<Move*> d_slides;
  std::vector<Move*> d_inserts;

public:
  std::vector<Move*> viable(Board const &board, bool maximizing, Move *prefer) const;
  MoveGenerator();
  ~MoveGenerator();
};

// For now, make the generator global.
extern MoveGenerator generator;

#endif