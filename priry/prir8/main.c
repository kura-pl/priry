#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#define N 100



int main(void)
{
    int i, tid;
    float a[N], b[N], iloczyn=0, iloczyn_l=0;
    for(i=0; i<N; i++){
        a[i] = i;
        b[i] = 2;
    }
#pragma omp parallel shared(iloczyn) private(tid) firstprivate(iloczyn_l)
    {
        tid = omp_get_thread_num();
#pragma omp for
        for(i=0; i < N; i++){
            iloczyn_l += (a[i] * b[i]);
        }
        printf("to ja numer %d, wyliczylem %f\n", tid, iloczyn_l);
#pragma omp critical
        {
            iloczyn += iloczyn_l;
            sleep(tid);
        }
    }
    printf("iloczyn skalarny %f\n", iloczyn);
    return EXIT_SUCCESS;
}

