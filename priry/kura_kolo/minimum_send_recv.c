#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int rank, size, N=10, *tablica, x,
            reszta, po_ile, *tablica_buforowa,
            ostateczne_minimum, minimum;

    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Rank: %d.Size: %d.\n", rank, size);

    srand(time(NULL));


    reszta = N % size;
    printf("Reszta %d\n", reszta);

    if(reszta == 0){
        po_ile = N / size;
    } else {
        po_ile = (N + size -reszta) /size;
    }

    tablica_buforowa = malloc(sizeof(int) * po_ile);
    if(rank == 0){
        tablica = (int*)malloc(N * sizeof(int));
        for(x=0; x < N; x+=1){
            tablica[x] = rand() % 100;
            printf("%d\n", tablica[x]);
        }

        for(x=1; x < size; x += 1){
            MPI_Send(&tablica[x * po_ile], po_ile, MPI_INT, x,1,MPI_COMM_WORLD);
        }
        minimum=tablica[0];
        for(x=0; x < po_ile; x += 1){
            if(minimum > tablica[x]){
                minimum = tablica[x];
            }
        }
        printf("Rank: %d, minimum: %d\n", rank, minimum);
        ostateczne_minimum = minimum;
        for(x=1; x < size; x += 1){
            MPI_Recv(&minimum, 1, MPI_INT, x, 1, MPI_COMM_WORLD, &status);
            if(ostateczne_minimum > minimum){
                ostateczne_minimum = minimum;
            }
        }
        printf("Minimum to: %d\n", ostateczne_minimum);


    } else {
        tablica_buforowa = malloc(sizeof(int) * po_ile);
        MPI_Recv(tablica_buforowa, po_ile, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        if(reszta == 0){
            minimum = tablica_buforowa[0];
            for(x=0; x < po_ile; x += 1){
                if(tablica_buforowa[x] < minimum)
                    minimum = tablica_buforowa[x];
            }
        } else {
            minimum = tablica_buforowa[0];
            if(rank != size - 1){
                for(x=0; x < po_ile; x += 1){
                    if(tablica_buforowa[x] < minimum)
                        minimum = tablica_buforowa[x];
                }
            } else {
                for(x=0; x < po_ile - reszta; x += 1){
                    if(tablica_buforowa[x] < minimum)
                        minimum = tablica_buforowa[x];
                }
            }
        }
        printf("Rank: %d, minimum: %d\n", rank, minimum);
        MPI_Send(&minimum, 1,MPI_INT, 0,1,MPI_COMM_WORLD);

    }


    MPI_Finalize();
    return 0;
}

