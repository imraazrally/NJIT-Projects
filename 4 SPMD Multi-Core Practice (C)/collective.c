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
   int vector_x[N], vector_y[N], finalProduct, dotProduct, i;
   init_lst(vector_x);
   init_lst(vector_y);

   int startTime=MPI_Wtime();
   //------------Start of Parellel Code()--------------
   int size, rank;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
   //------------Scatter------------------------------
   int nElem=N/size;
   int finalProducts[size];
   MPI_Scatter(vector_x,nElem,MPI_INT, vector_x+(rank*nElem),nElem,MPI_INT,MASTER,MPI_COMM_WORLD); 
   MPI_Scatter(vector_y,nElem,MPI_INT, vector_y+(rank*nElem),nElem,MPI_INT,MASTER,MPI_COMM_WORLD);
   
   //------------Calculates dot product------------------------------
   dotProduct=dot_product(vector_x,vector_y,rank*nElem, (rank*nElem)+(nElem-1));
 
   //------------Gather------------------------------
   MPI_Gather(&dotProduct, 1, MPI_INT, finalProducts, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
   int endTime=MPI_Wtime();

   if (rank==MASTER){
 	for (i=0; i<size; i++) finalProduct+=finalProducts[i];
	printf("Dot Product is %d : calculated in %fs \n", finalProduct, startTime-endTime); // OUTPUT.
   }
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
