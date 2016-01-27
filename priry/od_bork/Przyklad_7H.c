/*kolokwium*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#define N 20

int main(){
	float A[N];
	float diff,max,max_loc;
	int i;
	srand((unsigned int)time((time_t*)NULL));
   	for(i=0;i<N;i++){
         	A[i] =(float)rand();
	}
   	for(i=1;i<N;i++){
		printf("%20.2f\n",fabs(A[i]-A[i-1]));
	}
	max=fabs(A[1]-A[0]);
	max_loc=max;
#pragma omp parallel firstprivate(max_loc)
{
#pragma omp for
	for(i = 2;i<N;i++){
		diff=fabs(A[i]-A[i-1]);
		if(diff>max_loc)max_loc=diff;
	}
#pragma omp critical
{
	if(max_loc>max)max=max_loc;
}
#pragma omp barrier
#pragma omp master
{
	printf("%20.2f (diff maximum)\n",max);
}
}
return EXIT_SUCCESS;
}
