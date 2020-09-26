#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
char c;
int x=0;
sem_t p, c1, c2, mutex;
void *producer(void *vargp){
	while(1){
		sem_wait(&p);
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
void *consumer1(void *vargp){
	while(1){
		sem_wait(&c1);
		sem_post(&mutex);
		if(x!=0){
			x--;
			printf("Consumed by A\t%d items in BUFFER\n", x);
		}
		else
			printf("No items to consume\n");
		sem_post(&mutex);
	}
	return NULL;
}
void *consumer2(void *vargp){
	while(1){
		sem_wait(&c2);
		sem_post(&mutex);
		if(x!=0){
			x--;
			printf("Consumed by B\t%d items in BUFFER\n", x);
		}
		else
			printf("No items to consume\n");
		sem_post(&mutex);
	}
	return NULL;
}
int main(){
	pthread_t t1,t2,t3;
	sem_init(&p,0,0);
	sem_init(&c1,0,0);
	sem_init(&c2,0,0);
	sem_init(&mutex,0,1);
	pthread_create(&t1, NULL, producer, NULL);
	pthread_create(&t2, NULL, consumer1, NULL);
	pthread_create(&t3, NULL, consumer2, NULL);
	printf("Enter P to produce\nEnter A for Consumer 1 to consume\nEnter B for Consumer 2 to consume\n");
	while(1){
		scanf("%c", & c);
		if(c == 'p' || c == 'P')
			sem_post(&p);
		else if(c == 'a' || c == 'A')
			sem_post(&c1);
		else if(c == 'b' || c == 'B')
			sem_post(&c2);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
