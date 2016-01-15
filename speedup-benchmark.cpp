#define BSP_DISABLE_LEGACY

#include "bsp/bsp.h"
#include "board/board.h"
#include "search/search.h"
#include "move/move.h"
#include "heuristics/tables.h"
#include "movegenerator/movegenerator.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char **argv)
{
  size_t procs = (argc >= 2 ? stoul(argv[1]) : BSPLib::NProcs());

  BSPLib::Execute([]()
  {
    initTables();

    size_t const maxDepth = 11;
    size_t const NProcs = BSPLib::NProcs();
    size_t const ProcId = BSPLib::ProcId();
    chrono::duration<double> total;

    Minimax minimax(ProcId, NProcs);

    for (size_t turn = 0; turn < 2; ++turn)
    {
      bool maximize = (turn == 0);

      // Create different boards
      for (size_t pos1 = 0; pos1 < 16; ++pos1)
      {
        for (size_t pos2 = 0; pos2 < 15; ++pos2)
        {
          BSPLib::Sync();
          Board board;
          board = board.insert(1, pos1).insert(2, pos2);
          SearchResult result;

          if (ProcId == 0)
          {
            cout << (maximize ? "Maximize\n" : "Minimize\n");
            cout << board;
          }

          chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();
          for (size_t depth = maxDepth - 1; depth < maxDepth; ++depth)
          {
            result = minimax.think(depth, board, result.bestMove, maximize);
          }
          chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
          total += chrono::duration_cast<chrono::duration<double>>(end - begin);
        }
      }
    }

    if (ProcId == 0)
      cout << total.count() << endl;
  }, procs);
}
