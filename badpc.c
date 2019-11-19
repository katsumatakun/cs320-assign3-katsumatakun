#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE  10


int max;
volatile int counter = 0; // shared global variable
char* buffer[BUFFER_SIZE];
sem_t mutex, full, empty;


void printBuffer(){

  int i = 0;
  printf("\t");
  for (i = 0; i<counter; i++){
    printf("%s  ",buffer[i]);
  }
  printf("\n");
  printf("\t****************************");
  printf("\n");
}

void *producer(void *arg){
  int in = 0;
  char* r;
  int burst;
  int delay;
  int cnt = 0;
  while (1){
    burst = random()%10;
    delay = random()%2;
    while (cnt < burst){
      r = (char*) arg;
      // while (counter == BUFFER_SIZE);  // DO NOTHING
      sem_wait(&full);
      sem_wait(&mutex);
      printf("\nAdding %s \t %d in buffer\n", r, counter);
      // buffer[in] = r;
      // in = (in +1) % BUFFER_SIZE;
      buffer[counter] = r;
      // !!!!!!!!!!!!!!!!!!!!!! counter ? instead of in
      printf("in %d\n",in );
      counter ++;
      printf("counter %d\n", counter);
      cnt++;
      sem_post(&mutex);
      sem_post(&empty);
    }
    sleep(delay);
    cnt = 0;
  }
}

void * consumer(){

  int out = 0;
  char* r;
  while (1){
    // while (counter == 0);  // DO NOTHING
    sem_wait(&empty);
    sem_wait(&mutex);
    r = buffer[counter-1];
    // r =  buffer[out];
    // out = (out +1) % BUFFER_SIZE;
    counter --;
    printf("\tBuffer contents:\n");
    printBuffer();
    printf("\tRemoving %s \t %d in buffer\n", r, counter);
    sem_post(&mutex);
    sem_post(&full);
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
