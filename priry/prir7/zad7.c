#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int tid, i;
    omp_set_num_threads(2);
#pragma omp parallel private(tid)
    {
        tid=omp_get_thread_num();
#pragma omp for nowait
        for(i=0;i<8; i+=1){
            sleep(tid);
            printf("to ja z numerem %d, i = %d\n", tid, i);
        }
#pragma ompe barrier
        printf("KONIEC %d\n", tid);
    }
    return EXIT_SUCCESS;
}

