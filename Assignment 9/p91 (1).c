#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
sem_t mutex;
int ctr=0;
void* func1(void* arg)
{
	while(ctr!=6)
	{
		sem_wait(&mutex);
		printf("ba");
		ctr++;
		sem_post(&mutex);
		usleep(9000);
	}
	pthread_exit(NULL);
}
void* func2(void* arg)
{
	while(ctr!=6)
	{
		sem_wait(&mutex);
		printf("ab");
		ctr++;
		sem_post(&mutex);
		usleep(9000);
	}
	pthread_exit(NULL);
}
void main()
{
	pthread_t th1,th2;
	sem_init(&mutex,0,1);
	pthread_create(&th1,NULL,func1,NULL);
	pthread_create(&th2,NULL,func2,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	sem_destroy(&mutex);
	printf("\n");
}
