#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int dana=0;
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
void *pisz(void* ptr){
        pthread_mutex_lock(&mutex1);
        printf("watek drugi: zajalem zasob\n");
        if(dana!=5){
             printf("watek drugi zasypiam, zwalniam zasob i czekam na 5\n");
             pthread_cond_wait(&cond,&mutex1);
             printf("watek drugi zajmuj zasob. Robie cos bo bylo 5\n");
        }
        pthread_mutex_unlock((&mutex1));
        printf("watek drugi: zwolnilem zasob\n");

}


int main(void)
{
    pthread_t t1;
    int i;
    pthread_create(&t1,NULL,&pisz,NULL);
    for(i=0;i<8;i++){
        sleep(1);
        pthread_mutex_lock(&mutex1);
        printf("watek pierwszy: zajalem zasob\n");
        dana++;
        printf("a=%d\n",dana);
        if(dana==5){
            pthread_cond_signal(&cond);
            printf("watek pierwszy: wyslalem sygnal\n");
        }
        sleep(1);
        pthread_mutex_unlock(&mutex1);
        printf("watek pierwszy: zwolnilem zasob\n");
    }
    pthread_join(t1,NULL);
    pthread_mutex_destroy(&mutex1);
    pthread_cond_destroy(&cond);

    return 0;

}

