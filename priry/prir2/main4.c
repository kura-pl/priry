#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define N 12
float A[N], M[N];
int skok=N/4;
void* count(void *ptr){
    int k, *m;
    float* min=malloc(sizeof(float));
    m=(int*)ptr;
    *min=A[*m];
    for(k=*m+1;k<*m+skok;k++){
        if(*min>A[k]) *min=A[k];
    }
    return min;
}

int main(){
    int i;
    int message[4];
    pthread_t thread[4];
    void* wynik;
    for(i=0;i<4;i++) message[i]=i*skok;
    srand((unsigned int)time((time_t*)NULL));
    for(i=0;i<N;i++){
        A[i]=(float) (rand()/1000);
    };
    for(i=0;i<N;i++) printf("%20.2f\n",A[i]);
    for(i=0;i<4;i++)pthread_create(&thread[i],NULL,&count,(void*) &message[i]);
    float MIN=A[0];
    for(i=0;i<4;i++){
        pthread_join(thread[i], &wynik);
        if(*(float*)wynik<MIN) MIN=(*(float*)wynik);
        }printf("minimum %20.2f\n",A[i]);
        }

