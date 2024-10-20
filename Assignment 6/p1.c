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
	char str1[DATASIZE];
	char str2[DATASIZE];
	printf("Enter first string : ");
	fgets(str1,DATASIZE,stdin);
	printf("Enter second string : ");
	fgets(str2,DATASIZE,stdin);
	mkfifo("./myfifo1",0666|IPC_CREAT);
	mkfifo("./myfifo2",0666|IPC_CREAT);
	int fd1=open("./myfifo1",O_WRONLY);
	write(fd1,str1,DATASIZE);
	write(fd1,str2,DATASIZE);
	close(fd1);
	char data[DATASIZE];
	int fd2=open("./myfifo2",O_RDONLY);
	read(fd2,data,DATASIZE);
	printf("Data returned back is : %s\n",data);
	close(fd2);
	return 0;
}
