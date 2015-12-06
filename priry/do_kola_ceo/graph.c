#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv){
	int rank,i,count,
nodes=6,index[6]={2,5,7,9,12,14},edges[14]={1,3,0,2,4,1,5,0,4,1,3,5,2,4};
	int *sasiedzi;
	MPI_Init(&argc,&argv);
	MPI_Comm comm_graph;
	MPI_Graph_create(MPI_COMM_WORLD,nodes,index,edges,1,&comm_graph);
	MPI_Comm_rank(comm_graph,&rank);
	MPI_Graph_neighbors_count(comm_graph,rank,&count);
	sasiedzi=calloc(count,sizeof(int));
	MPI_Graph_neighbors(comm_graph,rank,count,sasiedzi);
	for(i=0;i<count;i++)
		printf("rank: %d sasiad:%d\n",rank,sasiedzi[i]);
	free(sasiedzi);
	MPI_Finalize();
	return 0;
}

