#include <stdio.h> 
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
char c;
int x=0;
sem_t full,empty, mutex;
void *producer(void *vargp){
	while(1){
		sem_wait(&empty);
		sem_wait(&mutex);
		if(x!=BUFFER_SIZE){
			x++;
			printf("%d items in BUFFER\n", x);
		}
		else
			printf("BUFFER Full\n");
		sem_post(&mutex);
	}
	return NULL;
}
void *consumer(void *vargp){
	while(1){
		sem_wait(&full);
		sem_post(&mutex);
		if(x!=0){
			x--;
			printf("%d items in BUFFER\n", x);
		}
		else
			printf("No items to consume\n");
		sem_post(&mutex);
	}
	return NULL;
}
int main(){
	pthread_t t1,t2;
	sem_init(&empty,0,0);
	sem_init(&full,0,0);
	sem_init(&mutex,0,1);
	pthread_create(&t1, NULL, producer, NULL);
	pthread_create(&t2, NULL, consumer, NULL);
	printf("Enter p to produce\nEnter c to consume\n");
	while(1){
		scanf("%c", & c);
		if(c == 'p' || c == 'P')
			sem_post(&empty);
		else if(c == 'c' || c == 'C')
			sem_post(&full);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
