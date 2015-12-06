#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char **argv){
	int wymiar=2,sasiedzi[4],koordynaty[2],rank;
	int dims[2]={2,3};
	int okresowosc[2]={1,0};
	MPI_Init(&argc,&argv);
	MPI_Comm comm_cart;
	MPI_Cart_create(MPI_COMM_WORLD,wymiar,dims,okresowosc,0,&comm_cart);
	MPI_Comm_rank(comm_cart,&rank);
	MPI_Cart_coords(comm_cart,rank,2,koordynaty);
	MPI_Cart_shift(comm_cart,0,1,&sasiedzi[0],&sasiedzi[1]);
	MPI_Cart_shift(comm_cart,1,1,&sasiedzi[2],&sasiedzi[3]);
	printf("rank = %d wspolrzedne to %d %d sasiedzi= %d %d %d %d \n",rank,koordynaty[0],koordynaty[1],sasiedzi[0],sasiedzi[1],sasiedzi[2],sasiedzi[3]);
	MPI_Finalize();	
	return 0;
}
