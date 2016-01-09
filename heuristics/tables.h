#ifndef TABLES_INCLUDE
#define TABLES_INCLUDE

#include "../types.h"

extern row_t row_left_table[65536];
extern row_t row_right_table[65536];
extern board_t col_up_table[65536];
extern board_t col_down_table[65536];
extern float score_table[65536];
extern float heur_score_table[65536];

void initTables();

#endif