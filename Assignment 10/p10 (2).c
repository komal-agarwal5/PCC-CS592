#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#define n 5
sem_t mutex;
sem_t full;
sem_t empty;
typedef struct
{
	int data[n];
	int front,rear;
}cq;
cq buff;
void sbuff_init(cq* buff)
{
	buff->front=buff->rear=-1;
	return;
}
void sbuff_insert(cq* buff,int item)
{
	if(buff->front==-1 && buff->rear==-1)
		buff->front=buff->rear=0;
	else
		buff->rear=(buff->rear+1)%n;
	buff->data[buff->rear]=item;
}
int sbuff_delete(cq* buff)
{
	int item;
	item=buff->data[buff->front];
	buff->front=(buff->front+1)%n;
	return item;
}
void sbuff_destroy(cq* buff)
{
	buff->front=buff->rear=-1;
}
void* produce(void* arg)
{
	int item=0;
	while(1)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		item++;
		sbuff_insert(&buff,item);
		printf("Item produced is : %d\n",item);
		sem_post(&mutex);
		sem_post(&full);
		sleep(2);
	}
	pthread_exit(NULL);
}
void* consume(void* arg)
{
	while(1)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		int item=sbuff_delete(&buff);
		printf("Item consumed is : %d\n",item);
		sem_post(&mutex);
		sem_post(&empty);
		sleep(2);
	}
	pthread_exit(NULL);
}
void main()
{
	pthread_t th1,th2;
	sbuff_init(&buff);
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,n);
	pthread_create(&th1,NULL,produce,NULL);
	pthread_create(&th2,NULL,consume,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
}

