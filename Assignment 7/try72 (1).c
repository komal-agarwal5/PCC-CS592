#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<signal.h>
struct check{
	int raised;
	int sig;
}c;
void myhandler(int signum)
{
	c.raised=1;
	c.sig=signum;
}
int main()
{
	signal(SIGALRM,myhandler);
	c.raised=0;
	c.sig=0;
	int pid;
	pid=fork();
	if(pid==0)
	{
		printf("Child process running with PID:%d\tPPID:%d\n",getpid(),getppid());
		sleep(9);
		kill(getppid(),SIGALRM);
	}
	if(pid>0)
	{
		printf("Parent waiting with PID:%d\tPPID:%d\n",getpid(),getppid());
		while(c.raised==0)
		{
			printf("Parent is running\n");
			sleep(1);
		}
		printf("Alarm was sent to parent by child with PID:%d\n",pid);
		printf("Signal number was %d\n",c.sig);
	}
	return 0;
}
