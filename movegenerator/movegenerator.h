#ifndef MOVEGEN_INCLUDE
#define MOVEGEN_INCLUDE

#include <vector>
#include "../move/move.h"

class MoveGenerator
{
  // This is to quickly initialize the insertion moves
  std::vector<char> d_insertsCopyMachine; 
  std::vector<Move*> d_moves;

public:
  Move *operator[](int i) const;
  std::vector<char> viable(Board const &board, bool maximizing, char prefers) const;
  MoveGenerator();
  ~MoveGenerator();
};

inline Move *MoveGenerator::operator[](int i) const
{
  return d_moves[i];
}

// For now, make the generator global.
extern MoveGenerator generator;

#endif