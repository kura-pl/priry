#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int N=20;
int main(int argc,char **argv){
	MPI_Init(&argc,&argv);
	srand((unsigned int)time((time_t*)NULL));
	int rank,size,r,q,*A,*B,i,min=100,c,min2;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	r=N%(size);
	if(r==0) q=N/size;
	else q=(N+size-r)/size;
	B=(int*)calloc(q,sizeof(int));
	if(rank==0){
		A=(int*)calloc(N,sizeof(int));
		for(i=0;i<N;i++){
			A[i]=rand()%100;
			printf("%d\n",A[i]);
		}
		for(i=1;i<size;i++){
			MPI_Send(&(A[(i)*q]),q,MPI_INT,i,1,MPI_COMM_WORLD);
		}
		for(i=0;i<q;i++){
			if(A[i]<min) min=A[i];
		}
		for(i=1;i<size;i++){
			MPI_Recv(&c,1,MPI_INT,i,1,MPI_COMM_WORLD,&status);
			if(c<min) min=c;
		}
		printf("Wynik to=%d\n",min);
		free(A);
	}
	else{
		MPI_Recv(B,q,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		for(i=0;i<q;i++)
			if(B[i]<min) min=B[i];
		MPI_Send(&min,1,MPI_INT,0,1,MPI_COMM_WORLD);
		free(B);
	}
	MPI_Finalize();
	return 0;	
}
