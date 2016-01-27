#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
void readMatrix(FILE *input,int *s,int **m){
	int size;
	int i,j,p;
	fscanf(input, "%d",&size);
	printf("fsize: %d\n",size);
	*s=size;
	fscanf(input,"\n",NULL);
	*m=malloc(sizeof(int)*size*size);
	for(i=0;i<size*size;i++){
		fscanf(input,"%d",&p);
		(*m)[i]=p;
		fscanf(input,"\n",NULL);
	}
}
void printMatrix(int **m,int size){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("%d\t",(*m)[i*size+j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){

	int i,j,size,sub_size,rows_perproc,k,*scounts=NULL,*displs=NULL,add;
	int p,myid,what_id,what_row;
	FILE *input = fopen("input_array.txt","r");
	int *m=NULL, *sub_m=NULL, *k_row=NULL, *k_col=NULL;
	


	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	if(myid==0){
		readMatrix(input,&size,&m);
		printf("Wczytana macierz: \n");
		printMatrix(&m,size);
	}
	MPI_Bcast(&size,1,MPI_INT,0,MPI_COMM_WORLD);
	
	displs = malloc(p*sizeof(int));
	scounts = malloc(p*sizeof(int));
	rows_perproc = size/p;
	add = size - rows_perproc*p;

	        for (i=0; i<p; ++i) {
			scounts[i] = rows_perproc*size;
			if(add > 0){scounts[i]+=size; add--;}
			if(i==0){displs[i] = 0;}
		        else{displs[i]=displs[i-1]+scounts[i-1];}
		}

	sub_size=scounts[myid]/size;
	sub_m=malloc(sizeof(int)*scounts[myid]);
	k_row=malloc(sizeof(int)*size);
	k_col=malloc(sizeof(int)*sub_size);
	MPI_Scatterv(m,scounts,displs,MPI_INT,sub_m,scounts[myid],MPI_INT,0,MPI_COMM_WORLD);
	for (k=0;k<size;k++){
		for(i=0;i<sub_size;i++) {
			k_col[i]=sub_m[i*size+k];
		}

		what_id=0;
		what_row=k;
		while(scounts[what_id]/size<=what_row) {
			what_row-=scounts[what_id]/size;
			what_id++;
		}
		
		if(what_id==myid){
			for(i=0;i<size;i++)
			k_row[i]=sub_m[what_row*size+i];
		}

		MPI_Bcast(k_row,size,MPI_INT,what_id,MPI_COMM_WORLD);
		for(i=0;i<sub_size;i++){
			for(j=0;j<size;j++){
			if(sub_m[i*size+j]>=(k_row[j]+k_col[i]))
				sub_m[i*size+j]=(k_row[j]+k_col[i]);
		}
		}
	}
	MPI_Gatherv(sub_m,scounts[myid],MPI_INT,m,scounts,displs,MPI_INT,0,MPI_COMM_WORLD);

	if(myid==0){
		printf("Wynik algorytmu: \n");
		printMatrix(&m,size);
	}
	free(scounts);
	free(displs);
	free(m);
	free(sub_m);
	free(k_col);
	free(k_row);

	MPI_Finalize();
	return 0;
}

