#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<pthread.h>
#include <semaphore.h>

//declaring semaphore 
sem_t * sema1;
sem_t * sema2;

void* t1(void *arg)
{
	for(int i=0;i<10;i++)
	{
		sem_wait(sema1); // decrements the semaphore, P Operation
		printf("Thread 1 is executing...%d\n",i);
		sem_post(sema2); // increments the semaphore, V Operation
	}       
	printf("Thread1 return\n");
	return NULL;
}

void* t2(void *arg)
{
	for(int i=0;i<10;i++)
	{
		sem_wait(sema2); // decrements the semaphore, P Operation
		printf("Thread 2 is executing...%d\n",i);
		sem_post(sema1); // increments the semaphore, V Operation
	}
	printf("Thread2 return\n");
	return NULL;
}


int main()
{
	pthread_t thread1, thread2; // thread declration
	char * name1 = "name1";
	char * name2 = "name2";
	int value1 = 1;
	int value2 = 2;
	// sem_init is for unnamed semaphores
	// sem_open is for named semaphores
	// On Mac OS X, only named semaphores are supported
	sema1 = sem_open(name1, O_CREAT, 0666, value1); 
	sema2 = sem_open(name2, O_CREAT, 0666, value2);

	pthread_create(&thread1, NULL, t1, NULL); // thread creation
	usleep(100);
	pthread_create(&thread2, NULL, t2, NULL);
	usleep(100);

	pthread_join(thread2, NULL); // thread join (wait)
	pthread_join(thread1, NULL);

	sem_unlink(name1); // remove the semaphore associated with the name1
	sem_unlink(name2); // remove the semaphore associated with the name1

	return 0;
}
