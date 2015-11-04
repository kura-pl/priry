#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int my_rank;
    char* message1="Hello";
    char* message2="World";
    char message[6];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if(my_rank ==0)
    {
    MPI_Send(message1, 6, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
    MPI_Send(message2, 6, MPI_CHAR, 2, 1, MPI_COMM_WORLD);
    }
    else
    {
    MPI_Recv(message, 6, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
    printf("%s\n", message);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}
