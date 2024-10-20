#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#define DATASIZE 50
int main()
{
	int pid;
	char msg[DATASIZE];
	int pfd[2];
	pipe(pfd);
	pid=fork();
	if(pid==0)
	{
		printf("Child process with PID:%d\tPPID:%d\n",getpid(),getppid());
		printf("Enter a message : ");
		fgets(msg,DATASIZE,stdin);
		write(pfd[1],msg,strlen(msg)+1);
	}
	if(pid>0)
	{
		printf("Parent process with PID:%d\tPPID:%d\n",getpid(),getppid());
		char data2[DATASIZE];
		read(pfd[0],data2,DATASIZE);
		printf("Message received from child is : %s\n",data2);
	}
	return 0;
}
