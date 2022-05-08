#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<pthread.h>

pthread_mutex_t first_mutex, second_mutex; // mutex locks
void *func1(); // functions or resources
void *func2(); // functions or resources

// Functions will try to acquire mutex locks in opposite order

void *func1(){
    // acquiring resource lock order - first then second
    pthread_mutex_lock(&first_mutex);
    printf("Thread1 has acquired first_mutex...\n");
    sleep(2);
    printf("Now, Thread1 is trying to get second_mutex...\n");
    pthread_mutex_lock(&second_mutex); 
    printf("Thread1 has acquired second_mutex...\n");

    // Releasing second mutex
    pthread_mutex_unlock(&second_mutex);
    printf("Thread1 released second_mutex...\n");
    // Releasing first mutex
    printf("Thread1 released first_mutex...\n");
    pthread_mutex_unlock(&first_mutex);

    pthread_exit(NULL);

}

void *func2(){
    // acquiring resource lock order - second then first
    pthread_mutex_lock(&second_mutex);
    printf("Thread2 has acquired second_mutex...\n");
    sleep(2);
    printf("Now, Thread2 is trying to get first_mutex...\n");
    pthread_mutex_lock(&first_mutex); 
    printf("Thread2 has acquired first_mutex...\n");

    // Releasing first mutex
    pthread_mutex_unlock(&first_mutex);
    printf("Thread2 released first_mutex...\n");
    pthread_mutex_unlock(&second_mutex);
    //printf("Thread2 released second_mutex...\n");

    pthread_exit(NULL);

}



int main() {
    // lock initialization
    pthread_mutex_init(&first_mutex,NULL);
    pthread_mutex_init(&second_mutex,NULL);

    pthread_t thread1,thread2;
    
    // thread create
    pthread_create(&thread1,NULL,func1,NULL);
    pthread_create(&thread2,NULL,func2,NULL);

    // wait for the thread to terminate
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("Threads joined\n");
    return 0;

}
