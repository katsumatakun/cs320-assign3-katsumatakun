#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE  10


int x,y,z;
volatile int readers = 0; // shared global variable
sem_t mutex, myturn, empty;

void *readers(){
  while (1){
    sem_wait(&myturn);
    sem_post(&myturn);
    sem_wait(&mutex);

    readers++;

    if(reader == 1){
      wait(&empty);
    }
    sem_post(&mutex);
    }
    sleep(delay);
    cnt = 0;
  }
}

void * writer(int num){

  while (1){
    // while (counter == 0);  // DO NOTHING
    sem_wait(&myturn);
    sem_wait(&empty);
    if (num == 1){
      x = 1;
      y = 3;
      z = 5;
    }
    else{
      x = 0;
      y = 2;
      z = 4;
    }

    sem_post(&empty);
    sem_post(&myturn);
  }
}



int
main(int argc, char *argv[])
{

  pthread_t produce1,  produce2, consume;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 0);
    sem_init(&full, 0, BUFFER_SIZE);
    pthread_create(&produce1, NULL, producer, "A");
    pthread_create(&produce2, NULL, producer, "B");

    pthread_create(&consume, NULL, consumer, NULL);

    pthread_join(produce1, NULL);
    pthread_join(produce2, NULL);
    pthread_join(consume, NULL);

    return 0;
}
