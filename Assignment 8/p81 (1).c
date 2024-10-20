#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int n=0;
void* func(void* arg)
{
	printf("Sub thread started..\n");
	printf("Enter value of n:");
	scanf("%d",&n);
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=i;
	}
	printf("Summation is : %d\n",sum);
	pthread_exit(NULL);
}
int main()
{
	printf("Main thread started..\n");
	pthread_t th1;
	pthread_create(&th1,NULL,func,NULL);
	pthread_join(th1,NULL);
	return 0;
}
