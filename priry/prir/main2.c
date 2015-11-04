#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int a=2;

int main(void)
{
   if(fork() == 0) 
   {
	   a = 4;
	   printf("potomek %d\n", a);
   }
   else
   {
	   wait((int*)0);
	   printf("rodzic %d\n", a);
   }
   return EXIT_SUCCESS;
}

