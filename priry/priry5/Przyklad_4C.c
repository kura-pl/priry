/*
 (1)----(0)----(3)----(2)
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	int rank,i,count_in,count_out,rank2,weighted;
	MPI_Comm comm_graph;
	int nnodes,*sources,*degrees,*destinations,*weights;
	int *In, *Out, *In_w, *Out_w;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank==0){
		nnodes=1;
		sources=malloc(nnodes*sizeof(int));sources[0]=0;
		degrees=malloc(nnodes*sizeof(int));degrees[0]=2;
		destinations=malloc(degrees[0]*sizeof(int));destinations[0]=1;destinations[1]=3;
		weights=malloc(degrees[0]*sizeof(int));weights[0]=1;weights[1]=1;
		MPI_Dist_graph_create(MPI_COMM_WORLD,nnodes,sources,degrees,destinations,weights,MPI_INFO_NULL,0,&comm_graph);
	}
	if(rank==1){
		nnodes=1;
		sources=malloc(nnodes*sizeof(int));sources[0]=1;
		degrees=malloc(nnodes*sizeof(int));degrees[0]=1;
		destinations=malloc(degrees[0]*sizeof(int));destinations[0]=0;
		weights=malloc(degrees[0]*sizeof(int));weights[0]=1;
		MPI_Dist_graph_create(MPI_COMM_WORLD,nnodes,sources,degrees,destinations,weights,MPI_INFO_NULL,0,&comm_graph);
	}
	if(rank==2){
		nnodes=1;
		sources=malloc(nnodes*sizeof(int));sources[0]=2;
		degrees=malloc(nnodes*sizeof(int));degrees[0]=1;
		destinations=malloc(degrees[0]*sizeof(int));destinations[0]=3;
		weights=malloc(degrees[0]*sizeof(int));weights[0]=1;
		MPI_Dist_graph_create(MPI_COMM_WORLD,nnodes,sources,degrees,destinations,weights,MPI_INFO_NULL,0,&comm_graph);
	}
	if(rank==3){
		nnodes=1;
		sources=malloc(nnodes*sizeof(int));sources[0]=3;
		degrees=malloc(nnodes*sizeof(int));degrees[0]=2;
		destinations=malloc(degrees[0]*sizeof(int));destinations[0]=0;destinations[1]=2;
		weights=malloc(degrees[0]*sizeof(int));weights[0]=1;weights[1]=1;
		MPI_Dist_graph_create(MPI_COMM_WORLD,nnodes,sources,degrees,destinations,weights,MPI_INFO_NULL,0,&comm_graph);
	}
	MPI_Comm_rank(comm_graph, &rank2);
	MPI_Dist_graph_neighbors_count(comm_graph, &count_in,&count_out,&weighted);
	In=malloc(count_in*sizeof(int));
	Out=malloc(count_out*sizeof(int));
	In_w=malloc(count_in*sizeof(int));
	Out_w=malloc(count_out*sizeof(int));
        MPI_Dist_graph_neighbors(comm_graph,count_in,In,In_w,count_out,Out,Out_w);
	for(i=0;i<count_in;i++)printf("(%d)<--%d--(%d)\n",rank2,In_w[i],In[i]);
	for(i=0;i<count_out;i++)printf("(%d)--%d-->(%d)\n",rank2,Out_w[i],Out[i]);
	free(sources);
	free(degrees);
	free(destinations);
	free(weights);
	free(In);
	free(Out);
	free(In_w);
	free(Out_w);
	MPI_Finalize();
	return EXIT_SUCCESS;
}
