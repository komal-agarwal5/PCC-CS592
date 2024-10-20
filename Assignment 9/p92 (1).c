#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

#define  MAX  32

void* func(void *v)
{
	int n=*((int*) v);
	char *p=(char*)malloc(sizeof(char)*MAX);
	int c=0;
	if(n==0 || n==1)
		strcpy(p,"NOT PRIME");
	else
	{
		for(int i=2;i<=n/2;i++)
		{
			if(n%i==0)
				c++;
		}
		if(c>=1)
			strcpy(p,"NOT PRIME");
		else
			strcpy(p,"PRIME");
	}
	pthread_exit((void*)p);
}
void main()
{
	pthread_t th1;
	int n;
	char *res;
	printf("Enter value : ");
	scanf("%d",&n);
	pthread_create(&th1,NULL,func,(void*)&n);	
	pthread_join(th1,(void**)&res);
	printf("%s\n",res);
}
