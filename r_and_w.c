#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUFFER_SIZE  10


int x,y,z;
volatile int readers = 0; // shared global variable
sem_t mutex, myturn, empty;

void* reader(void* name){
  int delay=1;
  while (1){
    sem_wait(&myturn);
    sem_post(&myturn);
    sem_wait(&mutex);

    readers++;
    if(readers == 1)
        sem_wait(&empty);

    sem_post(&mutex);

    printf("%s\n",(char*) name);
    printf("x:%d y:%d z:%d\n", x,y,z);

    sem_wait(&mutex);
    readers--;
    if(readers==0)
      sem_post(&empty);
    sem_post(&mutex);
    sleep(delay);
    }
  }

void* writer(void* num){
  int burst;
  int delay;
  int cnt = 0;
  while (1){
    burst = random()%10;
    delay = random()%2;
    while (cnt < burst){
    sem_wait(&myturn);
    sem_wait(&empty);
    if (!strcmp((char*) num,"1")){
      printf("assign odd nums \n");
      x = 1;
      y = 3;
      z = 5;
    }
    else{
      printf("assign even nums\n");
      x = 0;
      y = 2;
      z = 4;
    }
    sem_post(&empty);
    sem_post(&myturn);
    cnt++;
  }
    cnt = 0;
    sleep(delay);
  }
}



int
main(int argc, char *argv[])
{

  pthread_t writer1,  writer2, reader1, reader2, reader3, reader4, reader5, reader6;
    sem_init(&mutex, 0, 1);
    sem_init(&myturn, 0, 1);
    sem_init(&empty, 0, 1);
    pthread_create(&writer1, NULL, writer, "1");
    pthread_create(&writer2, NULL, writer, "0");

    pthread_create(&reader1, NULL, reader, "reader1");
    pthread_create(&reader2, NULL, reader, "reader2");
    pthread_create(&reader3, NULL, reader, "reader3");
    pthread_create(&reader4, NULL, reader, "reader4");
    pthread_create(&reader5, NULL, reader, "reader5");
    pthread_create(&reader6, NULL, reader, "reader6");

    pthread_join(writer1, NULL);
    pthread_join(reader1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(reader5, NULL);
    pthread_join(reader6, NULL);

    return 0;
}
