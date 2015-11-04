//mpdboot -n 4 -f ./machines
//mpicc program.c
//miexec -np
#include <stdlib.h>
#include <mpi.h>
define N 100
int main(int argc,char **argv){
	float *A,*B,*Arev,*Brev,c=0;d;
	int rank,i,p,r,q;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	r=N%p;
	if(r==0) q=N/p;
	else q=(N+p-r)/p;
	if(rank==0){
		A=calloc(q*p,sizeof(float));
		B=calloc(q*p,sizeof(float));
	}
	else{
		Arev=calloc(q,sizeof(float));
		Brev=calloc(q,sizeof(float));	
	}
	if(rank==0){
		for(int i=0;i<N;i++){
			A[i]=i;
			B[i]=2;		
		}
		for(int i=0;i<p;i++){
			MPI_SEND(&(A[(i)*q]),q,MPI_FLOAT,i,1,MPI_COMM_WORLD);
			MPI_SEND(&(B[(i)*q]),q,MPI_FLOAT,i,1,MPI_COMM_WORLD);	
		}
		for(int i=0;i<q;i++)
			c+=A[i]*B[i];
		for(int i=0;i<p;i++){
			MPI_Recv(&d,1,MPI_FLOAT,i,1,MPI_COMM_WORLD,&status);
			c+=d;
		}
		printf("%f\n",c);
		free(A);
		free(B);
			
	}else{
		MPI_Recv(Arev,q,MPI_FLOAT,0,1,MPI_COMM_WORLD,&status);
		MPI_Recv(Arev,q,MPI_FLOAT,0,1,MPI_COMM_WORLD,&status);
		for(i=0;i<q;i++)
			c+=Arev[i]*Brev[i];
		MPI_Send(&c,1,MPI_FLOAT,0,1,MPI_COMM_WORLD);
		free(Arev);
		free(Brev);	
	}
	MPI_Finalize();
	return 0;

}

