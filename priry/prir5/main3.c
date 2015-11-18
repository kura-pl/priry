#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc,char **argv)
{
    int rank,i,count;
    int* neighbors;
    int nnodes=4,index[4]={2,3,4,6},edges[6]={1,3,0,3,0,2};
    MPI_Comm comm_graph;
    MPI_Init(&argc,&argv);
    MPI_Graph_create(MPI_COMM_WORLD,nnodes,index,edges,1,&comm_graph);
    MPI_Comm_rank(comm_graph,&rank);

    MPI_Graph_neighbors_count(comm_graph,rank,&count);
    neighbors=malloc(count*sizeof(int));
    MPI_Graph_neighbors(comm_graph,rank,count,neighbors);
    for(i=0;i<count;i++){
        printf("(%d)---(%d)\n",rank,neighbors[i]);
    }
    free(neighbors);
    MPI_Finalize();
    return 0;
}
