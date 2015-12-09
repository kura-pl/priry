#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int sm=-2;
    float il = -1;
    printf("sm %d, il: %f\n", sm, il);
#pragma ompparallel reduction(+: sm) reduction(*: il)
    {
        printf("\tsm: %d, il: %f\n", sm, il);
        sm += 4;
        il *= 2;
        printf("\t\tsm %d, il %f\n", sm , il);
    }
printf("\t\t\tsm: %d, il: %f\n", sm, il);
   return EXIT_SUCCESS;
}

