#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
typedef struct cell{
int a[3][3];
int b[3][3];
int c[3][3];
int row;
int column;
}cell;

void *thread(void *arg) 
{
	cell *pass = (cell *)arg;
	int i=pass->row,j=pass->column;
	int k,x=0;
	for(k=0;k<3;k++){
		x=x+(pass->a[i][k]*pass->b[k][j]);
	}
	pass->c[i][j]=x;
	return NULL;
} 

int main() 
{ 
	int i,j;
	cell *pass = (cell *)malloc(sizeof(cell));
	for (i = 0; i < 3; i++)
		for(j=0;j<3; j++)
		{
			scanf("%d", &pass->a[i][j]);
		}
	for (i = 0; i < 3; i++)
		for(j=0;j<3; j++)
		{
			scanf("%d", &pass->b[i][j]);
		}
	pthread_t tid; 
	for (i = 0; i < 3; i++)
		for(j=0;j<3; j++)
		{	
			pass->row = i;
			pass->column = j;
			pthread_create(&tid, NULL, thread, (void *)pass);
		}
	pthread_join(tid, NULL);
	for (i = 0; i < 3; i++){
		for(j=0;j<3; j++)
		{
			printf("%6d", pass->c[i][j]);
		}
	printf("\n");
	}
	return 0; 
} 
