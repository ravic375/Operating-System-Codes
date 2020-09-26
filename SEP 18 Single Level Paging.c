#include<stdio.h>
typedef struct page_table{
int pages[8];
}page_table;

void create_process(page_table *process[], int memory[256]){
int i,j,r,n;
for(i=0;i<8&&process[i]!=NULL;i++){}
if(i==8){
printf("You reached MAX Process Limit\n");
return;
}
n=i;
process[n]=(page_table *)malloc(sizeof(page_table));
printf("Enter required number of pages:");
scanf("%d", &r);
printf("Process %2d created\n", n);
for(i=0,j=10;i<r&&i<8;j++){
if(memory[j]==0){
process[n]->pages[i]=j;
printf("Allocating %4d\n", j);
memory[j]=1;
i++;
}
}
for(;i<8;i++){
process[n]->pages[i]=-1;
}
}

void remove_process(page_table *process[], int memory[256]){
int n,i;
printf("Enter Process number to eliminate:");
scanf("%d", &n);
for(i=0;i<8;i++){
if(memory[process[n]->pages[i]]==1)
printf("DeAllocating %4d\n", process[n]->pages[i]);
memory[process[n]->pages[i]]=0;
}
free(process[n]);
process[n]=NULL;
return;
}

void address_translate(page_table *process[]){
int n,p;
printf("Process number:");
scanf("%d", &n);
printf("Page number:");
scanf("%d", &p);
printf("Frame %4d", process[n]->pages[p]);
}

int main(){
page_table *process[10];
int n, memory[256];
for(n=0;n<256;n++){
memory[n]=0;
}
for(n=0;n<8;n++){
process[n]=NULL;
}
while(1){
scanf("%d", &n);
switch (n)
{
    case 1: create_process(process, memory);
        break;
    case 2: remove_process(process, memory);
        break;
    case 3: address_translate(process);
        break;
}
}
return 0;
}
