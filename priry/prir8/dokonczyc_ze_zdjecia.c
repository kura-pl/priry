#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#define N 8



int main(void)
{
    int i,j,k;
    float A[N][N], B[N][N], C[N][N];
    for(i=0; i < N; i++){
        for(j=0; j< N; j++){
            A[i][j] = i;
            B[i][j] = 2;
            C[i][j] = 0;
        }
#pragma omp parallel
        {
#ragma omp for private(j,k)
            for (i=0; i < N; i +=1)
                for(j=0;j <N; j +=1)
                    for(k=0;k<N;k +=1)
                        C[i][j] += A[i][k] * B[k][j];
        }
        for (i=0; i<N; i++)
        }
    return EXIT_SUCCESS;
}

