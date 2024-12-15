#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/shm.h>
#include "psem.h"
#include "buffer_ReaderWriter.h"

const char *FILENAME = "data.txt";
const int SIZE = 100;
const int SHMKEY = 1234;

buffer *sbuf = NULL;

void handler(int sigNum) {
  if (sigNum == SIGINT) {
    changeFlag(sbuf);
    printf("\nExiting Program\n");
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  signal(SIGINT, handler);

  int shmid;
  psem_t mutex, writer;
  char buf[SIZE];
  FILE *fptr;

  if ((shmid = shmget(SHMKEY, sizeof(buffer), 0666 | IPC_CREAT)) == -1) {
    fprintf(stderr, "Failed to execute shmget\n");
    exit(1);
  }

  sbuf = (buffer *)shmat(shmid, NULL, 0);

  buf_init(sbuf);

  if (!psem_init(&mutex, "MUTEX", 1)) {
    fprintf(stderr, "Failed to initialize semaphore\n");
    exit(1);
  }
  if (!psem_init(&writer, "WRITER", 1)) {
    fprintf(stderr, "Failed to initialize semaphore\n");
    exit(1);
  }

  while (getFlag(sbuf)) {
    if ((fptr = fopen(FILENAME, "r")) == NULL) {
      fprintf(stderr, "Failed to open file\n");
      changeFlag(sbuf);
      break;
    }

    psem_wait(&mutex);
    incrementReader(sbuf);
    if (getReaderCount(sbuf) == 1) {
      psem_wait(&writer);
    }
    psem_post(&mutex);

    if (fgets(buf, SIZE, fptr) == NULL) {
      fprintf(stderr, "Failed to read from file\n");
      changeFlag(sbuf);
      break;
    }

    psem_wait(&mutex);
    decrementReader(sbuf);
    if (getReaderCount(sbuf) == 0) {
      psem_post(&writer);
    }
    psem_post(&mutex);

    printf("%s\n", buf);

    fclose(fptr);

    sleep(1);
  }

  psem_destroy(&writer);
  psem_destroy(&mutex);

  printf("Exiting Program\n");

  return 0;
}
