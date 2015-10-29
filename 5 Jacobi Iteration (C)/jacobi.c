#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 100
#define MAX_ITER 10000
void print_equation();
void jacobi();
void set_test();

float matrix_a[N][N], vec_b[N];
float vec_x[N], buf[N];
int n;
float error;


int main(int argc, char **argv)
{	 
   int i;
   n=atoi(argv[1]);
   error=atof(argv[2]);
   init();
	
   //while Convergence is not reached ---> Iterate
   while(!convergence()){
	jacobi();
   }

   for (i=0; i<n; i++) printf("X[%d]=%f \n",i,vec_x[i]);
   
}

int convergence(){
   int i,j;
   float product;

   for (i=0; i<n; i++){
	product=0;
	for(j=0; j<n; j++){
	   //Multiply each equality with corresponding x values/
	   product+=matrix_a[i][j]*vec_x[j];	
	}
	product=product-vec_b[i]; // if (ax+b=c) -> ax+b-c=0 -----Testing whether it's 0 +-error.
	if (product>error) return 0;
   } 	
   return 1;
}

void jacobi(){
   float tmp[n];
   float product;
   int i,j;
   // For each equation,
   for (i=0; i<n;i++){
	product=0;
   	for (j=0;j<n; j++){ //Except for a[i][i]
	   if(i!=j)product+=(-matrix_a[i][j])*vec_x[j]; // move the variable to the right handside (-)  
	}
	product+=vec_b[i]; 
	tmp[i]=product/matrix_a[i][i]; //devide by a[i][i]	
   }
   for (i=0; i<n; i++)vec_x[i]=tmp[i]; // Rewrite the vector_x
}

void init(char **argv){
   int i, j, sum;
   srand(time(NULL));
   //--------------------------Initializing the A matrix(random)---------------------
   for (i=0; i<n; i++){
   	for (j=0; j<n; j++){
	   matrix_a[i][j]=rand() & 0x7; // assign random values upto 7
	   if (rand()&0x1) matrix_a[i][j]=-matrix_a[i][j]; // random negative values	
	}
	// Ensuring Convergence
	sum=0;
	for (j=0; j<n; j++){
		if (i!=j) sum+=abs(matrix_a[i][j]); // summ values in each eqation except for diagnoal	
	}
	// If converganceFail(): increment the diagnol value so that convergencePass();
	if (matrix_a[i][i]<sum) matrix_a[i][i]=matrix_a[i][i]+sum; // this will make the value greater than sum
   }
   //---------------------------Initializing X Vector (1)------------------------------
   for (i=0; i<n; i++) vec_x[i]=0;

   //---------------------------Initializing B Vector (random)------------------------------
   for (i=0; i<n; i++){
	vec_b[i]=rand()& 0x7;
   	if (rand() & 0x1) vec_b[i]=-vec_b[i];
   }

   print_equation();
}

void print_equation(){
  int i,j;
  for (i=0; i<n; i++){
      for (j=0; j<n;j++)printf("%3d",(int)matrix_a[i][j]); 
      printf("  * x%d = %d \n", i, (int)vec_b[i]);
  }
}

