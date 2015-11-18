#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc,char **argv)
{
    int p,n,i,rank,g_rank,new_rank,a=0;
    int *ranks_new;
    MPI_Group g,g_new;
    MPI_Comm c_new;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_group(MPI_COMM_WORLD,&g);
    n=p/2;
    ranks_new=malloc(n*sizeof(int));
    for(i=0;i<n;i++) ranks_new[i]=2*i+1;
    if((rank%2)==1) MPI_Group_incl(g,n,ranks_new,&g_new);
    else MPI_Group_excl(g,n,ranks_new,&g_new);
    MPI_Comm_create(MPI_COMM_WORLD,g_new,&c_new);
    MPI_Group_rank(g_new,&g_rank);
    if(rank==0) a=10;
    if(rank==1) a=20;
    MPI_Bcast(&a,1,MPI_INT,0,c_new);
    printf("rank:%d, g_rank: %d, new_rank: %d, a=%d\n",rank,g_rank,new_rank,a);
    free(ranks_new);
    MPI_Finalize();
    return 0;
}

//25.11 nie ma zajec
//9.12 kolokwium MPI tylko
