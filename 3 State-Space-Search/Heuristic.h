#include <iostream>
#include "Search.h"
#include "Move.h"

#ifndef HEURISTIC_H
#define HEURISTIC_H

typedef enum{ROW, COL} table_index;
int find_index(struct node * tile, table_index idx, int lookup);
int calc_manhattan(struct node * tile, struct node * goal);
int get_gval(struct node * parent);
struct node * sort_merge(struct node * succ, struct node * open);
struct node * min_node(struct node *& lst);
int list_count(struct node * lst);
#endif
