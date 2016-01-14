#include "movegenerator.h"

MoveGenerator::~MoveGenerator()
{
  for (auto &move : d_moves)
    delete move;
}