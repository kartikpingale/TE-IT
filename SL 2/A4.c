/*
	ASSIGNMENT 4
	Thread synchronization using counting semaphores. Application to demonstrate producer-consumer problem with counting semaphores and mutex.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define SIZE 5

sem_t empty, full;
pthread_mutex_t x;
int buffer[SIZE], in=0, out=0;

void* producer(void* arg);
void* consumer(void* arg);

int main()
{
	pthread_t t1, t2;
	
	pthread_mutex_init(&x, NULL);
	sem_init(&empty, 0, SIZE);
	sem_init(&full, 0, 0);
	
	pthread_create(&t1, NULL, producer, NULL);
	pthread_create(&t2, NULL, producer, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	printf("\nDone!\n");
	
	return 0;
}

void* producer(void* arg)
{
	int item=1, i;
	
	while(1)
	{
		for(i=0; i<SIZE; i++)
		{
			sem_wait(&empty);
			pthread_mutex_lock(&x);
		
			printf("Produced item is %d", item);
			buffer[in] = item;
			in = (in+1)%SIZE;
			item++;
			
			pthread_mutex_unlock(&x);
			sem_post(&full);
		
			sleep(1);
		}
	}
}

void* consumer(void* arg)
{
	int item, i;
	
	while(1)
	{
		for(i=0; i<SIZE; i++)
		{
			sem_wait(&full);
			pthread_mutex_lock(&x);
		
			item = buffer[out];
			out = (out+1)%SIZE;
			printf("Consumed item is %d", item);
		
			pthread_mutex_unlock(&x);
			sem_post(&empty);
		
			sleep(1);
		}
	}
}
