
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>


#define TH_N 10


sem_t mutex[TH_N];


void *eat(void *args) {

  int i = *((int *)args);
  free(args);

  while (1) {
    sem_wait(&mutex[i]);
    sem_wait(&mutex[(i+1)%TH_N]);
  
    printf("\nPhilosopher %d is eating\n", i);

    sem_post(&mutex[i]);
    sem_post(&mutex[(i+1)%TH_N]);

    sleep(1);
  }

}


void handler(int sig) {
  if (sig == SIGINT) {
    printf("\nTerminating program\n");
    exit(EXIT_SUCCESS);
  }
}


int main(int argc, char *argv[]) {

  signal(SIGINT, handler);

  for (int i=0; i<TH_N; i++) {
    sem_init(&mutex[i], 0, 1);
  }

  pthread_t th[TH_N];

  for (int i=0; i<TH_N; i++) {
    int *arg = (int *)malloc(sizeof(*arg));
    if (arg == NULL) {
      fprintf(stderr, "COULDN'T ALLOCATE MEMORY FOR THREAD\n");
      exit(EXIT_FAILURE);
    }
    *arg = i+1;
    if (pthread_create(&th[i], NULL, &eat, arg) != 0) {
      fprintf(stderr, "FAILED TO CREATE THREAD\n");
      exit(EXIT_FAILURE);
    }
  }

  for (int i=0; i<TH_N; i++) {
    if (pthread_join(th[i], NULL) != 0) {
        fprintf(stderr, "FAILED TO JOIN THREAD\n");
        exit(EXIT_FAILURE);
    }
  }

  for (int i=0; i<TH_N; i++) {
    sem_destroy(&mutex[i]);
  }

  return EXIT_SUCCESS;

}
