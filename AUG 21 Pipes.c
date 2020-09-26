#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

void sort(int* a)
{int t;
int i,j;
for(i=0;i<5;i++)
{for(j=0;j<5;j++)
{if(a[i]>a[j]){
t=a[i];
a[i]=a[j];
a[j]=t;}
}
}
}
 int main(int argc, char*argv[])
{
   int pipefds[2];
   int pipe2[2],i;
   int pipe3[2];
   int pipe4[2];
   int returnstatus;
   int writemessages[5]={1, 7, 3, 2, 9};
   int readmessage[5];
   int msg[5];

returnstatus = pipe(pipefds);
if (returnstatus == -1)
{
      printf("Unable to create pipe\n");
      return 1;
}

returnstatus = pipe(pipe2);
if (returnstatus == -1)
{
      printf("Unable to create pipe\n");
      return 1;
}

returnstatus = pipe(pipe3);
if (returnstatus == -1)
{
      printf("Unable to create pipe\n");
      return 1;
}

returnstatus = pipe(pipe4);
if (returnstatus == -1)
{
      printf("Unable to create pipe\n");
      return 1;
}

write(pipefds[1], writemessages, sizeof(writemessages));
int rc=fork();

if(rc<0)
{
printf("unsucs");
}
else if(rc==0)
{
    read(pipefds[0],readmessage,sizeof(readmessage));
    sort(readmessage);
    write(pipe2[1], readmessage, sizeof(readmessage));
exit(0);
}
else
{
    wait(NULL);
    read(pipe2[0], msg, sizeof(msg));
    for( i=0; i<5; i++)
    printf("%d\n",msg[i]);
}

write(pipe4[1], writemessages, sizeof(writemessages));
rc=fork();
if(rc<0)
{
printf("unsucs");
}
   else if(rc==0)
   {
    read(pipe4[0],readmessage,sizeof(readmessage));
    write(pipe3[1], readmessage, sizeof(readmessage));
exit(0);
   }
   else{
    wait(NULL);
    read(pipe3[0], msg, sizeof(msg));
printf("\n");
    for( i=0; i<5; i++)
printf("%d\n",msg[i]);
       }

   return 0;
}