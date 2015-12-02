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
#pragma omp for schedule(dynamic,8)
        for(i=0;i<8; i+=1){
            sleep(tid);
            printf("to ja z numerem %d, i = %d\n", tid, i);
            fflush(stdout);
        }
    }
    return EXIT_SUCCESS;
}

