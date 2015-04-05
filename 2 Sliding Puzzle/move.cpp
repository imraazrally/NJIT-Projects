#include "Move.h"
#include "Search.h"
#include "Heuristic.h"

struct node * move(struct node *selected, tile_pos position){
       // This function will take as input a TILE and Move the tile UP or DOWN or LEFT or RIGHT.
       // 1) We don't want the original tile to be destroyed. So, First COPY the tile using MALLOC/NEW
       // 2) Perform MOVE operation 
       // 3) Calculate g(), h(), f()
       // 4) Return the Successor 
       
       int curr_row,  curr_col;
       struct node * ret_tile=new node; 
  
       //Copying the PUZZLE to to a new PUZZLE that will be returned after performing the MOVE operation
       for (unsigned i =0; i<N; i++){
           for (unsigned j=0; j<N; j++){
               ret_tile->loc[i][j]=selected->loc[i][j];        
               if (selected->loc[i][j]==0){
                      curr_row=i;
                      curr_col=j; 
               }        
           }
        }
       
              
       switch(position){
                        case UP: 
                             if (curr_row!=0){ // Boundry Check. You can't move UP if you're already on the first row (0th index)
                                ret_tile->loc[curr_row-1][curr_col]=selected->loc[curr_row][curr_col];
                                ret_tile->loc[curr_row][curr_col]=selected->loc[curr_row-1][curr_col];
                             }
                             break;
                        
                        case DOWN:
                             if (curr_row!=N-1){
                                ret_tile->loc[curr_row+1][curr_col]=selected->loc[curr_row][curr_col];
                                ret_tile->loc[curr_row][curr_col]=selected->loc[curr_row+1][curr_col];
                             }
                             break;
                             
                        case LEFT:
                             if (curr_col!=0){
                                ret_tile->loc[curr_row][curr_col-1]=selected->loc[curr_row][curr_col];
                                ret_tile->loc[curr_row][curr_col]=selected->loc[curr_row][curr_col-1];
                             }
                             break;    
                             
                        case RIGHT:
                             if (curr_col!=N-1){
                                ret_tile->loc[curr_row][curr_col+1]=selected->loc[curr_row][curr_col];
                                ret_tile->loc[curr_row][curr_col]=selected->loc[curr_row][curr_col+1];
                             }
                             break;                              
       }   
       
       // Calculating g(), h(), f()
       ret_tile->h_val=calc_manhattan(ret_tile,goal);
       ret_tile->g_val=get_gval(selected);
       ret_tile->f_val=ret_tile->h_val+ret_tile->g_val;
       return ret_tile;   
}
