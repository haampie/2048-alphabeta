#ifndef MOVEGEN_INCLUDE
#define MOVEGEN_INCLUDE

#include <vector>
#include "../move/move.h"

class MoveGenerator
{
  std::vector<Move*> d_slides;
  std::vector<Move*> d_inserts;

public:
  std::vector<Move*> viable(Board &board, bool maximizing) const;
  MoveGenerator();
  ~MoveGenerator();
};

// For now, make the generator global.
extern MoveGenerator generator;

#endif