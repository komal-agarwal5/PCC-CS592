/*
 *  Program: psem.h 
 *  Purpose: Definition of the semun union and process semaphore operations.
 *  Author : Dipankar Pal
 *  Last updated: 23.10.2024
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <string.h>
#include <malloc.h>

typedef struct {
	sem_t *semp;
	char *sname;
	int ival;
} psem_t;


int psem_holdon(psem_t *sem)
{
	int sval = -1;
	while(sval)
		sem_getvalue(sem->semp, &sval);
	return (sval);
}

int psem_init(psem_t *sem, const char *sname, int ival)
{
	if(ival >= 0) 
		sem_unlink(sname);
	//	sem->semp = sem_open (sname, O_CREAT, S_IRUSR | S_IWUSR, ival);
		sem->semp = sem_open (sname, O_CREAT, 0666, ival);

	sem->sname = (char *)malloc(strlen(sname)+1);
	strcpy(sem->sname, sname);
	sem->ival = ival;
	
	return (sem->semp != SEM_FAILED);
}

int psem_wait(psem_t *sem)
{
	return (sem_wait(sem->semp) != -1);
}

int psem_post(psem_t *sem)
{
	return (sem_post(sem->semp) != -1);
}

int psem_destroy(psem_t *sem)
{
	sem_close(sem->semp);
	int ret = sem_unlink(sem->sname);
	free(sem->sname);
	return(ret);
}

