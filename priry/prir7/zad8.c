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
        sleep(2);
        printf("to ja z numerem %d, i = %d\n", tid, i);
#pragma omp critical
        {
            sleep(2);
            printf("sekcja:critical, to ja numer %d\n", tid);
        }
#pragma ompe barrier
#pragma omp master
        {
            sleep(2);
            printf("sekcja:master, to ja numer %d\n", tid);
        }
    }
    return EXIT_SUCCESS;
}

