
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

   }
}


struct node * filter(struct node * hp, struct node * succ){
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
  	int i=0, j=0;
  	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			if (a->loc[i][j]!=b->loc[i][j]) return 0;		
		}	
	}
	return 1;  
}


struct node *expand(struct node *selected) {	
	struct node * up=move_up(selected);
	struct node * down=move_down(selected);
	struct node * left=move_left(selected);
	struct node * right=move_right(selected);
	up->next=down;
	down->next=left;
	left->next=right;
	right->next=NULL;
	return up;
}

struct node * move_up(struct node *selected){
	int i=0, j=0, tmp=0, mv_idx;
    struct node*moved=malloc(sizeof(struct node));
    
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			moved->loc[i][j]=selected->loc[i][j];
			if (selected->loc[i][j]==0 && i!=0){
				tmp=selected->loc[i-1][j];
				moved->loc[i-1][j]=selected->loc[i][j];
				moved->loc[i][j]=tmp;			
			}
		}	
	}

	return moved;
}

struct node * move_down(struct node *selected){
	int i=0, j=0, idx=-1;
    struct node*moved=malloc(sizeof(struct node));
	
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){ 
			moved->loc[i][j]=selected->loc[i][j];	
		}	
	}

	for (i=0; i<N; i++){
		for (j=0; j<N; j++){ 
			if (selected->loc[i][j]==0 && i!=N-1){
				moved->loc[i+1][j]=0;
				moved->loc[i][j]=selected->loc[i+1][j];	
			}
		}	
	}

	return moved;
}

struct node * move_left(struct node *selected){
	int i=0, j=0, idx=-1;
    struct node*moved=malloc(sizeof(struct node));

	for (i=0; i<N; i++){
		for (j=0; j<N; j++){
			moved->loc[i][j]=selected->loc[i][j];
			if (selected->loc[i][j]==0 && j!=0){
				moved->loc[i][j-1]=0;
				moved->loc[i][j]=selected->loc[i][j-1];			
			}
		}	
	}
	return moved;
}

struct node * move_right(struct node *selected){
	int i=0, j=0;
	struct node*moved=malloc(sizeof(struct node));
    

	for (i=0; i<N; i++){
		for (j=0; j<N; j++){ 
			moved->loc[i][j]=selected->loc[i][j];	
		}	
	}

	for (i=0; i<N; i++){
		for (j=0; j<N; j++){ 
			if (selected->loc[i][j]==0 && j!=N-1){
				moved->loc[i][j+1]=0;
				moved->loc[i][j]=selected->loc[i][j+1];			
			}
		}	
	}
	moved->next=NULL;
	return moved;
}

void print_a_node(struct node *np) {
    int i,j, (*mp)[N];
    mp = np->loc;
    for (i=0;i<N;i++) {
       for (j=0;j<N;j++) printf("%2d ",np->loc[i][j]);
       printf("\n");
    }
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
    goal=tp; 
    printf("goal state\n"); print_a_node(goal);

   return start;	
}

void print_nodes(struct node *cp) {
    while (cp) {
        print_a_node(cp);
        cp=cp->next;
    }
}
