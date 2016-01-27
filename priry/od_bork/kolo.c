#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
#define N 6  // Ustalam stala N liczb naturalnych w tablicy

int main (int argc, char **argv) {
	MPI_Init(&argc, &argv);
	//Tutaj dzieje sie program.
	int p; //Liczba procesow.
	MPI_COMM_SIZE(MPI_COMM_WORLD, &p); // wpisuje do p liczbe procesow
	int rank; //Numer procesu w komunikatorze
	MPI_COMM_RANK(MPI_COMM_WORLD, &rank); 

	//Tworzy tablice z liczbami
	int tablica[N], i;
	if (rank == 0){ // Proces 0 wypelnia tablice
		for( i = 0; i < N; i++)
			tablica[i] = i*10;
	}
	
	//Proces o numerze 0 wysyla wypelniona tablice do pozostalych procesow.
	MPI	

	//Program wykonywany przez p procesow:
	
	//Do komunikacji wykorzystaj funkcje MPI_Scatter oraz MPI_Gather


	MPI_Finalize();
	return 0;
}
