#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

int a = 2;
void* printmessage(void* ptr)
{
	a=4;
	printf("potomek %d\n", a);
	return NULL;
}

int main(void)
{
	pthread_t thread;
	pthread_create(&thread, NULL, &printmessage, NULL);
	pthread_join(thread, NULL);
	printf("rodzic: %d\n", a);
	return EXIT_SUCCESS;
}

