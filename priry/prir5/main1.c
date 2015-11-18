#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define N 20

float maximum(float* Arev,int q){
    float max=Arev[0];
    int i=1;
    for(i;i<q;i++) if(max<Arev[i]) max=Arev[i];
    return max;
}

int main(int argc, char** argv)
{
    float *A,*Arev,C,c;
    int rank,i,p,r,q;
    srand((unsigned int)time((time_t*)NULL));
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    r=N%p;
    if(r==0)q=N/p;
    else q=(N+p-r)/p;
    if(rank==0){
        A=calloc(q*p,sizeof(float));
        for(i=0;i<N;i++){
            A[i]=(float)rand();
            printf("%20.2f\n",A[i]);
        }
    }
    Arev=malloc(q*sizeof(float));
    MPI_Scatter(A,q,MPI_FLOAT,Arev,q,MPI_FLOAT,0,MPI_COMM_WORLD);
    c=maximum(Arev,q);
    MPI_Reduce(&c,&C,1,MPI_FLOAT,MPI_MAX,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("-----------------\n");
        printf("%20.2f(maximum)\n",C);
    }
    free(Arev);
    MPI_Finalize();
    return 0;
}
