#include <iostream>
#include "Search.h"
#ifndef MOVE_H
#define MOVE_H

typedef enum{UP, DOWN, LEFT, RIGHT} tile_pos;
struct node * move(struct node *selected, tile_pos position);
#endif
