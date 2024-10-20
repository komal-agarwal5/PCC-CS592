#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define TH_N 10
#define SIZE 100


sem_t mutex, writeMutex;
char *file = "data.txt";


void *reader(void *args) {

  while (1) {

    static int readerCount = 0;
  
    sem_wait(&mutex);
    readerCount++;
    if (readerCount == 1) {
      sem_wait(&writeMutex);
    }
    sem_post(&mutex);
  
    FILE *fptr;
    if ((fptr = fopen(file, "r")) == NULL) {
      perror("FAILED TO OPEN FILE\n");
      exit(EXIT_FAILURE);
    }
  
    char content[SIZE];
    fgets(content, SIZE, fptr);
    printf("%s\n", content);
  
    fclose(fptr);
  
    sem_wait(&mutex);
    readerCount--;
    if (readerCount == 0) {
      sem_post(&writeMutex);
    }
    sem_post(&mutex);
  
    sleep(1);

  }

}


void *writeMutexr(void *args) {

  while (1) {

    sem_wait(&writeMutex);
  
    FILE *fptr;
    if ((fptr = fopen(file, "w")) == NULL) {
      fprintf(stderr, "FAILED TO OPEN FILE\n");
      exit(EXIT_FAILURE);
    }
  
    char buffer[SIZE];
    printf("Enter text: ");
    fgets(buffer, SIZE, stdin);
    fprintf(fptr, "%s", buffer);  
  
    fclose(fptr);
  
    sem_post(&writeMutex);
  
    sleep(1);

  }

}


int main(int argc, char *argv[]) {

  sem_init(&mutex, 0, 1);
  sem_init(&writeMutex, 0, 1);

  pthread_t th[TH_N];

  for (int i=0; i<TH_N; i++) {
    if (i % 2 == 0) {
      if (pthread_create(&th[i], NULL, &reader, NULL) != 0) {
        perror("FAILED TO CREATE THREAD\n");
        exit(EXIT_FAILURE);
      }
    } else {
      if (pthread_create(&th[i], NULL, &writeMutexr, NULL) != 0) {
        perror("FAILED TO CREATE THREAD\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  for (int i=0; i<TH_N; i++) {
    if (pthread_join(th[i], NULL) != 0) {
        perror("FAILED TO JOIN THREAD\n");
        exit(EXIT_FAILURE);
    }
  }

  sem_destroy(&mutex);
  sem_destroy(&writeMutex);

  return EXIT_SUCCESS;

}
