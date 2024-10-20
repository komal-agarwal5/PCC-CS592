#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ipc.h>
#define DATASIZE 50
int main()
{
	char data1[DATASIZE];
	char data2[DATASIZE];
        int fd1=open("./myfifo1",O_RDONLY);
        read(fd1,data1,DATASIZE);
	read(fd1,data2,DATASIZE);
        close(fd1);
	char msg[DATASIZE];
	if(strcmp(data1,data2)==0)
		strcpy(msg,"SAME\n");
	else
		strcpy(msg,"NOT SAME\n");
        int fd2=open("./myfifo2",O_WRONLY);
        write(fd2,msg,DATASIZE);
        close(fd2);
        return 0;
}
