#include "Search.h"
#include "Heuristic.h"


int goal_found(struct node *cp,struct node *goal){ 
    // Comparing IF NODE == GOAL
	while(cp){
		if (nodes_same(cp,goal)){
			return 1;
		}else{
			cp=cp->next;
		}	
	}
}


struct node *merge(struct node *succ,struct node *open,int flag) {
    // Merging the NODES based on the SEARCH STRATEGY    
    // DFS will always expand the successors first. 
    // BFS will always finish LEVEL by LEVEL
    // A-Star (intelligent) search will look for the BEST possible node sorted by f() value
    struct node *csucc,*copen;
    if (flag==DFS) {	/* attach to the front: succ -> ... -> open */
        if (succ==NULL) return open;	
        csucc=succ;
        while(succ->next){
	    	succ=succ->next;	
        }
	    succ->next=open;
	    return csucc;
   }else if (flag==BFS) { /* attach to the end: open -> ... -> succ */
	    if (open==NULL) return succ;
        csucc=open;
        while(csucc->next){
             csucc=csucc->next;	
        }
        csucc->next=succ;
        return open;
   }else {	      /* Best first: insert in asc order of h value */
        return sort_merge(succ,open);
   }
}


struct node * filter(struct node * hp, struct node * succ){
// Given two lists of PUZZLES (A,B) return ONLY the puzzles in B that are NOT already in A. 
	int dup_found=0;	
	struct node * current=hp;
	struct node * tp;
	struct node * unique=NULL;

	while(succ){
		while(current){
			if(!nodes_same(current,succ)){
				current=current->next;			
			}else{
				dup_found=1;
				break;			
			}
		}			
		if (!dup_found){
			if (unique==NULL){
				unique=succ;
				succ=succ->next;
				unique->next=NULL;			
			}else{
				tp=unique;	
				while(tp->next){
					tp=tp->next;
				}
				tp->next=succ;
				tp=tp->next;
				succ=succ->next;
				tp->next=NULL;
			}
			
		}else{
			dup_found=0;
			succ=succ->next;
		}			
		current=hp;	
	}
    return unique;	
} 


int nodes_same(struct node * a, struct node * b) {
    // Comparing TWO Puzzles
  	int i=0, j=0;
  	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			if (a->loc[i][j]!=b->loc[i][j]) return 0;		
		}	
	}
	return 1;  
}


struct node *expand(struct node *selected) {
    // Given a PUZZLE, generate the successors.
    /*              (left)  (right)    So on
       ex: 1 2 3    1 2 3    1 2 3     ......
           4 0 5    0 4 5    4 5 0     ......
           6 7 8    6 7 8    6 7 8
    
    Return Successors---> (up)-->(down)->(left)-->(right)--->NULL
    
    */   
	struct node * up=move(selected, UP);
	struct node * down=move(selected, DOWN);
	struct node * left=move(selected, LEFT);
	struct node * right=move(selected, RIGHT);
	
	
	up->next=down;
	down->next=left;
	left->next=right;
	right->next=NULL;
	return up;
}

void print_a_node(struct node *np) {
    int i,j, (*mp)[N];
    mp = np->loc;
    for (i=0;i<N;i++) {
       for (j=0;j<N;j++) printf("%2d ",np->loc[i][j]);
       printf("\n");
    }
    std::cout<<"FVAL: "<<np->f_val<<" \n";
    printf("\n");
}

struct node * initialize(int argc, char **argv){
    int i,j,k,idx;
    struct node *tp;

    tp=(struct node *) malloc(sizeof(struct node));
    idx = 1;
    for (j=0;j<N;j++)
       for (k=0;k<N;k++) tp->loc[j][k]=atoi(argv[idx++]);
    for (k=0;k<N;k++) tp->loc[N][k]=0;	/* set f,g,h of initial state to 0 */
    tp->next=NULL;
    start=tp;
    printf("initial state\n"); print_a_node(start);

    tp=(struct node *) malloc(sizeof(struct node));
    idx = 1;
    for (j=0;j<N;j++)
      for (k=0;k<N;k++) tp->loc[j][k] = idx++;
    tp->loc[N-1][N-1] = 0;	      /* empty tile=0 */
    for (k=0;k<N;k++) tp->loc[N][k]=0;	/* set f,g,h of goal state to 0 */
    tp->next=NULL;
    //tp->h_val=calc_manhattan(tp,goal);
    goal=tp; 
    printf("goal state\n"); print_a_node(goal);

    
    start->h_val=calc_manhattan(start,goal);
    start->g_val=0;
    start->f_val=start->h_val+start->g_val;
    
    goal->h_val=0;
    goal->g_val=0;
    goal->f_val=0;
    
    return start;	
}

void print_nodes(struct node *cp) {
    while (cp) {
        print_a_node(cp);
        cp=cp->next;
    }
}
