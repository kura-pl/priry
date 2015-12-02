#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int tid, i;
#pragma omp parallel private(tid)
    {
        tid=omp_get_thread_num();
#pragma omp for
        for(i=0;i<8; i+=1){
            sleep(tid);
            printf("to ja z numerem %d, i = %d\n", tid, i);
        }
    }
    return EXIT_SUCCESS;
}

