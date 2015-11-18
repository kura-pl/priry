#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc,char **argv)
{
    int p,rank,n_rank,color,a=0;
    MPI_Comm c_new;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    color=rank%2;
    MPI_Comm_split(MPI_COMM_WORLD,color,rank,&c_new);
    MPI_Group_rank(c_new,&n_rank);
    if(rank==0) a=10;
    if(rank==1) a=20;

    MPI_Bcast(&a,1,MPI_INT,0,c_new);
    printf("rank:%d, n_rank: %d, a=%d, %d\n",rank,n_rank,a,color);
    MPI_Finalize();
    return 0;
}

//25.11 nie ma zajec
//9.12 kolokwium MPI tylko
