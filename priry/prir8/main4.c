#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100
int main(void)
{
    int i;
    double a[N], b[N], iloczyn = 0;
    for(i=0; i<N; i+=1){
        a[i] = i;
        b[i] = 2;
    }
#pragma omp parallel
    {
#pragma omp for reduction(+: iloczyn)
        for (i=0; i < N; i += 1){
            iloczyn += (a[i] * b[i]);
            }
    }
    printf("iloczyn skalarny: %f\n, iloczyn");
   return EXIT_SUCCESS;
}

