#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int N = 100;
int main(int argc,char **argv){
	float *A,*B,*C,*Arev,*Brev,c=0;
	int rank,i,p,r,q;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	r=N%(p);
	if(r==0) q=N/p;
	else q=(N+p-r)/p;
	Arev=calloc(q,sizeof(float));
	Brev=calloc(q,sizeof(float));
	if(rank==0){
		A=calloc(q*p,sizeof(float));
		B=calloc(q*p,sizeof(float));
		C=calloc(p,sizeof(float));
		for(i=0;i<N;i++){
			A[i]=i;
			B[i]=2;	
			}
		
		}
	MPI_Scatter(A,q,MPI_FLOAT,Arev,q,MPI_FLOAT,0,MPI_COMM_WORLD);
	MPI_Scatter(A,q,MPI_FLOAT,Brev,q,MPI_FLOAT,0,MPI_COMM_WORLD);
	for(i=0;i<q;i++)
		c+=Arev[i]*Brev[i];
	MPI_Gather(&c,1,MPI_FLOAT,C,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	if(rank==0){
		for(i=1;i<p;i++){
			c+=C[i];
		}
		printf("%f\n",c);
		free(A);
		free(B);
		free(C);
	}
	free(Arev);
	free(Brev);
	MPI_Finalize();
	return 0;
}
