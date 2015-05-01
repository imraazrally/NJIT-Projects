#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

#define N 100
#define MASTER 0
#define PRODUCT 0

void exec(int, int*);
int init_lst(int * vector);


int main(int argc, char **argv)
{
   int vector_x[N], vector_y[N]; // TWO Vectors to calculate DOT Product
   init_lst(vector_x);	// Initializing Vectors
   init_lst(vector_y);	// ""

   int startIndex, endIndex;
   double startTime, endTime;
   dotProduct=0;
   //------------setting up MPI()----------------------
   int size, rank;  
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   //------------Start of Parellel Code()--------------
   startTime=MPI_Wtime(); // Remembering Start Time

   startIndex=rank*N/size;
   endIndex=startIndex+(N/size)-1;
   
   int dotProducts[size]; // Saving the Dot Product calculated by each core;  
   int i;
   int finalProduct=0;    // Final value after merging the dotProducts of all cores
    //---------------------------------------------------
   if (rank==MASTER){
	finalProduct=dot_product(vector_x,vector_y,startIndex, endIndex); // Add my product to the final product;
	for (i=1; i<size; i++){
		MPI_Recv(dotProducts+i,1,MPI_INT,i, PRODUCT, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Wait until each core is complete
		finalProduct+=dotProducts[i]; // add each core's output to the finalProduct
	}
   }else{
	// If I'm worker, calculate dot product and send it to master
	dotProduct=dot_product(vector_x,vector_y,startIndex, endIndex);
	MPI_Send(&dotProduct, 1, MPI_INT, MASTER, PRODUCT, MPI_COMM_WORLD);
   }
   endTime=MPI_Wtime();
   

   if (rank==MASTER) printf("Dot Product is %d : calculated in %fs \n", finalProduct, startTime-endTime); // OUTPUT.
   MPI_Finalize();
   //------------END of Parellel Code()--------------
}


int init_lst(int * vector){
   //Initializing Values for Vectors 
   int i=0;
   for (i=0; i<N; i++)*vector++=i;
}

int dot_product(int * vec1, int * vec2, int startIndex, int endIndex){
   //Calculating DOT Product.
   int product=0; int i;
   for (i=startIndex; i<=endIndex; i++) product+=vec1[i]*vec2[i];
   return product;
}
