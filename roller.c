#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define C  6


int x,y,z;
volatile int boarders = 0; // shared global variable
volatile int unboarders = 0; // shared global variable
sem_t mutex1, mutex2, board, unboard, empty, full;

void* passenger(void* name){
  int delay=1;
  while (1){
    sem_wait(&board);
    printf("BOARD %s\n", (char*) name);
    sem_wait(&mutex1);
      boarders+=1;
      if(boarders==C){
        sem_post(&full);
        boarders=0;
      }
    sem_post(&mutex1);

    sem_wait(&unboard);
    printf("UNBOARD %s\n", (char*) name);

    sem_wait(&mutex2);
    unboarders+=1;
    if (unboarders == C){
      sem_post(&empty);
      unboarders = 0;
    }

    sem_post(&mutex2);
    sleep(delay);
    }
  }

void* car(){
  int burst;
  int delay;
  int cnt = 0;
  while (1){
    burst = random()%10;
    delay = random()%2;
    while (cnt < burst){
    printf("LOAD\n");
    for (int i=0; i<C; i++)
      sem_post(&board);
    sem_wait(&full);

    printf("RUN\n");

    printf("UNLOAD\n");
    for (int j=0; j<C; j++)
      sem_post(&unboard);
    sem_wait(&empty);
    cnt++;
  }
    cnt = 0;
    sleep(delay);
  }
}



int
main(int argc, char *argv[])
{

  pthread_t car1, p1, p2, p3, p4, p5, p6, p7;
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&board, 0, 0);
    sem_init(&unboard, 0, 0);
    sem_init(&empty, 0, 0);
    sem_init(&full, 0, 0);
    pthread_create(&car1, NULL, car, NULL);

    pthread_create(&p1, NULL, passenger, "p1");
    pthread_create(&p2, NULL, passenger, "p2");
    pthread_create(&p3, NULL, passenger, "p3");
    pthread_create(&p4, NULL, passenger, "p4");
    pthread_create(&p5, NULL, passenger, "p5");
    pthread_create(&p6, NULL, passenger, "p6");
    pthread_create(&p7, NULL, passenger, "p7");

    pthread_join(car1, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    pthread_join(p6, NULL);
    pthread_join(p7, NULL);

    return 0;
}
