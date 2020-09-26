#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
int g = 1;
void *thread1(void *vargp) 
{ 
	printf("thread1: wait...\n");
	g=g+23;
	return NULL;
} 
void *thread2(void *vargp) 
{ 
	printf("thread2: wait...\n");
	g=g*6;
	return NULL;
} 
int main() 
{ 
	int i; 
	pthread_t tid1, tid2; 
	for (i = 0; i < 3; i++)
	{
		pthread_create(&tid1, NULL, thread1, NULL); 
		pthread_create(&tid2, NULL, thread2, NULL); 
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL); 
	printf("g = %d\n", g); 
	return 0; 
} 
