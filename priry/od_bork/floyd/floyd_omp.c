#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 8
#define NUM_THREADS 4
#define MIN(a,b) (((a)<(b))?(a):(b))
int I[N][N];
int main(){
	int i,j,k;
	srand((unsigned int)time((time_t*)NULL));
	for(i=0;i<N;i++)for(j=0;j<N;j++){
		if(i==j){I[i][j]=0;continue;}
		I[i][j]=(rand()/100000000);
		if(I[i][j]>9)I[i][j]=1000000;
	};
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)printf("\t%d",I[i][j]);
		printf("\n");
	}
	printf("\n");
	for(k=0;k<N;k++)
#pragma omp parallel num_threads(NUM_THREADS) private(i,j) firstprivate(k)
{
#pragma omp for schedule(dynamic)
		for(i=0;i<N;i++) for(j=0;j<N;j++) I[i][j]=MIN(I[i][j],I[i][k]+I[k][j]); 
}
			
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)printf("\t%d",I[i][j]);
		printf("\n");
	}
	return EXIT_SUCCESS;
}

