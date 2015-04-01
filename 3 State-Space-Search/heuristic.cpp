#include "Heuristic.h"
#include "Search.h"
#include "Move.h"
int find_index(struct node * tile, table_index idx, int lookup){
    switch (idx){
           case ROW:  
                
                   for (unsigned int i=0; i< N; i++){
                       for (unsigned int j=0; j<N; j++){
                           if (tile->loc[i][j]==lookup) return i;
                       }
                   }
                   break;
                   
           case COL:  
                   for (unsigned int i=0; i< N; i++){
                       for (unsigned int j=0; j<N; j++){
                           if (tile->loc[i][j]==lookup) return j;
                       }
                   }
                   break;         
    }
}

int calc_manhattan(struct node * tile, struct node * goal){
     int manhattan_cnt=0;
     int goal_row=0; // Row Position in Goal  that you need to be
     int goal_col=0; // Col Position in Goal that you need to be
     
     for (unsigned int i=0; i<N; i++){
         for (unsigned int j=0; j<N; j++){
             goal_row=find_index(goal, ROW, tile->loc[i][j]);
             goal_col=find_index(goal, COL, tile->loc[i][j]);
             manhattan_cnt+=(abs(goal_row-i)+abs(goal_col-j));
         }
     }       
     return manhattan_cnt; 
}

struct node * sort_merge(struct node * succ, struct node * open){
     struct node * tp, *sorted, *tmp_sorted;
     int lst_count;
     // UNSORTED MERGE
     tp=succ;
     while(tp->next)tp=tp->next;
     tp->next=open;
     // Sorting the UNSORTED list (Insertion Sort) ** NOT USING INSERTION SORT because no PREV Pointer
     sorted=NULL;
     tmp_sorted=sorted;
     tp=succ;
     lst_count=list_count(succ);
     //---------------------------------------------------------------------
     sorted=min_node(succ);
     sorted->next=NULL;
     tp=sorted;
     for (unsigned i=0;i<lst_count-1; i++){
         tmp_sorted=min_node(succ);
         tp->next=tmp_sorted;
         tp=tp->next;
         tp->next=NULL;
     }
     return sorted;
     //----------------------------------------------------------------------
}

int list_count(struct node * lst){
    int cnt=1;
    while(lst->next){
                     cnt++;
                     lst=lst->next;
    }
    return cnt;
}

struct node * min_node(struct node *& lst){ // Will return the index the min_val in a linked list
    struct node * tp=lst;
    struct node * cp=lst;
    struct node * ret_tile=new node;
    int min_index=-1;
    int min_val=lst->f_val;
    int cnt=0;
    
    while(tp->next){
             if(tp->f_val<min_val){
                                   min_val=tp->f_val;
                                   min_index=cnt;
             }
             cnt++;
             tp=tp->next;          
    }
    tp=lst;
    tp=tp->next;
    
    if (min_index==-1){
       lst=lst->next;
       cp->next=NULL;
       return cp;        
    }
    
    for (unsigned int i=0; i<min_index-1; i++){
        tp=tp->next;
        cp=cp->next;
    }
    cp->next=tp->next;
    tp->next=NULL;
    return tp;    
}

int get_gval(struct node * parent){
    return parent->g_val+1;
}


