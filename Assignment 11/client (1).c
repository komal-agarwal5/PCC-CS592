#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "h1.h"
int sigrcvd = 0;
void sighandler(int sig) 
{
    if (sig == SIGCONT)
        sigrcvd = 1;
}
int main() {
    int shmid = shmget(1234, sizeof(shm_area), 0666 | IPC_CREAT);
    smem = shmat(shmid, NULL, 0);
    smem->cpid = getpid(); 
    while (smem->spid < 1)
        usleep(1000);
    signal(SIGCONT, sighandler);
    while (1) 
    {
        char str[BUFFSIZE];
        printf("Enter a string (type EXIT to quit): ");
        scanf("%s", str);
        strcpy(smem->data, str); 
        kill(smem->spid, SIGCONT);  
        if (strcmp(str, "EXIT") == 0)
            break;
        while (!sigrcvd) 
            pause();
        int reply = smem->result;
        if (reply == 1)
            printf("Palindrome\n");
        else
            printf("Not Palindrome\n");

        sigrcvd = 0;
    }

    shmdt(smem);
    return 0;
}

