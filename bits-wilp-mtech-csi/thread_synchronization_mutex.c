#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t threadids[2];
pthread_mutex_t mutex_lock;
int counter;

void* func1(void* arg)
{
	// acquiring resource lock
	pthread_mutex_lock(&mutex_lock);
	unsigned long i = 0;
	//counter += 1;
	counter = counter + 1;
	printf("Function %d has started\n", counter);
	for (i = 0; i < (0xFFFFFFFF); i++)
		;
	printf("\t Function %d has finished\n", counter);
	// releasing resource lock
	pthread_mutex_unlock(&mutex_lock);
	return NULL;
}

int main(void)
{
	int i = 0;
	int result;
	// lock initialization
	if (pthread_mutex_init(&mutex_lock, NULL) != 0) {
		printf("Failed to initialize mutex\n");
		return 1;
	}
	// verify if 2 locks are initiated
	while (i < 2) {
		result = pthread_create(&(threadids[i]),NULL,&func1, NULL);
		if (result != 0)
			printf("Failed to create thread :[%s]",strerror(result));
		i++;
	}
	// wait for the thread to terminate
	pthread_join(threadids[0], NULL);
	pthread_join(threadids[1], NULL);
	pthread_mutex_destroy(&mutex_lock);
	return 0;
}

