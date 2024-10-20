#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* func(void* n)
{
	printf("Sub thread started..\n");
	int x=*((int*)n);
	int* sum=(int*)malloc(sizeof(int));
	for(int i=1;i<=x;i++)
	{
		*sum+=i;
	}
	pthread_exit((void*)sum);
}
int main()
{
	printf("Main thread started..\n");
	int n;
	int *ret;
	printf("Enter value of n: ");
	scanf("%d",&n);
	pthread_t th1;
	pthread_create(&th1,NULL,func,(void*)&n);
	pthread_join(th1,(void**)&ret);
	printf("Sum is :%d\n",*ret);
	return 0;
}
