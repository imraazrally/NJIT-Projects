#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Search.h"
#include "Move.h"
#include "Move.cpp"
#include "Heuristic.h"


int main(int argc, char **argv)
{	 
   int iter=0;
   struct node *tsucc,*csucc,*copen,*topen,*open,*closed,*succ;
   open=closed=succ=NULL;
   start=initialize(argc, argv); // Initializing the START and GOAL Nodes.
   open=start;                  
   succ=expand(start);           // In the beginning, OPEN only contains the START node. So, Expand it.	
   while (open!=NULL) {
        copen=open;
      	open=open->next;
       	succ=expand(copen);        // Create Successors by expanding Node from OPEN
        succ=filter(open,succ);   // Check to see if any of the successors already exist in OPEN
        succ=filter(closed,succ); // Check to see if any of the successors already exist in CLOSED
	    if (goal_found(succ,goal)) break;
	    if (succ!=NULL) open=merge(succ,open,ASTAR); // Connect the SUCCESSORS with the PARENTS
	    copen->next=closed;       //Move the current node we just expanded to CLOSED 
        closed=copen;		
        iter++;
   }
   printf("%d iterations\n",iter);
   return 0;				
}


