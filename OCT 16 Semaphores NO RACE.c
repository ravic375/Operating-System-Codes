#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <semaphore.h>
int x=0;
sem_t s1,s2;
void *increment_t1_100000(void *vargp){
int i;
for(i=0;i<100000;i++){
sem_wait(&s2);
x++;
printf("From 1\n");
sem_post(&s1);
}
return NULL;
}
void *increment_t2_100000(void *vargp){
int i;
for(i=0;i<100000;i++){
sem_wait(&s1);
x++;
printf("From 2\n");
sem_post(&s2);
}
return NULL;
}
int main(){
pthread_t t1,t2;
sem_init(&s1,0,1);
sem_init(&s2,0,0);
pthread_create(&t1, NULL, increment_t1_100000, NULL);
pthread_create(&t2, NULL, increment_t2_100000, NULL);
pthread_join(t1, NULL);
pthread_join(t2, NULL);
printf("%d\n", x);
return 0;
}
