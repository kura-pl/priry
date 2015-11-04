#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int my_rank;
    char* message;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if(my_rank ==0)
    {
    message=malloc(6);
    strncpy(message, "hello", 6);
    MPI_Send(message, 6, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
    strncpy(message, "World", 6);
    MPI_Send(message, 6, MPI_CHAR, 2, 1, MPI_COMM_WORLD);
    free(message);
    }
    else
    {
    message=malloc(6);
    MPI_Recv(message, 6, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
    printf("%s\n", message);
    free(message);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}
