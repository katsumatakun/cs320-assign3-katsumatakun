#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int cnt = 0;
sem_t mutex;

void * Count(void * a)
{
    int i, tmp;
    for(i = 0; i < NITER; i++)
    {
      sem_wait(&mutex);
        tmp = cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        cnt = tmp;      /* store the local value into the global cnt */
        sem_post(&mutex);
    }
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;


    sem_init(&mutex, 0, 1);

    pthread_create(&tid1, NULL, Count, NULL);
    pthread_create(&tid2, NULL, Count, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
      
    if (cnt < 2 * NITER) 
        printf("\n BOOM! cnt is [%d], should be %d\n", cnt, 2*NITER);
    else
        printf("\n OK! cnt is [%d]\n", cnt);
  
    pthread_exit(NULL);
}


