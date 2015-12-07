#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int rank, size, N=10, *tablica, x,
            reszta, po_ile, *tablica_buforowa, *tablica_wynikowa, minimum;

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
            tablica_wynikowa = (int*)malloc(size * sizeof(int));
            for(x=0; x < N; x+=1){
                tablica[x] = rand() % 100;
            }

            for(x=0; x < N; x+=1){
                printf("%d\n", tablica[x]);
            }
        }
    MPI_Scatter(tablica, po_ile, MPI_INT, tablica_buforowa, po_ile, MPI_INT, 0, MPI_COMM_WORLD);
    for(x=0; x < po_ile; x += 1){
        printf("Rank %d, liczba %d\n", rank, tablica_buforowa[x]);
    }

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
    MPI_Gather(&minimum, 1,MPI_INT, tablica_wynikowa, 1,MPI_INT, 0, MPI_COMM_WORLD);
    if(rank == 0){
        minimum = tablica_wynikowa[0];
        for(x=0; x < size; x +=1){
            if(minimum > tablica_wynikowa[x])
                minimum = tablica_wynikowa[x];
        }
        printf("Minimum to: %d\n", minimum);
    }
    MPI_Finalize();
    return 0;
}

