#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
char c[50];
int readcount=0;
sem_t wrt,mutex, rmutex, r1, r2, w1, w2;
void *reader1(void *vargp){
int i, t=100;
	while(t--){
	   sem_wait(&mutex);
	   readcount++;
	   if (readcount==1)     
	      sem_wait(&wrt);
	   sem_post(&mutex);                   
		sem_wait(&rmutex);
		printf("Reader 1 is reading... ");
		printf("%s", c);
		printf("\n");
		sem_post(&rmutex);
	   readcount--;
	   if (readcount == 0) 
	       sem_post(&wrt);
	}
	return NULL;
}
void *reader2(void *vargp){
int i, t=100;
	while(t--){
	   sem_wait(&mutex);
	   readcount++;
	   if (readcount==1)     
	      sem_wait(&wrt);
	   sem_post(&mutex);                   
		sem_wait(&rmutex);
		printf("Reader 2 is reading... ");
		printf("%s", c);
		printf("\n");
		sem_post(&rmutex);
	   readcount--;
	   if (readcount == 0) 
	       sem_post(&wrt);
	}
	return NULL;
}

void *writer1(void *vargp){
int i, t=100;
while(t--){
	sem_wait(&wrt);
	printf("Writer 1 is writing... ");
	for(i=0; i<49; i++){
		c[i] = 'a' + (rand()%26);
	}
		printf("%s", c);
		printf("\n");
	sem_post(&wrt);
}
return NULL;
}

void *writer2(void *vargp){
int i, t=100;
while(t--){
	sem_wait(&wrt);
	printf("Writer 2 is writing... ");
	for(i=0; i<49; i++){
		c[i] = 'a' + (rand()%26);
	}
		printf("%s", c);
		printf("\n");
	sem_post(&wrt);
}
return NULL;
}
int main(){
c[49] = '\0';
pthread_t t1,t2,t3,t4;
sem_init(&rmutex,0,1);
sem_init(&wrt,0,1);
sem_init(&mutex,0,1);
pthread_create(&t2, NULL, writer1, NULL);
pthread_create(&t4, NULL, writer2, NULL);
pthread_create(&t1, NULL, reader1, NULL);
pthread_create(&t3, NULL, reader2, NULL);
pthread_join(t1, NULL);
pthread_join(t2, NULL);
pthread_join(t3, NULL);
pthread_join(t4, NULL);
return 0;
}
