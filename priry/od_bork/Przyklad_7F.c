/*kolokwium*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 10
int main(){
	long silnia=1;
	long i;	
#pragma omp parallel for reduction(*:silnia)
	for(i = 1;i<=N;i++){
		silnia=silnia*i;
	}
printf("%d!=%ld\n",N,silnia);
return EXIT_SUCCESS;
}
