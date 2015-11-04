#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define N 12
float A[N], MIN;
int skok=N/4;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
void* count(void *ptr){
    int k, *m;
    float min;
    m=(int*)ptr;
    min=A[*m];
    for(k=*m+1;k<*m+skok;k++){
        if(min>A[k])min=A[k];
    }
    pthread_mutex_lock(&mutex);
    if(MIN>min)
    {
        MIN = min;
    };
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    int i;
    int message[4];
    pthread_t thread[4];
    for(i=0;i<4;i++) message[i]=i*skok;
    srand((unsigned int)time((time_t*)NULL));
    for(i=0;i<N;i++){
        A[i]=(float) (rand()/1000);
    };
    for(i=0;i<N;i++) printf("%20.2f\n",A[i]);
    MIN = A[0];
    for(i=0;i<4;i++)pthread_create(&thread[i],NULL,&count,(void*) &message[i]);
    for(i=0;i<4;i++){
        pthread_join(thread[i], NULL);
    }printf("minimum %20.2f\n",A[i]);
    return EXIT_SUCCESS;
}

