#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

void* printmessage(void *ptr)
{
    char * message;
    message=(char*)ptr;
    printf("%s\n", message);
    return NULL;
}

int main(void)
{
    pthread_t thread1, thread2;
    char* mess1="Hello";
    char* mess2="Word";
    pthread_create(&thread1, NULL, &printmessage,(void*)mess1);
    pthread_create(&thread2, NULL, &printmessage,(void*)mess2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return EXIT_SUCCESS;
}

