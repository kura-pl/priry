#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char** argv)
{
    int p,n,i, rank, g_rank, new_rank,a=0;
    int* rank_new;
    MPI_Group g, g_new;
    MPI_Comm c_new;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD, & rank);
    MPI_Comm_group(MPI_COMM_WORLD, &g);
    n = p / 2;
    rank_new = malloc(n * sizeof(int));
    if (rank %2==0) for(i=0; i <n ; i++) rank_new[i] = 2 * i;
    else for(i=0; i <n; i++) rank_new[i] = 2 * i + 1;
    MPI_Group_incl(g,n,rank_new, &g_new);
    MPI_Comm_create(MPI_COMM_WORLD, g_new, &c_new);
    MPI_Group_rank(g_new, &g_rank);
    MPI_Comm_rank(c_new, &new_rank);
    if(rank == 0) a = 10;
    if(rank == 1) a = 20;
    MPI_Bcast(&a, 1, MPI_INT, 0, c_new);
        printf("rank : %d, g_rank: %d, new rank : %d, a = %d\n", rank, g_rank, new_rank,a);
    return 0;
}

