#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int x, rank, liczba_sasiadow, *lista_sasiadow;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm graf;

    int wezly = 4, zakresy[4] = {1, 3, 3, 4},
            krawedzie[4] = {1, 0, 2, 0};
    MPI_Graph_create(MPI_COMM_WORLD, wezly, zakresy, krawedzie,1, &graf );
    MPI_Comm_rank(graf, &rank);
    MPI_Graph_neighbors_count(graf, rank, &liczba_sasiadow);
    lista_sasiadow = malloc(sizeof(int) * liczba_sasiadow);
    MPI_Graph_neighbors(graf, rank, liczba_sasiadow, lista_sasiadow);
    for(x=0; x < liczba_sasiadow; x += 1){
        printf("Proces %d, ma sasiada: %d\n", rank, lista_sasiadow[x]);
    }
    free(lista_sasiadow);

    MPI_Finalize();
    return 0;
}

