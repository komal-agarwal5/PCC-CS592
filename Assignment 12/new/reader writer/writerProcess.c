#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
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
  psem_t writer;
  char buf[SIZE];
  FILE *fptr;

  if ((shmid = shmget(SHMKEY, sizeof(buffer), 0666 | IPC_CREAT)) == -1) {
    fprintf(stderr, "Failed to execute shmget\n");
    exit(1);
  }

  sbuf = (buffer *)shmat(shmid, NULL, 0);

  buf_init(sbuf);

  if (!psem_init(&writer, "WRITER", 1)) {
    fprintf(stderr, "Failed to initialize semaphore\n");
    exit(1);
  }

  while (getFlag(sbuf)) {
    printf("Enter string: ");
    if (fgets(buf, SIZE, stdin) == NULL) {
      fprintf(stderr, "Failed to take input\n");
      changeFlag(sbuf);
      break;
    }
    buf[strlen(buf)-1] = '\0';

    psem_wait(&writer);

    if ((fptr = fopen(FILENAME, "w")) == NULL) {
      fprintf(stderr, "Failed to open file\n");
      changeFlag(sbuf);
      break;
    }

    fprintf(fptr, "%s", buf);

    psem_post(&writer);

    printf("Wrote to file\n");

    fclose(fptr);

    sleep(1);
  }

  psem_holdon(&writer);

  printf("Exiting Program\n");

  return 0;
}
