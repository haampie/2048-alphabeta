#include "movegenerator.h"

MoveGenerator::~MoveGenerator()
{
  for (auto &move : d_slides)
    delete move;

  for (auto &move : d_inserts)
    delete move;
}