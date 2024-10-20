#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "h1.h"
int sigrcvd = 0;
void sighandler(int sig) {
    if (sig == SIGCONT)
        sigrcvd = 1;
}
int main() 
{
    int shmid = shmget(1234, sizeof(shm_area), 0666 | IPC_CREAT);
    smem = shmat(shmid, NULL, 0);
    smem->spid = getpid();
    while (smem->cpid < 1)
        usleep(1000);
    signal(SIGCONT, sighandler);
    while (1) 
    {
        pause(); 
        if (sigrcvd) 
        {
            char str[BUFFSIZE];
            strcpy(str, smem->data);
            if (strcmp(str, "EXIT") == 0)
                break;
            int len = strlen(str);
            int is_pal = 1;
            for (int i = 0; i < len / 2; i++) {
                if (str[i] != str[len - i - 1]) {
                    is_pal = 0;
                    break;
                }
            }
            smem->result = is_pal;
            kill(smem->cpid, SIGCONT);
            sigrcvd = 0;
        }
    }
    shmdt(smem);
    return 0;
}
