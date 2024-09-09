#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	int pid;
        puts("Starting parent\n");
        pid=fork();
        if(pid>0)
        {
                printf("Parent PID: %d\t PPID: %d\n",getpid(),getppid());
                sleep(8);
		printf("Parent died");
        }
        if(pid==0)
        {
                printf("Child PID: %d\t PPID: %d\n",getpid(),getppid());
                sleep(15);
        }
        return 0;
}

