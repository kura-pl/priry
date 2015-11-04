#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int Dana = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* printmessage(void* ptr)
{
	while(1)
	{
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        pthread_mutex_lock(&mutex1);
		Dana += 1;
		sleep(1);
        pthread_mutex_unlock(&mutex2);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
	};
}

void* readmessage(void* ptr)
{
	while(1)
	{
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        pthread_mutex_lock(&mutex2);
		printf("%i\n", Dana);
		sleep(3);
        pthread_mutex_unlock(&mutex1);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();

	};
}
int main(void)
{
	pthread_t thread, thread2;
    int signum;
    sigset_t mask;
    sigemptyset(&mask);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);
    pthread_mutex_lock(&mutex2);
	pthread_create(&thread, NULL, &readmessage, NULL);
	pthread_create(&thread2, NULL, &printmessage, NULL);
    sigwait(&mask, &signum);
    pthread_cancel(thread);
    pthread_cancel(thread2);
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
	return EXIT_SUCCESS;
}

