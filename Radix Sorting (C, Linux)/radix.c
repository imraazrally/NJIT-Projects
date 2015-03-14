// C coding
#include <stdio.h>

int main(int argc, char **argv)
{
	int i=0, j=0, pass=0; // Loops
	int group=4, n=10, bucket=1<<group;
	int list[] = {0x0000, 0x4c7f, 0xcd80, 0x41fc, 0x782c, 0x8b74, 0x7eb1, 0x9a03, 0xaa01, 0x73f1 };
	int buf[n];	
	int count[bucket];
	int map[bucket];
	int * buf_p=&list;
	int * list_p=&buf; 	
	printf("group: %d | n: %d | bucket: %d \n", group, n, bucket);
	
	//Initialize buf;
	for (i=0;i<n; i++){
		buf[i]=0;
	}
	//----------------------------------------------------------------------------------------------------

	//go from least significant to the most significant
	for (pass=0; pass<4; pass++)
	{
		//intialize count and map
		for (i=0; i<bucket; i++){
			count[i]=0;
			map[i]=0;
		}
		//Alternating list and buffer so that we don't overwrite and no need to create multiple arrays
		if (list_p=&buf){
			list_p=&list;
			buf_p=&buf;
		}else{
			list_p=&buf;
			buf_p=&list;
		}
		
		//1------COUNT
		for (i=0; i<n; i++){
			count[(list_p[i]>>(pass*group))&0x000f]++;		
		}
		
		printf("COUNT: ");		
		for (i=0; i<bucket;i++){printf("%x ",count[i]);}
		printf("\n");
		


		//2------MAP
		map[0]=0;
		for (i=1; i<bucket; i++){
			map[i]=map[i-1]+count[i-1];		
		}

		printf("MAP:  ");		
		for (i=0; i<bucket;i++){printf("%x ",map[i]);}
		printf("\n");





		
		//3-----Sort
		for (i=0; i<n; i++){
			buf_p[map[(list_p[i]>>(group*pass))&0x000f]]=list_p[i];
			map[(list_p[i]>>(group*pass))&0x000f]++;
		}
		
					
		printf("BUF:  ");		
		for (i=0; i<n;i++){printf("%x   ",buf_p[i]);}
		printf("\n\n\n\n");	


	}
	
}


