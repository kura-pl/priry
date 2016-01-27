/*kolokwium*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 8
int main(){
int   i,j,k;
float A[N][N],B[N],C[N];
for (i=0; i < N; i++){
	B[i] = 2;
	C[i]=0;
	for (j=0; j < N; j++){
  		A[i][j] = i;
	}
}
#pragma omp parallel for private(j)
	for (i=0; i < N; i++)
		for (j=0; j < N; j++)
				C[i]+=A[i][j]*B[j];
for (i=0; i < N; i++){
		printf("%f\n",C[i]);
}
return EXIT_SUCCESS;
}
