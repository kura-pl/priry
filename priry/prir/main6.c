#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int Dana = 0;
void* printmessage(void* ptr)
{
	while(1)
	{
		Dana += 1;
		sleep(2);
	};
}

void* readmessage(void* ptr)
{
	while(1)
	{
		printf("%i\n", Dana);
		sleep(1);
	};
}
int main(void)
{
	pthread_t thread, thread2;
	pthread_create(&thread, NULL, &printmessage, NULL);
	pthread_create(&thread2, NULL, &readmessage, NULL);
	sleep(2);
	pthread_detach(thread);
	pthread_detach(thread2);
	pthread_exit(NULL);
	return EXIT_SUCCESS;
}

