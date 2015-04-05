#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SEARCH_H
#define SEARCH_H

#define N 3
#define NxN 16			        /* able to handle any size */
#define DFS 0                   /* depth first search */
#define BFS 1                   /* breadth first search */
#define BEST 2                  /* best first search */
#define BB 3                    /* branch and bound */
#define ASTAR 4                 /* A* search */

//---------------Global Struct-------------
struct node {
  int loc[N+1][N];		
  struct node *next;
  int h_val;
  int g_val;
  int f_val;
};

struct node *start, *goal; // Intitial State - Goal State
int flag; // BFS or DFS or A-STAR

//---------------Function Prototypes----------
void print_a_node(struct node *np);
void print_nodes(struct node *cp);
struct node * initialize(int argc, char **argv);
struct node *expand(struct node *selected);
int nodes_same(struct node * a, struct node * b);
struct node * filter(struct node * hp, struct node * succ);
struct node *merge(struct node *succ,struct node *open,int flag);
int goal_found(struct node *cp,struct node *goal);
#endif
