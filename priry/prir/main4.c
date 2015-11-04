#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void* printmessage(void* ptr)
{
	int* w = malloc(sizeof(int));
	*w = 6;
	return w;
}

int main(void)
{
	pthread_t thread;
	void *wynik;
	pthread_create(&thread, NULL, &printmessage, NULL);
	pthread_join(thread, &wynik);
	printf("%d\n", *(int*)wynik);
	free(wynik);
	return EXIT_SUCCESS;
}

