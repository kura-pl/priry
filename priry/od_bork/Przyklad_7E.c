/*kolokwium*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 10
int main(){
	long silnia=1,silnia_loc=1;
	long i;	
#pragma omp parallel firstprivate(silnia_loc)
{
#pragma omp for
	for(i = 1;i<=N;i++){
		silnia_loc=silnia_loc*i;
	}
#pragma omp critical
{
	silnia=silnia_loc*silnia;
}
}
printf("%d!=%ld\n",N,silnia);
return EXIT_SUCCESS;
}
