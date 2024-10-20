#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
struct check{
	int received;
}c;
void leap(int y)
{
	if(y%400==0)
		printf("Leap year\n");
	else if(y%100!=0 && y%4==0)
		printf("Leap year\n");
	else
		printf("Not leap year\n");
}
void myhandler(int signum)
{
	c.received=1;
}
int main()
{
	int pid,i=1,n;
	signal(SIGCHLD,myhandler);
	c.received=0;
	pid=fork();
	if(pid==0)
	{
		printf("Child process with PID : %d and PPID : %d started..\n",getpid(),getppid());
		while(1)
		{
			pause();
			if(c.received==1)
			{
				printf("Child Process %d : Enter year to check leap year or not : ",getpid());
				scanf("%d",&n);
				leap(n);
				c.received=0;
			}
		}
	}
	else
	{
		printf("Parent process with PID : %d and PPID : %d started..\n",getpid(),getppid());
		while(i==1)
		{
			sleep(5);
			printf("Enter 1 to continue: ");
			scanf("%d",&i);
			if(i==0) 
				continue;
			printf("Parent sending signal to child with PID %d ..\n",pid);
			kill(pid,SIGCHLD);
		}
	}
	return 0;
}
