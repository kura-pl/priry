#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int N=10;
int main(int argc,char **argv){
	MPI_Init(&argc,&argv);
	int rank,size,r,q,*A,*B,*C,i,min=100;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	r=N%(size);
	if(r==0) q=N/size;
	else q=(N+size-r)/size;
	B=(int*)calloc(q,sizeof(int));
	if(rank==0){
		A=(int*)calloc(N,sizeof(int));
		C=(int*)calloc(size,sizeof(int));
		for(i=0;i<N;i++){
			A[i]=rand()%100;
			printf("%d\n",A[i]);

		}
	}
	MPI_Scatter(A,q,MPI_INT,B,q,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0;i<q;i++) if(min>B[i]) min=B[i];
	MPI_Gather(&min,1,MPI_INT,C,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
		for(i=1;i<size;i++){
			if(min>C[i]) min=C[i];
		}
		printf("Wynik to %d\n",min);
		free(A);
		free(C);
	}
	free(B);
	MPI_Finalize();
	return 0;	
}
