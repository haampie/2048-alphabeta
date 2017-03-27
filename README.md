Final project for a course in parallel programming: parallel game tree search for the 2048 game.

The key idea is to perform iterative deepening on the game tree, so that the best move sequence at depth N can be considered first at depth N + 1. This allows good alpha-beta pruning without communication in a distributed memory setting.
