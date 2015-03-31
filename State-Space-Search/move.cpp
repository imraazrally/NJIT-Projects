
struct node * move(struct node *selected, tile_pos position){
       int curr_row,  curr_col;
       //Copy the SELECTED Successor into a NEW tile which will be RETURNED
       struct node * ret_tile=new node;
       
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
                             if (curr_row!=0){ 
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
       return ret_tile;   
}
