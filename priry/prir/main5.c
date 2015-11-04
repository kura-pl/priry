#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int a = 2;
typedef struct _Arg{
	int b;
	int c;
} Arg;

void* printmessage(void* ptr)
{
	a += ((Arg*)ptr)->b;
	a *= ((Arg*)ptr)->c;
	printf("potomek %d\n", a);
	return NULL;
}

int main(void)
{
	Arg arg=(3,2);
	pthread_t thread;
	pthread_create(&thread, NULL, &printmessage, (void*)&arg);
	pthread_join(thread, NULL);
	printf("rodzic %d\n", a);
	return EXIT_SUCCESS;
}

